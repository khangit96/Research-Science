String test="7:24:05";
String  strHour,strMinute,strSecond;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  // String test1=test.substring(0,3);
  //Serial.println(test1);
     strHour=test.substring(0,2);
     strMinute=test.substring(3,5);
     strSecond=test.substring(6,8);
     Serial.println(strHour);
     Serial.println(strMinute);
     Serial.println(strSecond);
  delay(1000);
}
