# Smart Library Seat Management System

This project is a **Smart Library Seat Management System** built using an **ESP32 microcontroller**. It monitors seat occupancy, environmental conditions (temperature, humidity, and light levels), and controls the brightness of a reading lamp based on ambient light. The data is sent to **Firebase Realtime Database** and can be visualized on a web or mobile interface.

---

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Hardware Requirements](#hardware-requirements)
4. [Software Requirements](#software-requirements)
5. [Setup Instructions](#setup-instructions)
6. [Code Explanation](#code-explanation)
7. [Troubleshooting](#troubleshooting)
8. [License](#license)

---

## Project Overview

The system uses an ESP32 to:
- Detect seat occupancy using an **ultrasonic sensor**.
- Monitor environmental conditions using a **DHT11 sensor** (temperature and humidity) and an **LDR** (light intensity).
- Control the brightness of a reading lamp using **PWM** based on the LDR value.
- Send real-time data to **Firebase Realtime Database**.
- Display data on a **web or mobile interface**.

---

## Features

- **Seat Occupancy Detection:** Uses an ultrasonic sensor to detect if a seat is occupied.
- **Environmental Monitoring:** Monitors temperature, humidity, and light levels.
- **Reading Lamp Control:** Adjusts the brightness of a reading lamp based on ambient light.
- **Real-Time Data Logging:** Sends data to Firebase for real-time monitoring.
- **Web/Mobile Interface:** Displays data on a dashboard for easy visualization.

---

## Hardware Requirements

- **ESP32 Development Board**
- **Ultrasonic Sensor (HC-SR04)**
- **DHT11 Sensor** (Temperature and Humidity)
- **LDR (Light Dependent Resistor)**
- **LEDs** (Red and Green for seat status)
- **Buzzer** (for alerts)
- **Reading Lamp** (with PWM control)
- **Resistors** (10kΩ for LDR, 220Ω for LEDs)
- **Breadboard and Jumper Wires**

---

## Software Requirements

- **Arduino IDE** (with ESP32 board support)
- **Firebase ESP Client Library** (for Firebase integration)
- **DHT Sensor Library** (for DHT11 sensor)
- **WiFi Library** (for Wi-Fi connectivity)
- **Web/Mobile Interface** (optional, for data visualization)

---

## Setup Instructions

1. **Hardware Setup:**
   - Connect the sensors and components to the ESP32.
   - Ensure all connections are secure and correct.

2. **Software Setup:**
   - Install the Arduino IDE and set up the ESP32 board support.
   - Install the required libraries (`Firebase ESP Client`, `DHT Sensor`, etc.).
   - Update the code with your Wi-Fi credentials, Firebase API key, and database URL.
   - Upload the code to the ESP32.

3. **Firebase Setup:**
   - Create a Firebase project and enable the Realtime Database.
   - Add your Firebase credentials to the code.

4. **Web/Mobile Interface:**
   - Use Firebase SDK to create a web or mobile app for data visualization.

---

## Code Explanation

The code is divided into the following sections:
- **Setup:** Initializes sensors, Wi-Fi, and Firebase.
- **Loop:** Reads sensor data, controls the reading lamp, and sends data to Firebase.
- **Helper Functions:** Includes functions for reading the ultrasonic sensor and debugging.

For detailed code explanation, refer to the comments in the [main code file](main.ino).

---

## Troubleshooting

If the system is not working as expected:
1. **Check Serial Monitor:** Ensure the baud rate is set to 115200.
2. **Verify Wi-Fi Connection:** Ensure the ESP32 is connected to Wi-Fi.
3. **Check Firebase Credentials:** Ensure the API key, database URL, and user credentials are correct.
4. **Debugging Prints:** Add `Serial.println()` statements to identify where the code fails.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
