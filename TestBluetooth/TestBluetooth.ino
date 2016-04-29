char command;
String test;
boolean checkBluetooth=false;
String thayDoi;
int dem=0;
void setup() {
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
           }
           else if(test=="2")//Tắt máy bơm
           { 
              Serial.println("Tat may bom");
           
           }
           else if(test=="3")//Kéo màn lại
           {
             Serial.println("Keo man lai");
           }
           else if(test=="4")//Kéo màn ra
           {
              Serial.println("Keo man ra");
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
                  Serial.print("Do am da thay doi thanh cong: ");
                  //int a=test.toInt();
                //  Serial.println(a+10);
                  thayDoi="";
               }
               if(thayDoi=="t")//thay đổi thời gian
                { 
                  Serial.print("Thay doi thoi gian thanh cong");
                  Serial.println(test);
                  thayDoi="";
                }
              
             }
             
           }
            test="";
           command='\0';
           dem+=1;
           if(dem>=10)
           {  
               Serial.print("h");
               delay(50);
               convertIntToChar(dem);
               Serial.print("t");
                delay(50);
               convertIntToChar(dem+1);
           }   
         
     }
     else//Ngược lại là tin nhắn hoạt động
     {
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
            //if(NUMBER[i]!='\0')
            //{
               Serial.print(NUMBER[i]);  
              delay(50); 
            //}
     }
}
