#include <EEPROM.h>
int addr = 0;//địa chỉ EEPROM mà ta sẽ lưu đầu tiên
int count=0;
int val = 10;
int value;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
 
  
  
   //  WriteEEPROM(0,30);
     int value1 =ReadEEPROM(0);
      Serial.println(value1);


  delay(1000);
  
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

