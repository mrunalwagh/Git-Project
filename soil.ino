//for more project visit www.blackkeyhole.com
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "HX711.h"

int analogPin = D0;
int moisture;
int percentage;
int map_low = 686;
int map_high = 350;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "**************************";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "**********";
char pass[] = "***************";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
 {
  moisture = analogRead(analogPin);
  Serial.print("Raw: ");
  Serial.print(moisture);

  percentage = map(moisture, map_low, map_high, 0, 100);

  Serial.print(" | Percentage: ");
  Serial.print(percentage);

  Serial.println("%");
  delay(1000);
  
 
    Blynk.virtualWrite(V3, percentage);
  Blynk.run();
}