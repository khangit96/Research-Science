
#include<stdlib.h>
#include <string.h>
int count=0;
int count1=0;
char command;
String test;
char NUMBER[5];
int number=13455;
int LENGTH;
#define led 4
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop()
{  
  //Hàm chuyển đổi số nguyên sang char và lấy độ dài
  if(count1==0){
      itoa(number,NUMBER,10);
     for(int i=0;i<sizeof(NUMBER);i++){
        if(NUMBER[i]!='\0'){
          count1+=1;
           
        }
     }      
 }
 
    while(Serial.available() > 0)
     {
       command = ((byte)Serial.read());
       test += command;
       delay(100);
     }
     if(test=="TURN ON")
     {
       
       digitalWrite(led,HIGH);
   Serial.print(count1);
       test="";
       command='\0';
     }
     if(test=="TURN OFF")
     {
       digitalWrite(led,LOW); 
         Serial.print(count1);
        test="";
        command='\0';
     }
 
  delay(1000);
}
