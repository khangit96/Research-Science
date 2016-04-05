#define chanphat 7
#define chanthu 8
int thoigian,khoangcach;
#include<stdlib.h>
#include <string.h>
int count=0;
char command;
String test;
//#define led 4
boolean check=false;
#define Analog3 3

int count1;
int dem=0;

void setup() {
  Serial.begin(9600);
//  pinMode(led,OUTPUT);
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
     //  digitalWrite(led,HIGH); 
       test="";
    //   convertIntToChar(12346);
       command='\0';
     }
     if(test=="TURN OFF")
     {  
       
    //    digitalWrite(led,LOW); 
        test="";
        convertIntToChar(12345);
        command='\0';
     }
     //nếu như người dùng đã nhấn vào nút bắt đầu bên smartphone
     if(check==true)
     {
          //CẢM BIẾN SIÊU Âm
   
         digitalWrite(chanphat,HIGH);
         delayMicroseconds(1000);
         digitalWrite(chanphat,LOW);
         int thoi_gian=pulseIn(chanthu,HIGH);
         int khoang_cach=0.0344*(thoi_gian/2);
         if(khoang_cach<10)
         {
             Serial.print(khoang_cach);
         }
         else if(khoang_cach==10)
         {
           Serial.print("a");
         }
          else if(khoang_cach==11)
         {
           Serial.print("b");
         }
          else if(khoang_cach==12)
         {
              Serial.print("c");
         }
          else if(khoang_cach==13)
         {
              Serial.print("d");
         }
           else if(khoang_cach==14)
         {
              Serial.print("e");
         }
           else if(khoang_cach==15)
         {
              Serial.print("f");
         }
           else if(khoang_cach==16)
         {
              Serial.print("g");
         }
         else if(khoang_cach==17)
         {
             Serial.print("h");
         }
       
       
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


