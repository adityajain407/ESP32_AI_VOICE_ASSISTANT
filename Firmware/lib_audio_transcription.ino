// --- API key (replace with your ElevenLabs key) ---
const char* deepgramApiKey = "sk_3fcc3f1de0b09e8dbdecafeff28a482818e491d03d50db75"; // renamed var kept for minimal change

// ---------------------------------------------
// SpeechToText_Deepgram (modified to call ElevenLabs API only)
// ---------------------------------------------
String SpeechToText_Deepgram( String audio_filename )
{
  uint32_t t_start = millis();

  // ---------- Connect to ElevenLabs Server (only if needed)
  if ( !client.connected() )
  { DebugPrintln("> Initialize ElevenLabs Server connection ... ");
    client.setInsecure();
    if (!client.connect("api.elevenlabs.io", 443))
    { Serial.println("\nERROR - WifiClientSecure connection to ElevenLabs Server failed!");
      client.stop();
      return ("");
    }
    DebugPrintln("Done. Connected to ElevenLabs Server.");
  }
  uint32_t t_connected = millis();

  // ---------- Check if AUDIO file exists, check file size
  File audioFile = SD.open( audio_filename );
  if (!audioFile) {
    Serial.println("ERROR - Failed to open file for reading");
    return ("");
  }
  size_t audio_size = audioFile.size();
  audioFile.close();
  DebugPrintln("> Audio File [" + audio_filename + "] found, size: " + (String) audio_size );

  // ---------- flush inbound streaming data before new request
  String socketcontent = "";
  while (client.available())
  { char c = client.read(); socketcontent += String(c);
  } int RX_flush_len = socketcontent.length();

  // ---------- Sending HTTPS request header to ElevenLabs Server
  // Keep same linear POST approach as original: send raw WAV with Content-Type audio/wav
  client.println("POST /v1/speech-to-text HTTP/1.1");
  client.println("Host: api.elevenlabs.io");
  client.println("xi-api-key: " + String(deepgramApiKey)); // ElevenLabs header
  client.println("Content-Type: audio/wav");
  client.println("Content-Length: " + String(audio_size));
  client.println();   // header complete, now sending binary body (wav bytes)
  DebugPrintln("> POST Request to ElevenLabs Server started, sending WAV data now ..." );
  uint32_t t_headersent = millis();

  // ---------- Reading the AUDIO wav file, sending in CHUNKS
  File file = SD.open( audio_filename, FILE_READ );
  const size_t bufferSize = 3072;
  uint8_t buffer[bufferSize];
  size_t bytesRead;

  while (file.available())
  { bytesRead = file.read(buffer, sizeof(buffer));
    if (bytesRead > 0) { client.write(buffer, bytesRead); }   // sending WAV AUDIO data
  }

  file.close();
  DebugPrintln("> All bytes sent, waiting ElevenLabs transcription");
  uint32_t t_wavbodysent = millis();

  // ---------- Waiting to ElevenLabs Server response (stop waiting after TIMEOUT_DEEPGRAM secs)
  String response = "";
  while ( response == "" && millis() < (t_wavbodysent + TIMEOUT_DEEPGRAM*1000) )
  { while (client.available())
    { char c = client.read();
      response += String(c);
    }
    DebugPrint(".");  delay(100);
  }
  DebugPrintln();
  if (millis() >= (t_wavbodysent + TIMEOUT_DEEPGRAM*1000))
  { Serial.print("\n*** TIMEOUT ERROR - forced TIMEOUT after " + (String) TIMEOUT_DEEPGRAM + " seconds"); 
    Serial.println(" (is your ElevenLabs API Key valid ?) ***\n");
  }
  uint32_t t_response = millis();

  // ---------- closing connection (keep same behavior as original)
  client.stop();

  // ---------- Parsing response: ElevenLabs returns "text"
  int    response_len  = response.length();
  String transcription = json_object( response, "\"text\":" );
  String language      = json_object( response, "\"detected_language\":" ); // may be empty for ElevenLabs
  String wavduration   = json_object( response, "\"duration\":" );

  DebugPrintln( "---------------------------------------------------" );
  DebugPrintln( "-> Latency Server (Re)CONNECT [t_connected]:   " + (String) ((float)((t_connected-t_start))/1000) );
  DebugPrintln( "-> Latency sending HEADER [t_headersent]:      " + (String) ((float)((t_headersent-t_connected))/1000) );
  DebugPrintln( "-> Latency sending WAV file [t_wavbodysent]:   " + (String) ((float)((t_wavbodysent-t_headersent))/1000) );
  DebugPrintln( "-> Latency ELEVENLABS response [t_response]:   " + (String) ((float)((t_response-t_wavbodysent))/1000) );
  DebugPrintln( "=> TOTAL Duration [sec]: ..................... " + (String) ((float)((t_response-t_start))/1000) );
  DebugPrintln( "=> RX data prior request [bytes]: " + (String) RX_flush_len );
  DebugPrintln( "=> Server detected audio length [sec]: " + wavduration );
  DebugPrintln( "=> Server response length [bytes]: " + (String) response_len );
  DebugPrintln( "=> Detected language (optional): [" + language + "]" );
  DebugPrintln( "=> Transcription: [" + transcription + "]" );
  DebugPrintln( "---------------------------------------------------\n" );

  return transcription;
}

