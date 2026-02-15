1. Automatic Parking System (`Automatic_Parking_System.ino`)

Description

This project implements an automated parking management system using an Arduino. It monitors two parking slots using ultrasonic sensors and manages an entry gate controlled by a servo motor. The system provides real-time feedback via an I2C LCD screen and status LEDs for each slot.

Key Features

Slot Monitoring: Uses HC-SR04 ultrasonic sensors to detect if a vehicle is in Slot 1 or Slot 2.
Visual Indicators: Red and Green LEDs for each slot indicate "Occupied" (Red) or "Free" (Green) status.
Automated Entry: The entry gate opens automatically if a car is detected and at least one slot is available.
Capacity Management: If both slots are taken, the LCD displays "Parking Full," and the gate remains closed.
LCD Interface: Displays the real-time status of each parking slot.

Hardware Components

Arduino Board.
I2C LCD Display (0x27 address).
2x Servo Motors (Gate Control and Ultrasonic Rotation).
3x Ultrasonic Sensors (Entry, Slot 1, and Slot 2).
4x LEDs (2 Red, 2 Green).


2. LED Blinking Sequence (`Blinking_Assignment.ino`)

Description

This sketch demonstrates various LED animation patterns using an array of eight LEDs. It is designed to showcase control logic for multiple outputs, including conditional blinking and sequential "chase" effects.

Animation Patterns
Synchronous Blinking: All 8 LEDs blink on and off simultaneously.
Odd/Even Blinking: Alternates between blinking LEDs on odd-numbered pins and even-numbered pins.
Sequential Chase: LEDs light up one by one in a forward sequence, followed by a reverse sequence.

Hardware Setup
LEDs: 8 LEDs connected to digital pins 3, 4, 5, 6, 7, 8, 9, and 10.


3. ESP32 Firebase Integration (`Firebase1.ino`)

Description

This project connects an ESP32 microcontroller to the Firebase Realtime Database. It demonstrates how to authenticate a user and perform asynchronous data uploads of various data types.

Key Features

Wi-Fi Connectivity: Establishes a secure connection to a local wireless network.
User Authentication: Uses Email and Password authentication to interact with the Firebase project.
Periodic Data Logging: Sends an incrementing integer, a unique string, and a random float value to the database every 10 seconds.
Asynchronous Processing: Utilizes callback functions to handle and log success, errors, or debug information without blocking the main loop.

Libraries Used
 
`WiFi.h`: For network connectivity.

`FirebaseClient.h`: For communicating with the Firebase Realtime Database.


4. HTTP_miniproj_1 (Currency Rate Checker)

Objective: 
To create a device that fetches a real-time currency exchange rate from an online API and displays it on an LCD screen. 

Requirements and Implementation:

Hardware: 
An ESP32 was connected to an I2C-based LCD (e.g., 16x2).

GET Request: 
The ESP32 was programmed to act as an HTTP client, sending a GET request to a free exchange rate API (such as Exchangerate-API).

JSON Parsing: 
The API's JSON response, containing the latest exchange rates, was parsed using the ArduinoJson library.

Data Extraction:
The specific field for the USD to XAF conversion was extracted from the parsed JSON.

Display: 
The calculated XAF equivalent of $1 was displayed on the LCD, providing a live and up-to-date rate.

Learning Goal: 
This project successfully demonstrated the process of fetching external data via a GET request, parsing a JSON response, and extracting specific information for a practical application.

Embedded Blend: 
The ESP32's ability to connect to the internet and control a physical output (the LCD) was highlighted by showing live financial data on an embedded device. 


5. HTTP_miniproj_2 (Daily Quote Fetcher)

Objective:
To build a device that fetches a daily "quote of the day" from an API and displays it on an LCD screen, with a physical button to trigger a new fetch.

Requirements and Implementation:

Hardware: 
An ESP32, an I2C LCD, and a push button were connected.

API Integration: 
A GET request was made to a quote API (like ZenQuotes) to receive a random quote.

JSON Handling: 
The JSON text was parsed, and the quote and author were extracted.

Button Interaction: 
A push button was configured to act as a user input. A simple debounce function was implemented to ensure reliable presses.

Dynamic Display: 
A function was created to display the fetched quote on the LCD. The final implementation made the quote scroll across the screen to accommodate longer text.

