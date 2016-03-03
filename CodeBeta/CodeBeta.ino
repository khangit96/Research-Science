

/*****************************************************************************KHỞI TẠO****************************************************************************/
#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
#include<stdlib.h>
#include <string.h>

//LCD
/*LiquidCrystal lcd(8,9,4,5,6,7);
byte doC[8]={B01110,B01010,B01010,
B01110,B00000,B00000,B00000,B00000}; //biến đọc*/

//SIM-SMS
SoftwareSerial SIM900(2,3);
#include "SIM900.h"
#include "sms.h"
SMSGSM sms;
char smsbuffer[160]; //biến tin nhắn nhận
char n[20]="+84902581349"; //SĐT người gửi - chủ
char pos; //biến vị trí tin nhắn trong sim
char *p; //biến lệnh của người gửi
#define Led 12
//Độ ẩm đất
/*#define Analog 5
#define Digital 0
#define Relay1 11
#define Relay2 8
//mặc định độ ẩm đất là 500

//Độ ẩm không khí-nhiệt độ
#include "DHT.h"       // Gọi thư viện DHT11(độ ẩm đất-độ ẩm ko khí
const int DHTPIN = 1;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);*/
int doAmDatCanTuoi=500;

/*****************************************************************************HÀM CÀI ĐẶT**************************************************************************/
void setup() 
{    
  //Khởi động cảm biến độ ẩm
   // dht.begin(); 
  //Khởi động modun
  Serial.begin(9600);
  //Pin Relay 
  //pinMode(Relay1, OUTPUT);
  //pinMode(Relay2, OUTPUT);
  //Khởi động LCD
//  lcd.begin(16,2);
 // lcd.clear();
  //lcd.createChar(1,doC);
  //Kết nối modu sim900a
  Serial.println("GSM Shield testing.");
  if (gsm.begin(2400)) 
      Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
}

/*****************************************************************************HÀM HIỂN THỊ LÊN LCD*****************************************************************************/
/*void XuatLCD(void)
{
  lcd.setCursor(0,0);
  lcd.print("DAK:");
  delay(500);
  lcd.setCursor(4,0);
  lcd.print("50");
  delay(500);
  lcd.setCursor(6,0);
  lcd.print("%");
  lcd.setCursor(8,0);
  lcd.print("ND:");
  delay(500);
  lcd.setCursor(11,0);
  lcd.print("32");
  lcd.setCursor(13,0);
  lcd.write(1);
  lcd.setCursor(14,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("DAD:");
  delay(500);
  lcd.setCursor(4,1);
  lcd.print("60");
  lcd.setCursor(6,1);
  lcd.print("%");
  lcd.setCursor(8,1);
  lcd.print("LL:");
  delay(500);
  lcd.setCursor(11,1);
  lcd.print("10");
  lcd.setCursor(14,1);
  lcd.print("mL");
  delay(200);
  delay(10000);  
  lcd.clear();
  delay(1000);
}*/


/*****************************************************************************HÀM TIN NHẮN TRẢ VỀ*****************************************************************************/
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


/*****************************************************************************VÒNG LẶP TRONG MẠCH*****************************************************************************/
void loop() 
{
  //Xuất thông tin ra màn hình LCD
 // XuatLCD();
 
  //LấyGiá trị độ ẩm đất
 /*int doAmDat=analogRead(Analog);
 int kiemTraDoAmDat=digitalRead(Digital);//nếu có độ ẩm đất thì kiemTraDoAmDat=1 và ngược lại thì kiemTraDoAmDat=0
 
//Lấy giá trị độ ẩm không khí-nhiệt độ không khí
  int doAmKhongKhi = dht.readHumidity();    //Đọc độ ẩm không khí
  int nhietDoKhongKhi = dht.readTemperature(); //Đọc nhiệt độ không khí*/
  
  //Đọc tin nhắn và phân tích lệnh
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
      sms.SendSMS(n, Reply(12,23,65));
      Serial.println("send ok!");
    }
    else//ngược lại nếu nội dung tin nhắn ko phải là STATUS
    {
          p=strstr(smsbuffer,"WATERING");//thì tìm kiếm chuổi WATERING trong nội dung tin nhắn
          if(p)//nếu mà nội dung tin nhắn là WATERING 
          {
             digitalWrite(Led,HIGH);
             delay(5000);
             digitalWrite(Led,LOW);
          }
          else//ngược lại nếu nội dung tin nhắn ko phải là WATERING
          {
                p=strstr(smsbuffer,"CHANGE");//thì tìm kiếm chuổi CHANGE trong nội dung tin nhắn dùng để thay đổi nhiệt độ
              if(p)//nếu mà nội dung tin nhắn là CHANGE 
              {  
                int length=sizeof(smsbuffer);//lấy độ dài của chuổi tin nhắn
                char changeNhietDo[30];//biến để lấy ra giá trị nhiệt độ từ nội dung tin nhắn thay đổi nhiệt độ
                strncpy(changeNhietDo,smsbuffer+8,length-8);//cắt giá trị nhiệt độ từ trong nội dung chuổi tin nhắn
                doAmDatCanTuoi=(int)changeNhietDo;//gán doAmDatCanTuoi bằng với giá trị nhiệt độ cần thay đổi trong nội dung tin nhắn
                Serial.print("Do am can tuoi: ");
                Serial.println(doAmDatCanTuoi);
               // digitalWrite(Relay1,HIGH);
                delay(9000);
                //digitalWrite(Relay1,LOW);
              }
         }
    }
   //Kiểm tra độ ẩm đất
   /* if (doAmDat>doAmDatCanTuoi)
  {
   digitalWrite(Relay1,HIGH);
  }
  else if(doAmDat<=doAmDatCanTuoi)
  {
   digitalWrite(Relay1,LOW);
  }*/
 
  
    delay (1000);
}
