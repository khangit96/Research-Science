int count=0;
char command;
String test="";
int water=0;
boolean checkWater=false;
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
       checkWater=true;
       delay(100);
     }
     //chuyển test về kiểu số nguyên
     if(checkWater==true)
     {
         water=test.toInt();
         count+=1;
         if(count==water)
         {
            digitalWrite(led,HIGH);
            Serial.print("O");
            checkWater=false;
            count=0;
         }
         else{
           digitalWrite(led,LOW); 
           Serial.print("F");
         }
         delay(3000);
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