Learning Goal: 
This project focused on handling string-based API responses, parsing simple JSON, and using a physical input (the button) to control the device's functionality.

Embedded Blend: 
This project integrated user input (the button) with a network request and a display, creating a complete and interactive embedded system. 


6. HTTP_miniproj_3 (ESP32 Weather-Triggered LED)

Objective: 
To use an ESP32 to fetch a weather forecast and control different colored LEDs based on the conditions. 

Requirements and Implementation:

Hardware: 
An ESP32 was connected to a blue LED (for rain) and a yellow LED (for sun), each with a current-limiting resistor.

API Request: 
A GET request was sent to the Open-Meteo API to retrieve the weather code for a specific location.

JSON Parsing and Data Mapping: 
The ArduinoJson library parsed the response, and the weather code was mapped to predefined conditions (e.g., rain, clear sky).

Actuator Control: 
digitalWrite() was used to control the state of the LEDs. A "rain" forecast turned on the blue LED, a "sunny" forecast turned on the yellow LED, and other conditions turned both off. Status updates were also displayed on an optional LCD.

Learning Goal: 
This project focused on mapping data from an API response to the states of physical outputs (actuators), a fundamental concept in embedded systems.

Embedded Blend: 
The project served as a simple, tangible weather notification system, where a physical output (LEDs) provided immediate feedback based on real-time external data. 

7. HTTP_miniproj_3 (Simple News Ticker)

Objective: 
To create a news ticker that fetches the latest headlines from a news API and displays them on an LCD screen, using a button to cycle through the headlines. 

Requirements and Implementation:

Hardware: 
An ESP32, an I2C LCD, and a push button were used.

API Request and Data Parsing: 
The ESP32 fetched the latest headlines from a news API (like Newsdata.io). The ArduinoJson library was used to parse the JSON response and extract the headlines.

Time Synchronization: 
A non-blocking timer using the millis() function was implemented to automatically fetch new headlines at regular intervals (e.g., every 30 seconds) without freezing the program.

Interactive Display: 
A push button was configured to allow the user to manually advance to the next headline.

Scrolling Display: 
The headlines were displayed on the LCD using a custom function that provided a smooth, left-to-right scrolling effect for longer headlines.

Learning Goal: 
This project refined skills in handling string-based responses, implementing a non-blocking timer for synchronized events, and managing user interaction.

Embedded Blend: 
The final product was a functional news-ticker device, demonstrating the ability to blend internet connectivity with a physical interface and display. 

8. HTTP_miniproj_3 (ESP32 Weather Client)

Objective: 
To create an ESP32 client that fetches and displays real-time weather information (temperature, humidity, forecast) on an LCD screen. 

Requirements and Implementation:

Hardware: 
An ESP32 was connected to an I2C LCD.

API Request: 
The ESP32 acted as an HTTP client, requesting current weather data from the Open-Meteo API for a specific location (e.g., Bafoussam, Cameroon).

JSON Parsing and Data Extraction: 
The temperature, humidity, and weather code were extracted from the API's JSON response.

Display on LCD: 
The extracted weather data was formatted and displayed on the LCD screen, providing easy-to-read, real-time information.

Robustness: 
The code included error handling for failed HTTP requests and JSON parsing, displaying informative messages on the LCD.

Learning Goal: 
This project provided a practical application of fetching and parsing structured data from an API and presenting it on a display, reinforcing the fundamental client-side concepts.

Embedded Blend: 
The final system was a standalone weather display, showcasing the ESP32's capability to transform raw internet data into a useful, physical device. 


9. I2C Interface & Parking System Sketches (I2C.ino)
Description
This file serves as a development "sketchpad" for various I2C-based projects. It includes logic for temperature monitoring and an automated parking system using ultrasonic sensors and servos.
Key Features
Temperature Monitoring: Reads data from an analog temperature sensor and displays it on an I2C LCD.
Parking Logic: Multiple versions of code to monitor parking slots, update occupancy status on an LCD, and control an entry gate servo.
Hysteresis Implementation: Includes logic to prevent "bouncing" between free and occupied statuses.
Hardware Components
Arduino Board.
I2C LCD (16x2).
HC-SR04 Ultrasonic Sensors.
Servo Motors.
LEDs (Red/Green).
10. ESP32 Access System (keypad.ino)
Description
A secure access control system built for the ESP32. It uses a 4x4 matrix keypad for pin entry and a servo motor to actuate a physical locking mechanism.
Key Features
Password Authentication: Validates a 4-digit PIN (default "1245").


