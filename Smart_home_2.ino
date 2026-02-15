// #include <WiFi.h>
// #include <FirebaseESP32.h>
// #include <DHT.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// // --- Wi-Fi & Firebase ---
// #define WIFI_SSID       "IoT"
// #define WIFI_PASSWORD   "*******1"
// #define FIREBASE_HOST   "smart-home-d58d5-default-rtdb.firebaseio.com"
// #define FIREBASE_AUTH   "BKJlxzdS0Vr3HWO6RWTajQA7BBzBEJ6NUq92GyPl"

// // --- Pins ---
// #define LED_PIN         18
// #define FAN_PIN         15
// #define DHTPIN          4
// #define DHTTYPE         DHT11

// // --- Objects ---
// FirebaseData   fbdo;
// FirebaseConfig config;
// FirebaseAuth   auth;
// DHT dht(DHTPIN, DHTTYPE);
// LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27

// void setup() {
//   Serial.begin(115200);
//   pinMode(LED_PIN, OUTPUT);
//   pinMode(FAN_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW);
//   digitalWrite(FAN_PIN, LOW);

//   dht.begin();
//   lcd.init();
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Smart Home Ready");

//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.println("\nWiFi Connected");

//   config.host = FIREBASE_HOST;
//   config.signer.tokens.legacy_token = FIREBASE_AUTH;
//   Firebase.begin(&config, &auth);
//   Firebase.reconnectWiFi(true);
// }

// void loop() {
//   // --- Read DHT11 ---
//   float temp = dht.readTemperature();
//   float hum  = dht.readHumidity();

//   if (isnan(temp) || isnan(hum)) {
//     Serial.println("Sensor error");
//     lcd.setCursor(0, 1);
//     lcd.print("Sensor error     ");
//     delay(5000);
//     return;
//   }

//   // --- Upload sensor data ---
//   Firebase.setFloat(fbdo, "/smartHome/fan/temp", temp);
//   Firebase.setFloat(fbdo, "/smartHome/fan/humidity", hum);

//   // --- Fan control ---
//   String fanStatus = "OFF";
//   if (Firebase.getString(fbdo, "/smartHome/fan/command")) {
//     String cmd = fbdo.stringData();
//     Serial.println("Fan Command: " + cmd);

//     if (cmd == "FAN ON") {
//       digitalWrite(FAN_PIN, HIGH);
//       fanStatus = "ON ";
//     } else if (cmd == "FAN OFF") {
//       digitalWrite(FAN_PIN, LOW);
//       fanStatus = "OFF";
//     } else if (cmd == "AUTO") {
//       digitalWrite(FAN_PIN, temp > 30 ? HIGH : LOW);
//       fanStatus = (temp > 30) ? "AUTO ON" : "AUTO OFF";
//     }
//   } else {
//     Serial.println("Failed to read fan command: " + fbdo.errorReason());
//   }

//   // --- Light control ---
//   if (Firebase.getString(fbdo, "/smartHome/lightCommand")) {
//     String lightCmd = fbdo.stringData();
//     Serial.println("Light Command: " + lightCmd);

//     if (lightCmd == "LIGHT ON") {
//       digitalWrite(LED_PIN, HIGH);
//     } else if (lightCmd == "LIGHT OFF") {
//       digitalWrite(LED_PIN, LOW);
//     }
//   } else {
//     Serial.println("Failed to read light command: " + fbdo.errorReason());
//   }

//   // --- Update LCD ---
//   lcd.setCursor(0, 0);
//   lcd.printf("T:%.1fC H:%.0f%%", temp, hum);
//   lcd.setCursor(0, 1);
//   lcd.print("Fan: ");
//   lcd.print(fanStatus);
//   lcd.print("       ");

//   delay(5000); // Update every 5 seconds
// }






#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Wi-Fi & Firebase ---
#define WIFI_SSID       "IoT"
#define WIFI_PASSWORD   "*******1"
#define FIREBASE_HOST   "smart-home-d58d5-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH   "BKJlxzdS0Vr3HWO6RWTajQA7BBzBEJ6NUq92GyPl"

