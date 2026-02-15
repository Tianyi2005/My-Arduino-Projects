#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 128, 32);

const int UP_BUTTON_PIN = 8;
const int DOWN_BUTTON_PIN = 7;
const int LED_PIN[] = {13, 12, 11, 10, 9};
const int LED_num = 5;
const int EEPROM_ADDR = 0;

int LED_count = 0;
int newVolume;
int oldVolume = 0;
int max = 5;
int min = 0;

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello Mr.Tchasso");
  lcd.setCursor(0, 1);
  lcd.print("We are the best");

  Serial.begin(9600);
  while (!Serial);

  Serial.println("Enter volume level");

  // Restore volume from EEPROM
  LED_count = EEPROM.read(EEPROM_ADDR);
  if (LED_count < min || LED_count > max) {
    LED_count = min; // fallback if EEPROM value is invalid
  }
  newVolume = LED_count * 20;
  oldVolume = newVolume;

  for (int i = 0; i < LED_num; i++) {
    pinMode(LED_PIN[i], OUTPUT);
  }
  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
}

void loop()
{
  int UpbuttonState = digitalRead(UP_BUTTON_PIN);
  int DownbuttonState = digitalRead(DOWN_BUTTON_PIN);

  if (UpbuttonState == HIGH)
  {
    delay(300);
    if (LED_count < max)
    {
      LED_count++;
      newVolume = LED_count * 20;
    }
  }

  if (Serial.available())
  {
    int level = Serial.parseInt();
    if (level >= 0)
    {
      if (level <= max)
      {
        LED_count = level;
        newVolume = LED_count * 20;
      }
      else
      {
        LED_count = max;
        newVolume = max * 20;
      }
    }
    else
    {
      LED_count = min;
      newVolume = min * 20;
    }
  }

  if (DownbuttonState == HIGH)
  {
    delay(300);
    if (LED_count > min)
    {
      LED_count--;
      newVolume = LED_count * 20;
    }
  }

  for (int i = 0; i < LED_num; i++)
  {
    digitalWrite(LED_PIN[i], i < LED_count ? HIGH : LOW);
  }

  if (newVolume != oldVolume)
  {
    Serial.print("The volume is ");
    Serial.println(newVolume);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Volume is ");
    lcd.print(newVolume);
    lcd.setCursor(0, 1);
    lcd.print("MaxLED is 05");

    oldVolume = newVolume;

    // Save volume level to EEPROM
    EEPROM.update(EEPROM_ADDR, LED_count);
  }
}