📌 About the Portable AI Voice Assistant Project

The Portable AI Voice Assistant is a compact, standalone personal assistant designed to provide intelligent, voice-based interaction without relying on a traditional screen-based interface. The device allows users to ask questions verbally and receive spoken responses through a built-in speaker, making the interaction natural and hands-free.

This assistant is powered by an AI large language model (LLM) and is capable of understanding spoken input, processing it in real time, and generating meaningful responses. It supports a wide range of use cases, including:

General knowledge queries

Mathematics and logical problem solving

Real-time language translation

Conversational questions and assistance

The project has been tested using Google’s Gemini LLM, achieving very low response latency, which makes conversations feel smooth and practical for real-world use. The entire system is designed to be portable, allowing it to function as a personal AI companion that can be used anywhere.

This project was built to explore the integration of AI, embedded systems, and real-time voice interaction in a compact hardware form, demonstrating how modern AI models can be deployed beyond phones and computers into dedicated physical devices.

💡 Why I Built This Project

I built the Portable AI Voice Assistant because I wanted to explore how modern AI can be integrated into a standalone physical device rather than just living in apps on phones or computers. I’ve always been fascinated by voice-based interaction — but most AI assistants today either require a smartphone or cloud services, and I wanted to push beyond that to create something portable, hardware-based, and fully interactive.

This project gave me the chance to learn and overcome real engineering challenges: capturing and processing audio in real time, connecting to a large language model like Google’s Gemini, and generating voice responses with minimal latency. It helped me deepen my understanding of embedded hardware, real-time audio pipelines, and practical AI integration — skills I didn’t have before.

Another key motivation was accessibility and usability. I believe that technology should be easy to interact with, and voice input/output makes information more accessible for everyone, especially in situations where screens aren’t ideal. Building this project was a way for me to bring AI into the physical world in a practical and useful way, while also documenting the full process so others can learn from it




🛠️ 3. Assembly Instructions

This section explains how to assemble the Portable AI Voice Assistant from scratch using the custom PCB and components shown above. Basic experience with soldering and electronics assembly is recommended.

<img width="1919" height="1079" alt="Screenshot 2025-12-17 122840" src="https://github.com/user-attachments/assets/54718d8f-3bc5-4fc4-bd4f-b8f85da76220" />

🔧 Tools Required

Soldering iron (fine tip)

Solder wire

Flux (for SMD components)

Tweezers

Multimeter

Hot glue or double-sided tape

USB-C cable

📘 Step 1: PCB Inspection

Inspect the PCB for any visible damage or manufacturing defects. Identify the major sections on the board, including the ESP32 module footprint, microphone section, speaker terminals, SD card slot, buttons, power input, and charging circuit.


<img width="1919" height="1079" alt="Screenshot 2025-12-17 122942" src="https://github.com/user-attachments/assets/1d793230-ea30-4d3d-8bfb-47d50fb61036" />
🔌 Step 2: Power Section Assembly

Solder the small surface-mount components in the power regulation and charging section first. This includes resistors, capacitors, voltage regulator ICs, and the USB-C connector. After soldering, use a multimeter to verify proper continuity and voltage rails.

🧠 Step 3: ESP32 Module Installation

Align the ESP32 module with the PCB footprint and solder all castellated pads carefully. Ensure there are no solder bridges between pins, as the ESP32 is the main controller responsible for connectivity and AI communication.

🎙️ Step 4: Microphone Installation

Solder the microphone module in the designated area on the PCB. Make sure the orientation is correct so that power, ground, and signal lines are properly connected.

<img width="713" height="444" alt="Screenshot 2025-12-17 123058" src="https://github.com/user-attachments/assets/1cf3d303-7d91-4f2d-aee8-0f409e7603ee" />

🔊 Step 5: Speaker Connection

Connect the speaker wires to the PCB terminals marked SPK+ and SPK−. Secure the speaker to the enclosure or PCB using screws to prevent movement and vibration during operation.

💾 Step 6: SD Card Slot Assembly

Solder the micro-SD card slot onto the PCB. This slot is used for storing audio files and other data required by the system. Insert the SD card only after soldering is complete.

🔘 Step 7: Button Installation

Solder the tactile buttons for REC, BOOT, and RESET. Ensure the buttons are properly aligned so they are accessible once the device is enclosed.

🔋 Step 8: Battery Connection

Connect the Li-ion battery to the PCB terminals labeled B+ and B−, ensuring correct polarity. Confirm that the charging circuit functions correctly when USB power is applied.

💻 Step 9: Firmware Upload and Testing

Connect the device to a computer using a USB-C cable and upload the firmware to the ESP32. Test the microphone input, speaker output, button functionality, and overall system response before final enclosure assembly.

✅ Final Assembly

After successful testing, secure all components inside the enclosure. Ensure all wires are properly routed and that the microphone and speaker openings are unobstructed. The Portable AI Voice Assistant is now fully assembled and ready for use.




# here is 3d model 



![MixCollage-17-Dec-2025-11-39-PM-2850](https://github.com/user-attachments/assets/838167b1-440b-4e6f-88d9-1e99411322d2)



# pcb image

![WhatsApp Image 2025-12-17 at 12 38 31 PM](https://github.com/user-attachments/assets/d4aad548-e51d-43b3-bbc9-7723d722d373)

# wireing diagram

<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/c97a6c81-99bd-4f8c-a196-58b22f102c15" />
