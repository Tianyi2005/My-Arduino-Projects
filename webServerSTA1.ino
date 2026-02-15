#include <WiFi.h>
#include <WebServer.h>
#include "time.h"

// Replace with your network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Define the pin connected to the IN pin of the relay module
const int relayPin = 2;

// NTP server to request time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600; // Your GMT offset in seconds (e.g., WAT is +1 hour = 3600)
const int   daylightOffset_sec = 0; // Daylight saving offset, 0 if not applicable

// Create WebServer object on port 80
WebServer server(80);

// Global variables to store fan state and time
String fanState = "OFF";
String lastToggleTime = "Never";

// Function to get current formatted time
String getFormattedTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "No time available";
  }
  char timeString[50]; // Use a larger buffer
  strftime(timeString, sizeof(timeString), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  return String(timeString);
}

// Function to build and send the HTML page
void sendHTML() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Fan Controller</title>";
  html += "<style>body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 8px; }";
  html += ".button-red { background-color: #f44336; }</style></head><body>";
  html += "<h1>Classroom Fan Controller</h1>";
  html += "<p>Fan State: <strong>" + fanState + "</strong></p>";
  html += "<p>Last Toggled: <strong>" + lastToggleTime + "</strong></p>";
  html += "<p><a href='/on'><button class='button'>Fan ON</button></a>";
  html += "<a href='/off'><button class='button button-red'>Fan OFF</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleRoot() {
  sendHTML();
}

void handleOn() {
  digitalWrite(relayPin, HIGH); // Adjust HIGH/LOW based on relay module logic
  fanState = "ON";
  lastToggleTime = getFormattedTime();
  Serial.println("Fan turned ON at: " + lastToggleTime);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Redirecting...");
}

void handleOff() {
  digitalWrite(relayPin, LOW); // Adjust HIGH/LOW based on relay module logic
  fanState = "OFF";
  lastToggleTime = getFormattedTime();
  Serial.println("Fan turned OFF at: " + lastToggleTime);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Redirecting...");
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure fan starts off

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize time from NTP server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Define server routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  // Start server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}