#include <WiFi.h>
#include <FirebaseESP32.h>

// --- Your details ---
#define WIFI_SSID "IoT"
#define WIFI_PASSWORD "*******1"

// #define WIFI_SSID "UBa Student WiFi"
// #define WIFI_PASSWORD "12345678"

// The HOST must NOT include "https://" or the trailing "/"
#define FIREBASE_HOST "smart-home-d58d5-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "BKJlxzdS0Vr3HWO6RWTajQA7BBzBEJ6NUq92GyPl"       

#define ledPin 18

FirebaseData fbdo;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getString(fbdo, "/smartHome/lightCommand")) {
    String command = fbdo.stringData();
    Serial.println("Command: " + command);

    if (command == "LIGHT ON") {
      digitalWrite(ledPin, HIGH);
    } else if (command == "LIGHT OFF") {
      digitalWrite(ledPin, LOW);
    }
  } else {
    Serial.println("Failed to read from Firebase: " + fbdo.errorReason());
  }

  delay(1000); // Poll every second
}