// --- Pins ---
#define LED_PIN         18
#define FAN_PIN         15
#define DHTPIN          4
#define DHTTYPE         DHT11

// --- Objects ---
FirebaseData   fbdo;
FirebaseData   streamData; // Dedicated FirebaseData object for streaming
FirebaseConfig config;
FirebaseAuth   auth;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27

// --- Timing Variables ---
unsigned long previousMillis = 0;
const long interval = 2000; // Update sensor data and LCD every 2 seconds
String currentFanStatus = "OFF";

// --- Function Prototypes ---
void streamCallback(StreamData data);
void streamTimeoutCallback(bool timeout);
void handleFanControl(String command);
void handleLightControl(String command);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Home Ready");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // --- Start Streaming ---
  // Listen for real-time changes at the root of smartHome
  if (!Firebase.beginStream(streamData, "/smartHome")) {
    Serial.println("Reason: " + streamData.errorReason());
  }
  Firebase.setStreamCallback(streamData, streamCallback, streamTimeoutCallback);
}

void loop() {
  // Check if it's time to read sensors and update Firebase/LCD (non-blocking)
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // --- Read DHT11 ---
    float temp = dht.readTemperature();
    float hum  = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("Sensor error");
      lcd.setCursor(0, 1)FCRDWAQ  
      lcd.print("Sensor error     ");
      return; // Skip update this cycle if sensor fails
    }

    // --- Upload sensor data ---
    // Use the non-blocking async functions for background data uploads
    Firebase.setFloatAsync(fbdo, "/smartHome/fan/temp", temp);
    Firebase.setFloatAsync(fbdo, "/smartHome/fan/humidity", hum);

    // If in AUTO mode, re-evaluate the fan state
    if (currentFanStatus.startsWith("AUTO")) {
        // Simple logic for auto mode handling
        if (temp > 30 && currentFanStatus != "AUTO ON") {
            handleFanControl("FAN ON");
            currentFanStatus = "AUTO ON";
        } else if (temp <= 30 && currentFanStatus != "AUTO OFF") {
             handleFanControl("FAN OFF");
             currentFanStatus = "AUTO OFF";
        }
    }

    // --- Update LCD ---
    lcd.setCursor(0, 0);
    lcd.printf("T:%.1fC H:%.0f%%", temp, hum);
    lcd.setCursor(0, 1);
    lcd.print("Fan: ");
    lcd.print(currentFanStatus);
    lcd.print("       ");
  }

  // The loop runs continuously and quickly, checking for stream events
  // in the background without blocking.
}

// Callback function to handle real-time database changes
void streamCallback(StreamData data) {
  Serial.printf("Stream updated at %s\n", data.dataPath());
  Serial.println("Event Type: " + data.eventType());

  // Check which command path was updated
  if (data.dataPath() == "/fan/command") {
    String cmd = data.stringData();
    handleFanControl(cmd);
  } else if (data.dataPath() == "/lightCommand") {
    String cmd = data.stringData();
    handleLightControl(cmd);
  }
}

// Handle fan logic in a separate function
void handleFanControl(String command) {
    Serial.println("Processing Fan Command: " + command);
    if (command == "FAN ON") {
      digitalWrite(FAN_PIN, HIGH);
      currentFanStatus = "ON ";
    } else if (command == "FAN OFF") {
      digitalWrite(FAN_PIN, LOW);
      currentFanStatus = "OFF";
    } else if (command == "AUTO") {
      // In auto mode, the temperature reading logic in loop() will handle the actual pin state
      currentFanStatus = "AUTO"; // Status is initially AUTO, loop() determines ON/OFF
    }
}

// Handle light logic in a separate function
void handleLightControl(String command) {
    Serial.println("Processing Light Command: " + command);
     if (command == "LIGHT ON") {
      digitalWrite(LED_PIN, HIGH);
    } else if (command == "LIGHT OFF") {
      digitalWrite(LED_PIN, LOW);
    }
}

void streamTimeoutCallback(bool timeout) {
  if (timeout) {
    Serial.println("Stream timeout, re-establishing...");
  }
}
