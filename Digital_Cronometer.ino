#include <TimeLib.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

int LED_PIN = 12;

int start_hour = 0;
int start_minute = 0;
String timer = "";
String hourInput = "";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  while (Serial.available() == 0) {

  }

  hourInput = Serial.readString();

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");



  for (int i = 0, counter = 1; i < hourInput.length(); i++, counter++) {

    timer += hourInput[i];

    if (counter == 2) {
      start_hour = timer.toInt();
      timer = "";
    }

    if (counter == 4)
    {
      start_minute = timer.toInt();
    }
  }

  Serial.println("Defined Hour: ");
  Serial.print(start_hour);
  Serial.print(":");
  Serial.print(start_minute);
}

void loop() {
  check_time();
}

void check_time() {
  // check if the current time matches with the defined time

  if (hour() == start_hour && minute() == start_minute)
  {
    Serial.println("ON");
    digitalWrite(LED_PIN, HIGH); // liga o led
  }
  else {
    Serial.println("OFF");
    digitalWrite(LED_PIN, LOW); // desliga o led
  }

}
