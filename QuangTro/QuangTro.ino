
int value;
#define Analog3 3
#define led 
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  value= analogRead(Analog3);
  Serial.print("Gia tri quang tro: ");
  Serial.println(value,DEC);
  delay(3000);
  
}
