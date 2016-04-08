f//************************************************
#include <SoftwareSerial.h>
#include<stdlib.h>
#include <string.h>
SoftwareSerial SIM900(2,3);
#include "SIM900.h"
#include "sms.h"
SMSGSM sms;
char smsbuffer[10]; //biến tin nhắn nhận
char n[20]="+841695821150"; //SĐT người gửi - chủ
char pos; //biến vị trí tin nhắn trong sim
char *p; //biến lệnh của người gửi
char *p1;
char command;
String test;
int count=0;
boolean admin=false;
boolean bomm = false;

//********************************************
#define Analog 5
//*****************************************************
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11 
#define Bom 5
#define Van 6
DHT dht(DHTPIN, DHTTYPE);

//Mái che
int cuongDoAnhSang;
#define Analog3 4
#define manChe 8
//******************************************
int doAmDatCanTuoi=50;
void setup() 
{
 Serial.begin(9600);
 dht.begin();
 pinMode(Bom,OUTPUT);
 pinMode(Van,OUTPUT);
 digitalWrite(Bom,HIGH);
 digitalWrite(Van,HIGH);
 pinMode(manChe,OUTPUT);
 Serial.println("GSM Shield testing.");
  if (gsm.begin(2400)) 
      Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE"); 
}
//****************************************************
char *Reply(int Doamdat,int Doamkhongkhi,int Nhietdo)
{  
  char q[10],w[10],e[10];
  char DO_AM[30]="Do am dat: ";
  char DO_AM_KK[30]="Do am khong khi: ";
  char NHIET_DO[30]="Nhiet do: ";
  char result[160]="\0";
  itoa(Doamdat,q,10);//chuyển đổi doAm về chuổi DO_AM
  itoa(Doamkhongkhi,w,10);
  itoa(Nhietdo,e,10);
  strcat(result,DO_AM); //nối biến DO_AM vào sau biến result->kết quả là: "Độ ẩm: 123" 
  strcat(result,q);
  strcat(result,"%\n");//xuống dòng
  strcat(result,DO_AM_KK);
  strcat(result,w);
  strcat(result,"%\n");
  strcat(result,NHIET_DO);
  strcat(result,e);
  strcat(result,"*C");
  return result;
}
//Hàm trả tin nhắn cho người dùng khi không tưới đk
char *Reply1()
{  
  char content[50]="Khong the tuoi duoc vi dat con kho";
  return content;
}