Administrative Control: Allows password updates and remote unlocking via Serial commands (e.g., setpass=XXXX, unlock).


Audio-Visual Feedback: Uses an I2C LCD to show status and a buzzer to provide unique tones for granted or denied access.


Auto-Lock: Automatically returns the servo to the locked position 5 seconds after access is granted.


Hardware Components
ESP32 Development Board.
4x4 Matrix Keypad.
I2C LCD.
Servo Motor (Lock).
Active/Passive Buzzer.
11. Smart Volume Controller (serial_volume_control_button_with_lcd1.ino)
Description
A user-friendly volume control interface that allows adjustments via physical buttons or Serial input. It includes a visual LED "meter" and persists settings across power cycles.
Key Features
Dual Control: Adjust volume using physical UP/DOWN buttons or by sending integer values (0–5) over the Serial monitor.


Visual Meter: A set of 5 LEDs lights up sequentially to represent the volume level.


Persistent Memory: Uses EEPROM to save the current volume level, ensuring it remains the same after a restart.


LCD Display: Shows current volume percentage and maximum limits.


Hardware Components
Arduino Board.
I2C LCD.
2x Push Buttons.
5x LEDs with resistors.
12. Smart Home Light Control (Smart_home_1.ino)
Description
A streamlined IoT project demonstrating the basics of remote device control using the ESP32 and Firebase Realtime Database.
Key Features
Cloud Control: Polls a specific Firebase path (/smartHome/lightCommand) for updates.


Remote Toggle: Responds to "LIGHT ON" and "LIGHT OFF" commands from the database to control a connected LED.


WiFi Integration: Connects to a specified wireless network for cloud communication.


13. Advanced Smart Home System (Smart_home_2.ino)
Description
An expanded IoT system that integrates environmental monitoring with remote and automated appliance control.
Key Features
Climate Monitoring: Reads temperature and humidity from a DHT11 sensor and uploads data to Firebase.


Multi-Mode Fan Control: Supports three modes: "FAN ON", "FAN OFF", and "AUTO" (where the fan activates if the temperature exceeds 30°C).


Real-time Dashboard: Displays current temperature, humidity, and fan status on a local I2C LCD.


Hardware Components
ESP32 Board.
DHT11 Temperature/Humidity Sensor.
I2C LCD (16x2).
Relay Module (for Fan).
LED (for Light).
14. Digital Potentiometer Control (SPI.ino)
Description A technical example showcasing the use of the SPI (Serial Peripheral Interface) protocol to control an AD5206 6-channel digital potentiometer.

Key Features
Multi-Channel Control: Individually addresses all six channels of the AD5206.


Resistance Cycling: Automatically cycles the resistance of each wiper from minimum to maximum and back, creating a fading effect on connected LEDs.


15. Classroom Fan Web Controller (miniProject4.ino)
Description
A localized web-based controller designed to manage classroom fans. This project turns the ESP32 into a standalone Access Point (AP).
Key Features
Local WiFi Network: Creates its own WiFi network ("ESP32-Access-Point"), allowing control without an internet connection.


Web Interface: Serves a mobile-friendly HTML page with buttons to toggle the fan.


Status Indicators: Uses a Green LED to indicate the fan is running and a Red LED to indicate it is off.


16. Multi-GPIO Web Server (webServer1.ino)
Description
A versatile ESP32 web server project for controlling multiple generic outputs via a browser.
Key Features
Access Point Mode: Operates as a standalone hotspot.


Dual Channel Control: Provides independent ON/OFF control for GPIO pins 26 and 27 through a single web interface.


Dynamic UI: The web page updates in real-time to show the current state of each pin.


17. NTP-Synced Fan Web Server (webServerSTA1.ino)
Description
A sophisticated fan controller that connects to an existing network (Station Mode) and provides logging capabilities using real-world time.
Key Features
Time Synchronization: Connects to an NTP server (pool.ntp.org) to fetch the current date and time.


Activity Logging: Records the exact time and date whenever the fan is toggled.


Integrated Web UI: Displays the current fan status and the "Last Toggled" timestamp on the web dashboard.
