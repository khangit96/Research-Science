int count=0;
String test;
char command;
#define led 4
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop()
{ 
    while(Serial.available() > 0)
     {
       command = ((byte)Serial.read());
       test += command;
       
       delay(1);
     }
     if(test=="TURN ON")
     {
       digitalWrite(led,HIGH);
       Serial.print("S");
       test="";
      command='\0';
     }
     if(test=="TURN OFF")
     {
       digitalWrite(led,LOW); 
       Serial.print("D");
        test="";
        command='\0';
     }
 
  delay(1000);
}

