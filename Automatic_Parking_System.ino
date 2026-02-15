// Automatic Parking System.

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LEDs for slot1
#define led1redPin 13
#define led1greenPin 12

// LEDs for slot2
#define led2redPin 11
#define led2greenPin 10

LiquidCrystal_I2C lcd( 0x27, 128, 32);

// --- Ultrasonic Sensor Pins ---
// Sensor for the entrance gate
const int trigPinEntry = 4;
const int echoPinEntry = 3;

// Sensor for parking slot 1
const int trigPinSlot1 = 9;
const int echoPinSlot1 = 8;

// Sensor for parking slot 2
const int trigPinSlot2 = 7;
const int echoPinSlot2 = 6;

// --- Servo Motor Pin 1---
const int servoPin1 = 5;
Servo tollGate;

// --- Servo Motor Pin 2---
const int servoPin2 = 2;
Servo Ultrarotate;


// --- Thresholds and Variables ---
// Adjust these distance thresholds based on your Tinkercad setup
const int entryThreshold = 150;
const int exitThreshold = 150;
const int slotThreshold = 150;    
const int gateOpenAngle = 90;    
const int gateClosedAngle = 0;  


int occupiedSlots = 0;
bool slot1Occupied = false;
bool slot2Occupied = false;

// --- Ultrasonic Sensor Function ---
// A reusable function to measure distance
long getDistance(int trigPin, int echoPin) {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Send a 10-microsecond pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);
  // Convert the time into a distance
  return duration / 58;
}


void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello, You're welcome!");
  lcd.setCursor(0,1);
  lcd.print("To SEED PARKING");
  delay(1000);
  
  Serial.begin(9600);
  // pinMode(trig, OUTPUT); 
  // digitalWrite(trig, LOW); 
  // delayMicroseconds(2);  
  // pinMode(echo, INPUT); 
  // delay(6000); 
  
  // Set up LED pins
  pinMode(led1redPin, OUTPUT);
  pinMode(led1greenPin, OUTPUT);
  
  pinMode(led2redPin, OUTPUT);
  pinMode(led2greenPin, OUTPUT);
  
  // Set up ultrasonic sensor pins
  pinMode(trigPinEntry, OUTPUT);
  pinMode(echoPinEntry, INPUT);
  pinMode(trigPinSlot1, OUTPUT);
  pinMode(echoPinSlot1, INPUT);
  pinMode(trigPinSlot2, OUTPUT);
  pinMode(echoPinSlot2, INPUT);
  
  // Set up servo motor
  tollGate.attach(servoPin1);
  tollGate.write(gateClosedAngle);

  // Set up servo motor
  Ultrarotate.attach(servoPin2);
  Ultrarotate.write(0);
  
}

 void updateLCD() {
   lcd.clear();
   lcd.setCursor(0, 0); // Column 0, Row 0
   lcd.print("Slot1: ");
   if (slot1Occupied) {
     lcd.print("Occupied");
   } else {
     lcd.print("Free");
   }

   lcd.setCursor(0, 1); // Column 0, Row 1
   lcd.print("Slot2: ");
   if (slot2Occupied) {
     lcd.print("Occupied");
   } else {
     lcd.print("Free");
   }
 }

