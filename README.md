

# Air Quality Monitoring System with ESP32

A compact, real-time **Air Quality Monitoring IoT device** using **ESP32**, **DHT11**, **MQ138 gas sensor**, **SSD1306 OLED Display**, and **Blynk IoT platform**.

> Built for smart environments to monitor **temperature**, **humidity**, and **air quality** (AQI estimation) — all visualized locally and remotely.

---

## Features

* Wi-Fi connected ESP32-based system
* Real-time temperature and humidity monitoring using DHT11
* Air quality estimation using MQ138 gas sensor
* OLED display for live sensor readouts
* Blynk IoT integration for remote monitoring via smartphone
* Automatic retry on Wi-Fi failure with graceful reboot
* Ideal for indoor air quality analysis, environmental monitoring, and smart home systems

---



## Hardware Requirements

| Component          | Description                   |
| ------------------ | ----------------------------- |
| ESP32 Dev Board    | Wi-Fi enabled microcontroller |
| DHT11 Sensor       | For temperature and humidity  |
| MQ138 Gas Sensor   | For VOC/air quality detection |
| SSD1306 OLED       | 128x64 I2C display            |
| Breadboard + Wires | For prototyping               |

---

## Software Stack

* Arduino IDE
* Blynk Library (`BlynkSimpleEsp32.h`)
* U8g2 Library for OLED rendering
* DHT Library for sensor readings
* ESP32 WiFi Library

---

## Blynk Setup

1. Create a new project in the Blynk app
2. Select **ESP32** as the device and note your **Auth Token**
3. Add three virtual widgets:

   * `V0` for Temperature
   * `V1` for Humidity
   * `V2` for AQI

---

## Code Configuration

Update the following lines in the code with your Wi-Fi and Blynk credentials:

```cpp
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"
```

---

## OLED Display Output

Example output on the OLED display:

```
Temp: 28.3 C
Humidity: 45.6 %
AQI: 123 (est)
```

---

## Sensor Data Mapping

* **Temperature & Humidity**: Read directly from DHT11
* **AQI (Air Quality Index)**: Estimated using analog values from the MQ138 sensor:

```cpp
float aqi = map(mq138_raw, 0, 4095, 0, 500);
```

Note: This is a simulated AQI for demonstration purposes.

---

## Wi-Fi Auto Recovery

If the device fails to connect to Wi-Fi:

1. A failure message is shown on the OLED
2. The device waits for 10 seconds
3. The ESP32 automatically restarts to retry the connection

---

## Getting Started

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/esp32-air-quality-monitor.git
   ```
2. Open the `.ino` file in the Arduino IDE
3. Install the required libraries:

   * U8g2
   * DHT Sensor Library
   * Blynk
4. Select the correct ESP32 board from Tools > Board
5. Upload the code to your ESP32 via USB



## Author

**Sourashis Das**
IoT Developer | Embedded Systems Engineer



