
int value;
#define Analog3 4
#define manChe 8
void setup()
{
  Serial.begin(9600);
  pinMode(manChe,OUTPUT);
}
void loop()
{
  value= analogRead(Analog3);
  Serial.print("Gia tri quang tro: ");
  Serial.println(value,DEC);
  if(value<=100)
  {
   
    digitalWrite(manChe,HIGH);
  }
  else
  {
    digitalWrite(manChe,LOW);
  }
  delay(1000);
  
}
