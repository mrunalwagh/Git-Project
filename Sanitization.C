
#define FilterLimit 5

const int trigPin = 3;
const int echoPin = 2;
const int motor = 1;
const int led = 4;
long duration;
int distanceCm, distanceInch;
int flag=0;
int Filter_Counter=0;
//int Filter_Counter_1=0;
int dist();
void setup()
{
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(motor, OUTPUT);
pinMode(led, OUTPUT);

}
void loop()
{
// delay(500);                          // No Need
     int dis=dist();
  if(dis>=0&&distanceCm<=186)
  {
    Filter_Counter++;                    //Increment the counter to check max cosecutive reading distanceCm
    if(Filter_Counter > FilterLimit)     // If continuously getting reading
    {
      Filter_Counter=0;
      if(flag==0)
       {
         flag=1;
         digitalWrite(motor, LOW);
           digitalWrite(led, HIGH);
         delay(3000);
         digitalWrite(motor, HIGH);
         digitalWrite(led, LOW);
        delay(1000);
       }

      }
      else
      {
        
        digitalWrite(motor, HIGH);
      
      }
    }
 
else if(distanceCm>=186)
{

    flag=0;

 
}
  else
  {
    
    Filter_Counter=0;                //if distanceCm gets wrong reading in less than 5 count
 
  }
 
}

int dist()
{
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;

return distanceCm;

} 