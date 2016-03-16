#define chanphat 7
#define chanthu 8
int thoigian,khoangcach;
#include<stdlib.h>
#include <string.h>
int count=0;
char command;
String test;
#define led 4
boolean check=false;
#define Analog3 3
int count1;


void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(chanphat, OUTPUT);
  pinMode(chanthu, INPUT);
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
       check=true; 
       digitalWrite(led,HIGH); 
       test="";
      // convertIntToChar(12346);
       command='\0';
     }
     if(test=="TURN OFF")
     {  
       
        digitalWrite(led,LOW); 
        test="";
        //convertIntToChar(12345);
        command='\0';
     }
    
     //nếu như người dùng đã nhấn vào nút bắt đầu bên smartphone
     if(check==true)
     {
          //CẢM BIẾN SIÊU Âm
         //int  camBienSieuAm=CamBienSieuAm();
         //convertIntToChar(camBienSieuAm);
        
          //delay(500);
          digitalWrite(chanphat,HIGH);
          delayMicroseconds(1000);
          digitalWrite(chanphat,LOW);
          thoigian=pulseIn(chanthu,HIGH);
          khoangcach=0.0344*(thoigian/2);
          convertIntToChar(khoangcach);
      }
   
  
  delay(1000);
}

 //Hàm chuyển đổi số nguyên sang char và lấy độ dài  
void convertIntToChar(int number)
{
    count1=0;
    char NUMBER[5];
    itoa(number,NUMBER,10);
    
    //xác định độ dài của chuổi
    for(int i=0;i<sizeof(NUMBER);i++)
    {
            if(NUMBER[i]!='\0')
            {
               count1+=1; 
            }
     }
     
   //Gửi biến độ dài đi
  Serial.print(count1);   
  delay(50);
  //Gửi thông tin chuổi số đi
  for(int i=0;i<sizeof(NUMBER);i++)
    {
            if(NUMBER[i]!='\0')
            {
               Serial.print(NUMBER[i]);  
              delay(50); 
            }
     }
}

//Cảm biến siêu âm
int CamBienSieuAm()
{
  int KHOANG_CACH;
digitalWrite(chanphat,HIGH);
delayMicroseconds(1000);
digitalWrite(chanphat,LOW);
thoigian=pulseIn(chanthu,HIGH);
KHOANG_CACH=0.0344*(thoigian/2);
return KHOANG_CACH;
delay(500); 
}
