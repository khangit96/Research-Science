char command;
String test;
boolean checkBluetooth=false;
String thayDoi;
int dem=0;
String  strHour,strMinute,strSecond;
#include <Wire.h> 
#include <EEPROM.h>
/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;
 boolean checkTime=false;
/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;
int c_second=40;
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop()


{  
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
 //     Serial.println("Da ket noi voi Android");
       Serial.println("O");
       test="";
       command='\0';
     }
     if(test=="F")
     {  
        checkBluetooth=false;
     //   Serial.println("Dã ngat ket noi voi Android");
       Serial.println("F");
         test="";
        command='\0';
     }
     //Bluetooth bắt đầu hoạt động
     if(checkBluetooth==true)
         {
           if(test=="1")//Bật máy bơm
           {
           //   Serial.println("Bat may bom");
           Serial.print("1");
           
           }
           else if(test=="2")//Tắt máy bơm
           { 
             // Serial.println("Tat may bom");
              Serial.print("2");
           }
           else if(test=="3")//Kéo màn lại
           {
            // Serial.println("Keo man lai");
              Serial.print("3");
           }
           else if(test=="4")//Kéo màn ra
           {
             // Serial.println("Keo man ra");
               Serial.print("4");
           }
           else if(test=="h")//kiểm tra nếu người dùng chọn thay đổi độ ẩm
           {
             thayDoi=test;
           }
           else if(test=="t")
           {
             thayDoi=test;
           }
           else
           {
             if(test!="")
             { 
               if(thayDoi=="h")//thay đổi độ ẩm
               {
               //   Serial.print("Do am da thay doi thanh cong: ");
                  //int a=test.toInt();
                //  Serial.println(a+10);
                  Serial.print("h");
                  thayDoi="";
               }
               else if(thayDoi=="t")//thay đổi thời gian
                { 
                 // Serial.print("Thay doi thoi gian thanh cong");
                   strHour=test.substring(0,2);
                   strMinute=test.substring(2,4);
                   WriteEEPROM(0,strHour.toInt());
                   WriteEEPROM(1,strMinute.toInt());
                   WriteEEPROM(2,strHour.toInt());
                   WriteEEPROM(3,strMinute.toInt());
                   Serial.println(strHour.toInt());
                   Serial.println(strMinute.toInt());
                  thayDoi="";
                }
                else
                { 
                    if(test=="r")
                    {
                      
                      
                      Serial.println("Repeat");
                    }
                    else if(test=="n")
                    {
                      Serial.println("Not Repeat");
                    }
                    else
                    {
                    strHour=test.substring(0,2);
                    strMinute=test.substring(3,5);
                    strSecond=test.substring(6,8);
                    setTime(strHour.toInt(),strMinute.toInt(),strSecond.toInt(), 1, 20, 4, 16); 
                    }
                    
                }
                
             }
             
           }
            test="";
           command='\0';
          /* dem+=1;
           if(dem>=10)
           {  
               Serial.print("h");
               delay(50);
               convertIntToChar(dem);
               Serial.print("t");
                delay(50);
               convertIntToChar(dem+1);
           }
        */   
         
     }
     else//Ngược lại là tin nhắn hoạt động
     { 
       
      
     }
     readDS1307();
    digitalClockDisplay();
    int getHourToCompar=ReadEEPROM(0);
    int getMinuteToCompar=ReadEEPROM(1);
    //Kiểm tra nếu thời gian cài đặt tưới bằng thời gian hiện tại
    if(getHourToCompar==hour&&getMinuteToCompar==minute)
    {
      WriteEEPROM(0,0);
      WriteEEPROM(1,0);
      Serial.println("equal");
    }
    if(ReadEEPROM(3)!=minute)
    {
      WriteEEPROM(0,ReadEEPROM(2));
      WriteEEPROM(1,ReadEEPROM(3));
      Serial.println("Not equal");
    }
     delay(1000);
}

 //Hàm chuyển đổi số nguyên sang char và lấy độ dài  
void convertIntToChar(int number)
{
    char NUMBER[2];
    itoa(number,NUMBER,10);
  //Gửi thông tin chuổi số đi
  for(int i=0;i<sizeof(NUMBER);i++)
    {
              
             Serial.print(NUMBER[i]);   
            delay(50); 
            
     }
}
void readDS1307()
{
        Wire.beginTransmission(DS1307);
        Wire.write((byte)0x00);
        Wire.endTransmission();
        Wire.requestFrom(DS1307, NumberOfFields);
        
        second = bcd2dec(Wire.read() & 0x7f);
        minute = bcd2dec(Wire.read() );
        hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
        wday   = bcd2dec(Wire.read() );
        day    = bcd2dec(Wire.read() );
        month  = bcd2dec(Wire.read() );
        year   = bcd2dec(Wire.read() );
        year += 2000;    
        WriteEEPROM(0,hour);
}
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}
 
void digitalClockDisplay(){
    // digital clock display of the time
    Serial.print(hour);
    printDigits(minute);
    printDigits(second);
    Serial.print(" ");
    Serial.print(day);
    Serial.print(" ");
    Serial.print(month);
    Serial.print(" ");
    Serial.print(year); 
    Serial.println(); 
}
 
void printDigits(int digits){
    // các thành phần thời gian được ngăn chách bằng dấu :
    Serial.print(":");
        
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
 
/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(min));
        Wire.write(dec2bcd(hr));
        Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
        Wire.write(dec2bcd(d)); 
        Wire.write(dec2bcd(mth));
        Wire.write(dec2bcd(yr));
        Wire.endTransmission();
}
//Write EEPROM
void WriteEEPROM(int address,int value)
{
     EEPROM.write(address, value);
     delay(5);
}
//Read EEPROM
int ReadEEPROM(int address)
{  
   int result= EEPROM.read(address);
     delay(5);
   return result;
    
}