/**********************************************************/
 int DO_AM_DAT()
{
  //int ana=analogRead(Analog);
  //int anal=ana-223;
 // int doAmDat=100-(anal/800);
 float ana=analogRead(Analog);
 float anal=ana-223;
 float analog=anal/800;
 float doAmDat=100-(analog*100);
 int test=(int)doAmDat;
  return test;
}
 int DO_AM_KHONG_KHI()
{
  int h=dht.readHumidity();
  return h;
}
 int NHIET_DO_KHONG_KHI()
{
  int t=dht.readTemperature();
  return t;
}
/*****************************************************************************VÒNG LẶP TRONG MẠCH*****************************************************************************/
void loop() 
{  
  
  
  
  int DO_AM_DAT1=DO_AM_DAT();
  Serial.println(DO_AM_DAT1);
  //Gửi dữ liệu về  độ ẩm đất,nhiệt độ không khí qua android
  
  
  //Bluetooth
   while(Serial.available() > 0)
     {
       command = ((byte)Serial.read());
       test += command;
       delay(100);
     
   }
     if(test=="TURN ON")
     {  
    //   admin=true;
       test="";
       command='\0';
       //Tiến hành tưới nước
       digitalWrite(Bom,LOW);
       digitalWrite(Van,LOW);
     
     }
      else if(test=="TURN OFF")
     {  
       test="";
       command='\0';
  
       //Tiến hành tắt máy bơm
       digitalWrite(Bom,HIGH);
       digitalWrite(Van,HIGH);       
     }
     
  //Đọc tin nhắn
  pos=sms.IsSMSPresent(SMS_UNREAD);
  Serial.println((int)pos);
  Serial.print("POS=");
  Serial.println((int)pos);
  smsbuffer[0]='\0';
  sms.GetSMS((int)pos,n,20,smsbuffer,160);
  p=strstr(smsbuffer,"STATUS");//tìm kiếm chuổi STATUS trong nội dung tin nhắn
    if(p)//nếu mà nội dung tin nhắn là STATUS 
    {
      sms.SendSMS(n, Reply(DO_AM_DAT(),DO_AM_KHONG_KHI(),NHIET_DO_KHONG_KHI()));
   
    }
    else//ngược lại nếu nội dung tin nhắn ko phải là STATUS
    {
        
          p=strstr(smsbuffer,"WATERING");//thì tìm kiếm chuổi WATERING trong nội dung tin nhắn
          p1=strstr(smsbuffer,"STOP");
          if(p)//nếu mà nội dung tin nhắn là WATERING 
          {     admin=true;
               //Bật máy bơm
              // BatMayBom();
           
           
          }
          else if(p1)//Ngược lại nếu nội dung tin nhắn là STOP
          {
               admin=false;
               //Tắt máy bơm
            //   TatMayBom();
               
          }
          else//ngược lại nếu nội dung tin nhắn ko phải là WATERING
          {
             
                p=strstr(smsbuffer,"CHANGE");//thì tìm kiếm chuổi CHANGE trong nội dung tin nhắn dùng để thay đổi nhiệt độ
              if(p)//nếu mà nội dung tin nhắn là CHANGE 
              {  
                int Length=sizeof(smsbuffer);//lấy độ dài của chuổi tin nhắn
                char changeNhietDo[163]="\0";//biến để lấy ra giá trị nhiệt độ từ nội dung tin nhắn thay đổi nhiệt độ
                strncpy(changeNhietDo,smsbuffer+7,2);//cắt giá trị nhiệt độ từ trong nội dung chuổi tin nhắn
                doAmDatCanTuoi=atoi(changeNhietDo);//gán doAmDatCanTuoi bằng với giá trị nhiệt độ cần thay đổi trong nội dung tin nhắn
                sms.SendSMS(n,"Da thay doi");
                delay(50);
              }
         }
          
    }
    
    //
    if (admin ==true)
    {
          count+=1;
          if(count==20)
          {
            Reset();
          } 
    }
    else
     { //Phần tưới tự động
          if(DO_AM_DAT1<=50)//mỗi lần muốn tưới phải kiểm tra xem độ ẩm có lớn hơn 50% chưa(tức là đất phải khô mới tưới)
             {   
                 bomm=true;
                 //Bật máy bơm
                 //BatMayBom();
             }
         if (bomm ==true)
          {
            count+=1;
            if(count==20)
            {
              Reset1();
            } 
         }
   }
     
  //Xử lý mái che
   //XuLyMaiChe();
 
    delay(1000);
}


/**============================================================================CÁC HÀM XỬ LÝ========================================================**/


 //Hàm chuyển đổi số nguyên sang char và lấy độ dài  
/*void convertIntToChar(int number)
{
        int count1=0;
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


//Hàm reset
void Reset()
{
    digitalWrite(Bom,HIGH);
    digitalWrite(Van,HIGH); 
    count=0;
    admin=false;
}
//Hàm reset1
void Reset1()
{
    digitalWrite(Bom,HIGH);
    digitalWrite(Van,HIGH); 
    count=0;
    bomm=false;
}

//Hàm bật máy bơm nước
void BatMayBom()
{
    digitalWrite(Bom,LOW);
    digitalWrite(Van,LOW); 
}

//Hàm tắt máy bơm nước
void TatMayBom()
{
    digitalWrite(Bom,HIGH);
    digitalWrite(Van,HIGH); 
}

//Phần xử lý mái che
void XuLyMaiChe()
{
    cuongDoAnhSang= analogRead(Analog3);
    if(cuongDoAnhSang<=100)
    {
      digitalWrite(manChe,HIGH);
    }
    else
    {
      digitalWrite(manChe,LOW);
    }
}*/
