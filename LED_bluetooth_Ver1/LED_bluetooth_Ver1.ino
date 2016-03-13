int count=0;
char command;
String test;
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
       
       delay(100);
     }
     if(test=="TURN ON")
     {
       digitalWrite(led,HIGH);
       Serial.print("O");
       test="";
       command='\0';
     }
     if(test=="TURN OFF")
     {
       digitalWrite(led,LOW); 
       Serial.print("F");
        test="";
        command='\0';
     }
 
  delay(1000);
}
