#include"SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
char number[20];
char message[160];
char pos;
 
void setup(){
    Serial.begin(9600);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    if (gsm.begin(2400))
        Serial.println("ok");
}
 
void Delsms(){//hàm xóa tất cả tin nhắn lưu trong bộ nhớ sim
    Serial.println("Delete SMS...");
    for (int i=0; i<40; i++){  // sim lưu được 40 tin nhắn
        int pos=sms.IsSMSPresent(SMS_ALL);//kiểm tra xem có tn lưu trong bộ nhớ không
         
        if (pos!=0){//nếu có
            Serial.print("\nSMS number ");
            Serial.println(pos); 
             
            if (sms.DeleteSMS(pos)==1){//xóa tin 
                Serial.print("\nDelete SMS number ");
                Serial.println(pos);      
            }
        }
    }
}
void loop(){
    pos=sms.IsSMSPresent(SMS_UNREAD);//biến pos là biến đếm số tin nhắn lưu trong bộ nhớ sim
     
    if((int)pos>0&&(int)pos<=40){
        message[0]='\0';
        
        sms.GetSMS((int)pos,number,message,160);//lấy nội dung sms tới
        sms.DeleteSMS((int)pos);//xóa sms vừa nhận
         
        if((int)pos>10)
            Delsms();// nếu sms lớn hơn 10 thì xóa toàn bộ sms. nên có hàm này vì sim test thường offline nên lúc online sẽ có nhiều tn tới nhất là chú viettel spam thôi rồi :v
    }
}
