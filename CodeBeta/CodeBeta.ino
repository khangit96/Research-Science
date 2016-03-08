//************************************************
#include <SoftwareSerial.h>
#include<stdlib.h>
#include <string.h>
SoftwareSerial SIM900(2,3);
#include "SIM900.h"
#include "sms.h"
SMSGSM sms;
char smsbuffer[10]; //biến tin nhắn nhận
char n[20]="+84971982955"; //SĐT người gửi - chủ
char pos; //biến vị trí tin nhắn trong sim
char *p; //biến lệnh của người gửi
//********************************************
#define Analog 1
//*****************************************************
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//******************************************
int doAmDatCanTuoi=500;
void setup() 
{
 Serial.begin(9600);
 dht.begin();
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
  char content[50]="Khong the tuoi duoc ";
  return content;
}

/**********************************************************/
 int DO_AM_DAT()
{
  int doAmDat=analogRead(Analog);
  return doAmDat;
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
  pos=sms.IsSMSPresent(SMS_UNREAD);
  Serial.println((int)pos);
  Serial.print("POS=");
  Serial.println((int)pos);
  smsbuffer[0]='\0';
  sms.GetSMS((int)pos,n,20,smsbuffer,160);
  p=strstr(smsbuffer,"STATUS");//tìm kiếm chuổi STATUS trong nội dung tin nhắn
    if(p)//nếu mà nội dung tin nhắn là STATUS 
    {
      //sms.SendSMS(n, Reply(doAmDat,doAmKhongKhi,nhietDoKhongKhi));//thì gửi lại thông tin cho người dùng
      sms.SendSMS(n, Reply(DO_AM_DAT(),DO_AM_KHONG_KHI(),NHIET_DO_KHONG_KHI()));
      Serial.println("send ok!");
    }
    else//ngược lại nếu nội dung tin nhắn ko phải là STATUS
    {
          p=strstr(smsbuffer,"WATERING");//thì tìm kiếm chuổi WATERING trong nội dung tin nhắn
          if(p)//nếu mà nội dung tin nhắn là WATERING 
          {
            if(DO_AM_DAT()>500)//mỗi lần muốn tưới phải kiểm tra xem độ ẩm có lớn hơn 500 chưa(tức là đất phải khô mới tưới)
            {
                digitalWrite(13,HIGH);
            }
            else//ngược lại
            {
              Reply1(); //sẽ gửi tin nhắn về cho người dùng thông báo rằng ko tưới đk vì đất còn ướt
             
            }
           
          }
          else//ngược lại nếu nội dung tin nhắn ko phải là WATERING
          {
                p=strstr(smsbuffer,"CHANGE");//thì tìm kiếm chuổi CHANGE trong nội dung tin nhắn dùng để thay đổi nhiệt độ
              if(p)//nếu mà nội dung tin nhắn là CHANGE 
              {  
                int Length=sizeof(smsbuffer);//lấy độ dài của chuổi tin nhắn
                char changeNhietDo[163]="\0";//biến để lấy ra giá trị nhiệt độ từ nội dung tin nhắn thay đổi nhiệt độ
                strncpy(changeNhietDo,smsbuffer+7,3);//cắt giá trị nhiệt độ từ trong nội dung chuổi tin nhắn
                doAmDatCanTuoi=atoi(changeNhietDo);//gán doAmDatCanTuoi bằng với giá trị nhiệt độ cần thay đổi trong nội dung tin nhắn
                sms.SendSMS(n,"Da thay doi");
                Serial.println(doAmDatCanTuoi);
                delay(5000);
              }
         }
    }
    if(DO_AM_DAT()>500)//mỗi lần muốn tưới phải kiểm tra xem độ ẩm có lớn hơn 500 chưa(tức là đất phải khô mới tưới)
       {
        digitalWrite(13,HIGH);
       }
   else
       {
              
       }
    delay(1000);
}
