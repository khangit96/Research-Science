#include "SIM900.h"
#include <SoftwareSerial.h>
SoftwareSerial SIM900(2,3);
#include "sms.h"
SMSGSM sms;
#define Analog 1
#define Digital 4
#define Led 12
boolean started=false;
char smsbuffer[160];
char n[20]="+84971982955";
int giatriAnalog, giatriDigital;
char pos;
char *p;
char *ledOn;
char *ledOff;
void setup() {
  Serial.begin(9600);
  pinMode(Digital,INPUT);
  pinMode(Led,OUTPUT);
  Serial.println("GSM Shield testing.");
  if (gsm.begin(2400)) {
          Serial.println("\nstatus=READY");
     } else Serial.println("\nstatus=IDLE");
};
void loop() {
giatriAnalog=analogRead(Analog);
giatriDigital=digitalRead(Digital);
/*if (giatriAnalog>500)
{
  digitalWrite(Led,HIGH);
}
else if(giatriAnalog<=500)
{
  digitalWrite(Led,LOW);
}*/
pos=sms.IsSMSPresent(SMS_UNREAD);
Serial.println((int)pos);
if((int)pos>0&&(int)pos<=20)
{
  Serial.print("POS=");
  Serial.println((int)pos);
  smsbuffer[0]='\0';
  sms.GetSMS((int)pos,n,20,smsbuffer,160);
    p=strstr(smsbuffer,"LEDON");
 // p=strstr(smsbuffer,"LEDON");
 ledOn=strstr(smsbuffer,"LEDON");
  ledOff=strstr(smsbuffer,"LEDOFF");
    if(p)
    {  
      digitalWrite(Led,HIGH);
    }
    else
   {
      p=strstr(smsbuffer,"LEDOFF");
      if(p){
        digitalWrite(Led,LOW);
      }
      
   }
}
delay (1000);
}
void doAm(){
}

