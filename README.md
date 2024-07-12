# ESP32_BLE_WEATHER
ESP32 Project for humidity and temperature measurement with BLE connectivity
BLE Weather Station

This Arduino project measures humidity and temperature and sends the data over BLE to the nRF Connect app using an ESP32's inbuilt BLE.

## Components

- ESP32 board
- DHT11 or DHT22 sensor (for humidity and temperature)

## Installation

1. **Clone the repository:**
   sh
   git clone https://github.com/being-satyam/ESP32_BLE_WEATHER.git         https://github.com/being-satyam/Krishi_Mitra.git
   cd BLE_Weather_Station
   
2. Open the Arduino IDE:

Download and install the Arduino IDE.
Set up the ESP32 in Arduino IDE:

Follow the instructions to set up ESP32 in the Arduino IDE from the ESP32 official guide.
Open the project:

Open the BLE_Weather.ino file in the Arduino IDE.
Install necessary libraries:

In the Arduino IDE, go to Sketch > Include Library > Manage Libraries.
Search for and install the following libraries:
->DHT sensor library
->Adafruit Unified Sensor
->ESP32 BLE Arduino

3. Upload the code:
Connect your ESP32 board to your computer.
Select the appropriate ESP32 board and port from the Tools menu.
Click the upload button to program the ESP32.
Usage

4.Power up the ESP32:

Connect your ESP32 to a power source.
Open the nRF Connect app:

Download the nRF Connect app from the Google Play Store or Apple App Store.
Scan for the BLE device and connect to it.

5. View the data:

Once connected, you will see the humidity and temperature data being updated in real-time on the app.
6. Demo Video
https://drive.google.com/file/d/13EsIrN_P-XaFQxG8OHh4GM5zmgdbsRU4/view?usp=sharing

7. Acknowledgments
Inspiration and code samples from various online resources and the Arduino community.