// ---------------------------------------------
// Deepgram_KeepAlive (modified to call ElevenLabs endpoint only)
// ---------------------------------------------
void Deepgram_KeepAlive()        // should be called each ~5 seconds (keeps connection alive)
{
  led_RGB(0, 50, 0);
  uint32_t t_start = millis();
  DebugPrint( "* ElevenLabs KeepAlive | " );

  if ( !client.connected() )
  { DebugPrint("NEW Reconnection ... ");
    client.setInsecure();
    if (!client.connect("api.elevenlabs.io", 443))
    { Serial.println("\n* PING Error - Server Connection failed.");
      x++;
      if (x > 2) { esp_restart(); }
      return;
    }
    DebugPrint( "Done, connected.  -->  Connect Latency [sec]: ");
    DebugPrintln( (String)((float)((millis()-t_start))/1000) );
    led_RGB(0, 0, 0);
    return;
  }

  // sending a dummy 16Khz/8bit audio wav header and small silent data to ElevenLabs endpoint
  uint8_t empty_wav[] = {
    0x52,0x49,0x46,0x46, 0x40,0x00,0x00,0x00, 0x57,0x41,0x56,0x45,0x66,0x6D,0x74,0x20,
    0x10,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x80,0x3E,0x00,0x00,0x80,0x3E,0x00,0x00,
    0x01,0x00,0x08,0x00,0x64,0x61,0x74,0x61, 0x14,0x00,0x00,0x00, 0x80,0x80,0x80,0x80,
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80 };

  client.println("POST /v1/speech-to-text HTTP/1.1");
  client.println("Host: api.elevenlabs.io");
  client.println("xi-api-key: " + String(deepgramApiKey));
  client.println("Content-Type: audio/wav");
  client.println("Content-Length: " + String(sizeof(empty_wav)));
  client.println(); // header complete, now sending wav bytes ..
  client.write(empty_wav, sizeof(empty_wav));

  // ---------- RX - read any available data (do not block)
  String response = "";
  while (client.available())
  { char c = client.read(); response += String(c);
  } int RX_len = response.length();

  // NOT closing connection here (keeps same logic as original)
  DebugPrint( "TX (WAV): " + (String) sizeof(empty_wav) + " bytes | " );
  DebugPrint( "RX (TXT): " + (String) RX_len + " bytes  -->  " );
  DebugPrintln( "Total Latency [sec]: " + (String) ((float)((millis()-t_start))/1000) );
}

// ---------------------------------------------
// json_object unchanged except it'll now be used to extract "text"
String json_object( String input, String element )
{ String content = "";
  int pos_start = input.indexOf(element);
  if (pos_start > 0)
  {  pos_start += element.length();
     int pos_end = input.indexOf( ",\"", pos_start);
     if (pos_end > pos_start)
     { content = input.substring(pos_start,pos_end);
     } content.trim();
     if (content.startsWith("\""))
     { content=content.substring(1,content.length()-1);
     }
  }
  return (content);
}