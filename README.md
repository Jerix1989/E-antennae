**# E-antennae**
Arduino code for spike encoding function used in the project of electronic antennae


**Arduino_Code_for_Spike_Encoding**
Functionality of this code:
Briefly, the spike-encoding strategy is implemented in this code. The spike encoding function starts with reading the current value of the sensor signal. Then, the current sensor value is compared with the previous sensor value. If the absolute difference between them is larger than the predefined FA threshold, an FA pulse is generated. Subsequently, the current sensor value is compared with the default sensor value, and if the absolute difference is greater than the predefined SA threshold, an SA pulse is generated. In this way, two pairwise sets of FA and SA spike trains are simultaneously derived from the signal of one sensor, achieving the spike-encoding function. The spike trains are then sent to the artificial synaptic device for spatiotemporal processing.

**System requirements:**
•	Software Arduino IDE is required to run this code. The open-source Arduino Software (IDE) makes it easy to write code and upload it to the Arduino board. This software can be installed on Windows, macOS, or Linux.
•	This code has been successfully compiled and tested on the software of Arduino IDE with version number 1.8.19.
•	This code is required to uploaded to the Arduino hardware. Arduino Nano board is the preferred hardware. There is no requirement on non-standard hardware.


**Installation guide:**
•	The installation of this software on Windows follows the steps below (https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE): 
1.	Download the software Arduino IDE 1.8.19 (The download will start after you click this link. Check your browser’s download manager or the Downloads folder on your computer to find the downloaded file)
2.	Double-click the executable (.exe) file.
3.	Follow the instructions in the installation guide.
4.	When completing the setup, leave Run Arduino IDE ticked to launch the application, or launch it later from the Start Menu.
•	The installation time on a normal desktop computer is less than 5 min.

**Demo:**
•	The file named “Spike_encode_demo.ino” contains the demo code that perform the spike encoding function. To run this demo code, connect the Arduino Nano board use USB cable to a computer, and double click this file, and then configure the Board, Processor, and Port in the “Tools” of Arduino IDE software. Afterwards, compile this code by clicking “Verify” button and upload this code by clicking “Upload” button. After uploading the code, choose the Serial Monitor in the “Tools” of Arduino IDE software, and set the Baud rate as 250000, and click “Clear Output” button. Regarding the input dataset, the file “dataset_input.txt” contains a real dataset acquired from two sensors and this dataset can be used for testing the demo code. To allow a user-friendly demonstration, all the values of the input dataset have been added in the demo code.
•	The expected output of this demo code is displayed in the Serial Monitor, containing 4 types of sensory spikes that are automatically generated. The 4 sensory spikes are named as SA1, FA1, SA2, and FA2, with SA meaning Slow-Adapting Spike, and FA representing Fast-Adapting Spike. Regarding the output values, the file “dataset_output.txt” contains the expected output of the encoded spikes.
•	The expected run time for this demo code in a desktop computer is several seconds.

**Instructions for use:**
•	The file named “Spike_encode.ino” contains the actual code that perform the spike encoding function in a real-time and hardware-based manner. To run this code, the setups are the same as those for the demo code. In addition, sensor#1 and sensor#2 are connected to A0 and A1 port in the Arduino Nano board, and the two gates of device#1 are connected to A2 and A3 port in the Arduino Nano board, and the two gates of device#2 are connected to A4 and A5 port in the Arduino Nano board. The microcontroller, the flexible sensor, and the synaptic device comprise the neuromorphic sensory system.
