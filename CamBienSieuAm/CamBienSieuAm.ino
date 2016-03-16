

#define chanphat 7
#define chanthu 8
int led=12;
int thoigian,khoangcach;
void setup(){
  Serial.begin(9600);
  pinMode(chanphat, OUTPUT);
  pinMode(chanthu, INPUT);
  pinMode(led, OUTPUT);
}
void loop(){
digitalWrite(chanphat,HIGH);
delayMicroseconds(1000);
digitalWrite(chanphat,LOW);
thoigian=pulseIn(chanthu,HIGH);
khoangcach=0.0344*(thoigian/2);
Serial.print(khoangcach);
Serial.println("cm");
if(khoangcach>5&&khoangcach<15)
{
  digitalWrite(led,HIGH);
  delay(3000);
}
else
{
  digitalWrite(led,LOW);
}
delay(500);
}
