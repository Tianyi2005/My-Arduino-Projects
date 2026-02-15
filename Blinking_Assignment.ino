int LED[] = {3, 4, 5, 6, 7, 8, 9, 10};

void setup() {
  // put your setup code here, to run once:
  for (int ledPin : LED)
  {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i = 0; i <= 10; i ++)
    {
      for (int ledPin : LED)
      {
        digitalWrite(ledPin, HIGH);
      }
      delay(100);
      for (int ledPin : LED)
      {
        digitalWrite(ledPin, LOW);
      }
      delay(100);
    }
  delay(200);

  for (int i = 0; i <= 10; i ++)
  {
    for (int ledPin : LED)
    {
      if (ledPin % 2 != 0)
        {
          digitalWrite(ledPin, HIGH);
        }
    }
    delay(100);
    for (int ledPin : LED)
    {
      if (ledPin % 2 != 0)
        {
          digitalWrite(ledPin, LOW);
        }
    }
    delay(100);
  }
  delay(200);

  for (int i = 0; i <= 10; i ++)
  {
    for (int ledPin : LED){
      if (ledPin % 2 == 0)
        {
          digitalWrite(ledPin, HIGH);
        }
    }
    delay(100);
    for (int ledPin : LED){
      if (ledPin % 2 == 0)
        {
          digitalWrite(ledPin, LOW);
        }
    }
    delay(100);
  }
  delay(200);

  for (int i = 0; i <= 10; i ++)
    {
      for (int ledPin : LED)
      {
        digitalWrite(ledPin, HIGH);
        delay(50);
        digitalWrite(ledPin, LOW);
        delay(50);
      }
      for (int i = 7; i >= 0; i --)
      {
        digitalWrite(LED[i], HIGH);
        delay(50);
        digitalWrite(LED[i], LOW);
        delay(50);
      }
    }
  delay(200);
}