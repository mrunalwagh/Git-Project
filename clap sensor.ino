
//Interfacing Sound Sensor and activation through clap
/* Sample code-1 */
/* Interfacing Sound sensor and counting knocks */

int sensorPin = A0;
int sensorValue;
int thresholdValue = 270;
int counter = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop()
{
  sensorValue = analogRead(sensorPin);

  if (sensorValue > thresholdValue)
  {
    counter = counter++;                 //count the knocks
    Serial.print("Sensor value is:");
    Serial.println(sensorValue);
    delay(200);
    Serial.print("Knock count is:");
    Serial.println(counter);
    delay(200);
    Serial.print(" ");
  }
}
                 