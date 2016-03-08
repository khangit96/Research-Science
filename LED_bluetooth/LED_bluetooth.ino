char command;
String string;
boolean ledon = false;
#define led 4
#define led2 8
 void setup()
 {
     Serial.begin(9600);
     pinMode(led, OUTPUT);
     pinMode(led2, OUTPUT);
 }
 void loop()
 {
     if (Serial.available() > 0)
     {
       string = "";
     
     }
     while(Serial.available() > 0)
     {
       command = ((byte)Serial.read());
       if(command == ':')
       {
       break;
       }
       else
       {
       string += command;
       }
       delay(1);
     }
     if(string == "TURN ON")
      {
       ledOn();
        digitalWrite(led2,HIGH);
       ledon = true;
       Serial.println(string);
     }
     if(string =="TURN OFF")
     {
       ledOff();
       digitalWrite(led2,LOW);
       ledon = false;
       Serial.println(string); //debug
     }
    /* if ((string.toInt()>=0)&&(string.toInt()<=255))
     {
       if (ledon==true)
       {
       analogWrite(led, string.toInt());
       Serial.println(string); //debug
       delay(10);
       }
     }
    */
      delay(1000);
  }
    
 void ledOn()
  {
    digitalWrite(led,HIGH);
   // delay(10);
  }
 void ledOff()
  {
    digitalWrite(led,LOW);
   // delay(10);
}
