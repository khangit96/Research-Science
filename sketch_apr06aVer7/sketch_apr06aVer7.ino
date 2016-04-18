//************************************************
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
char *p2;
char *p3;
char *p4;
int count=0;
boolean admin=false;
boolean bomm = false;
int dem=0;
char command;
String test;
boolean checkBluetooth=false;
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
int value;
#define Analog3 4
#define manChe 8
int doAmMacDinh=50;//độ ẩm mặc định cần phải tưới
//******************************************
int doAmDatCanTuoi=50;
int tat=0;
int bat=0;
int demReset=0;
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
  char q[10],e[10];
  char DO_AM[30]="Do am dat: ";
  char NHIET_DO[30]="Nhiet do: ";
  char result[160]="\0";
  itoa(Doamdat,q,10);//chuyển đổi doAm về chuổi DO_AM
  itoa(Nhietdo,e,10);
  strcat(result,DO_AM); //nối biến DO_AM vào sau biến result->kết quả là: "Độ ẩm: 123" 
  strcat(result,q);
  strcat(result,"%\n");//xuống dòng
  strcat(result,NHIET_DO);
  strcat(result,e);
  strcat(result,"*C");
  return result;
}
//Hàm trả tin nhắn cho người dùng khi không tưới đk
char *Reply1(int doAmMacDinh)
{  
  char q[10];
  char result[160]="\0";
  char content[50]="Do am can tuoi da thay doi thanh ";
  itoa(doAmMacDinh,q,10);
  strcat(result,content);
  strcat(result,q);
  strcat(result,"%");
  return result;
}
char *Reply2()
{  
  char content[80]="Do am dat da du.De tiep tuc tuoi,soan YES";
  return content;
}
/**********************************************************/
 int DO_AM_DAT()
{
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
  if(demReset==0)
   {
     sms.SendSMS(n,"He thong da bat dau hoat dong...");
     demReset=1;
   }
   while(Serial.available() > 0)
     {
       command = ((byte)Serial.read());
       test += command;
       delay(100);
   } 
    //Bật kết nối Bluetooth
     if(test=="O")
     {  
       checkBluetooth=true;
       Serial.println("Da ket noi voi Android");
       test="";
       command='\0';
     }
     if(test=="F")
     {  
        checkBluetooth=false;
        Serial.println("Dã ngat ket noi voi Android");
        test="";
        command='\0';
     }
     //Bluetooth bắt đầu hoạt động
     if(checkBluetooth==true)
         {
           if(test=="1")//Bật máy bơm
           {
              Serial.println("Bat may bom");
              digitalWrite(Bom,LOW);//bơm nước
           }
           else if(test=="2")//Tắt máy bơm
           {
              Serial.println("Tat may bom");
              digitalWrite(Bom,HIGH);//bơm nước
           }
           else if(test=="3")//Kéo màn lại
           {
             Serial.println("Keo man lai");
              digitalWrite(manChe,HIGH);
           }
           else if(test=="4")//Kéo màn ra
           {
              Serial.println("Keo man ra");
              digitalWrite(manChe,LOW);
           }
           else//Thay đổi độ ẩm
           {  
              Serial.print("Do am da thay doi thanh cong");
              Serial.print(test);
           }
           test="";
           command='\0';
   }
   else
   {
               int DO_AM_DAT1=DO_AM_DAT();
           /**Phần xử lý tin nhắn**/
          //Đọc tin nhắn
          pos=sms.IsSMSPresent(SMS_UNREAD);
          Serial.println((int)pos);
          Serial.print("POS=");
          Serial.println((int)pos);
          smsbuffer[0]='\0';
          sms.GetSMS((int)pos,n,40,smsbuffer,160);
          if((int)pos>0)
          {
            p=strstr(smsbuffer,"STATUS");//tìm kiếm chuổi STATUS trong nội dung tin nhắn
            p1=strstr(smsbuffer,"WATERING");//thì tìm kiếm chuổi WATERING trong nội dung tin nhắn
            p2=strstr(smsbuffer,"STOP");
            p3=strstr(smsbuffer,"YES");
            p4=strstr(smsbuffer,"CHANGE");
             if(p)//nếu mà nội dung tin nhắn là STATUS
            {
              sms.SendSMS(n,Reply(DO_AM_DAT(),DO_AM_KHONG_KHI(),NHIET_DO_KHONG_KHI()));
             
            }
            if(p1)//Nếu nội dung là WATERING
            {
                     //Trước khi tưới phải kiểm tra xem điều kiện độ ẩm đất có hợp lý hay ko
                      if(DO_AM_DAT1>doAmMacDinh)
                      {
                         sms.SendSMS(n,Reply2());
                      }
            }
             if(p2)//Nếu nội dung là STOP
            {
                       sms.SendSMS(n,"Da dung.");
                       admin=false;
                       digitalWrite(Bom,HIGH);//bơm nước
                       digitalWrite(Van,HIGH); 
            }
             if(p3)//Nếu nội dung là YES
            {
                       sms.SendSMS(n,"Dang tuoi...");
                       admin=true;
                       digitalWrite(Bom,LOW);//bơm nước
                       digitalWrite(Van,LOW);  
            }
             if(p4)//Nếu nội dung là CHANGE
            {
                        int Length=sizeof(smsbuffer);//lấy độ dài của chuổi tin nhắn
                        char changeNhietDo[163]="\0";//biến để lấy ra giá trị nhiệt độ từ nội dung tin nhắn thay đổi nhiệt độ
                        strncpy(changeNhietDo,smsbuffer+7,2);//cắt giá trị nhiệt độ từ trong nội dung chuổi tin nhắn
                        doAmDatCanTuoi=atoi(changeNhietDo);//gán doAmDatCanTuoi bằng với giá trị nhiệt độ cần thay đổi trong nội dung tin nhắn
                        doAmMacDinh=doAmDatCanTuoi;
                        sms.SendSMS(n,Reply1(doAmMacDinh));
            }
          }
          
            /**Thông báo đến người dùng xem tin nhắn đã gửi thành công hay chưa**/
            
             /**Phần xử lý việc bơm nước**/
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
            if(DO_AM_DAT1<=doAmMacDinh)//mỗi lần muốn tưới phải kiểm tra xem độ ẩm có lớn hơn 50% chưa(tức là đất phải khô mới tưới)
               {   
                   bomm=true;
                   digitalWrite(Bom,LOW);
                   digitalWrite(Van,LOW); 
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
             
          /**Phần xử lý mái che**/
          value= analogRead(Analog3);
          if(value<=100)
          {
            bat+=1;
            if (bat==3)
            {
            digitalWrite(manChe,HIGH);
            }
            if(bat>3) 
            {
              bat=0;
            }
          }
          else
          {
              tat+=1;
              if (tat==3)
              {
              digitalWrite(manChe,LOW);
              }
               if(tat>3) 
              {
              tat=0;
              }
          }
        
    }
  

    delay(1000);
}

/**============================================================================CÁC HÀM XỬ LÝ========================================================**/
//Hàm reset
void Reset()
{  
    sms.SendSMS(n,"Da tuoi thanh cong.");
    digitalWrite(Bom,HIGH);
    digitalWrite(Van,HIGH); 
    count=0;
    admin=false;
}

void Reset1()
{  
    digitalWrite(Bom,HIGH);
    digitalWrite(Van,HIGH); 
    count=0;
    bomm=false;
}