void loop() {
  // Read distances from all sensors
  long distanceSlot1 = getDistance(trigPinSlot1, echoPinSlot1);
  long distanceSlot2 = getDistance(trigPinSlot2, echoPinSlot2);

  // Update slot occupancy status
  slot1Occupied = (distanceSlot1 < slotThreshold);
  slot2Occupied = (distanceSlot2 < slotThreshold);
  
  // Update the count of occupied slots
  occupiedSlots = (slot1Occupied ? 1 : 0) + (slot2Occupied ? 1 : 0);

  // Update the LEDs of occupied slots
  if (slot1Occupied)
  {
    digitalWrite(led1redPin, HIGH);
    digitalWrite(led1greenPin, LOW);
  }
  else
  {
  	digitalWrite(led1greenPin, HIGH);
    digitalWrite(led1redPin, LOW);
  }
  if (slot2Occupied)
  {
    digitalWrite(led2redPin, HIGH);
    digitalWrite(led2greenPin, LOW);
  }
  else
  {
  	digitalWrite(led2greenPin, HIGH);
    digitalWrite(led2redPin, LOW);
  }
  
  // Update LCD display
  updateLCD();
  delay(1000);

  // Logic for the toll gate
  //int lastPosition = Ultrarotate.read();
  
  //for (int pos = 0; pos <= 90; pos += 10)
   //{
    Ultrarotate.write(0);              
    delay(500); 
    long distanceEntry = getDistance(trigPinEntry, echoPinEntry);
   // if (lastPosition == 0)
    //{
      if (distanceEntry < entryThreshold) {
        Serial.println("Car at entrance detected.");
        if (occupiedSlots < 2) { // If there is at least one free slot
          Serial.println("Gate opening...");
          tollGate.write(gateOpenAngle);
          delay(1000); // Keep gate open for a few seconds
        } else {
          Serial.println("Parking full. Gate remains closed.");
          // Optionally display a "Parking Full" message on LCD
          tollGate.write(gateClosedAngle);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Parking Full");
          lcd.setCursor(0, 1);
          lcd.print("No Entry");
          delay(1000);
        }
      } 
      else 
      {
      // If no car is at the entrance, keep the gate closed
      tollGate.write(gateClosedAngle);
      }
  
    Ultrarotate.write(90);              
    delay(500); 
    distanceEntry = getDistance(trigPinEntry, echoPinEntry);
    //else if (lastPosition == 90)
    //{
      float distanceExit = distanceEntry;
        
        if (distanceExit < exitThreshold) {
          Serial.println("Car at entrance detected.");
          Serial.println("Gate opening...");
          tollGate.write(gateOpenAngle);
          delay(1000); // Keep gate open for a few seconds
        } 
        else 
        {
          Serial.println("No car detected");
          tollGate.write(gateClosedAngle);
          delay(1000);
        }
   // }
    //else
    //{
      //tollGate.write(gateClosedAngle);
    //}
  //}
  //for (int pos = 90; pos >= 0; pos -= 10) { 
    //Ultrarotate.write(pos);              
    //delay(15); 
    
    //if (lastPosition == 90)
 /*   //{
  	Ultrarotate.write(90);              
    delay(500); 
    long distanceEntry = getDistance(trigPinEntry, echoPinEntry);
  
      float distanceExit = distanceEntry;
        
        if (distanceExit < exitThreshold) {
          Serial.println("Car at entrance detected.");
          Serial.println("Gate opening...");
          tollGate.write(gateOpenAngle);
          delay(1000); // Keep gate open for a few seconds
        } 
        else 
        {
          Serial.println("No car detected");
          tollGate.write(gateClosedAngle);
          delay(1000);
        }
   // }
   // else if (lastPosition == 0)
   // {
  	Ultrarotate.write(0);              
    delay(500); 
    long distanceEntry = getDistance(trigPinEntry, echoPinEntry);
  
      if (distanceEntry < entryThreshold)
      {
        Serial.println("Car at entrance detected.");
        if (occupiedSlots < 2) { // If there is at least one free slot
          Serial.println("Gate opening...");
          tollGate.write(gateOpenAngle);
          delay(1000); // Keep gate open for a few seconds
        } 
        else 
        {
          Serial.println("Parking full. Gate remains closed.");
          // Optionally display a "Parking Full" message on LCD
          tollGate.write(gateClosedAngle);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Parking Full");
          lcd.setCursor(0, 1);
          lcd.print("No Entry");
          delay(1000);
        }
      } 
      else 
      {
      // If no car is at the entrance, keep the gate closed
      tollGate.write(gateClosedAngle);
      }
   // }
   // else
   // {
   //   tollGate.write(gateClosedAngle);
    //}
//}*/

  delay(500); // Wait for half a second before repeating the loop
}


//void loop()
//{
  /*
  //Entry
  digitalWrite(trigPinEntry, HIGH);     
  delayMicroseconds(10); 
  digitalWrite(trigPinEntry, LOW);     
  int durationEntry = pulseIn(echoPinEntry, HIGH); 
  
  //slot1
  digitalWrite(trigPinSlot1, HIGH);     
  delayMicroseconds(10); 
  digitalWrite(trigPinSlot1, LOW);     
  int durationSlot1 = pulseIn(echoPinSlot1, HIGH);
  
  //slot2
  digitalWrite(trigPinSlot1, HIGH);     
  delayMicroseconds(10); 
  digitalWrite(trigPinSlot1, LOW);     
  int durationSlot2 = pulseIn(echoPinSlot1, HIGH);
  
  if(durationEntry >= 38000)
  { 
    Serial.print("Out range");   
  }  
  else{ 
    float distanceEntry = durationEntry / 58;
    Serial.print("DistanceEntry:");
    Serial.println(distanceEntry);     
    Serial.print("cm");
  
    if (distanceEntry <= 150)
    {
      if(durationSlot1 >= 38000)
      { 
    Serial.print("Out range");   
      }
      else
      {
      	float distanceSlot1 = durationSlot1 / 58;
        Serial.print("DistanceSlot1:");
        Serial.println(distanceSlot1);     
        Serial.print("cm");
        
        if (distanceSlot1 <= 150)
        {
          
        
        }
      }
      tollGate.write(gateOpenAngle); // Move to 90 degrees
      delay(1000);       // Wait for 1 second
    } 
    else 
    {
      tollGate.write(gateClosedAngle);
      delay(1000);
    }
  }  
  delay(1000);*/
  
  
//}