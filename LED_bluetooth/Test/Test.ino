// Khai báo biến
char state;
 
void setup() {
 // Cài đặt các chân bạn muốn điều khiển thành thành Ouput 
 // Ở đây tôi sử dụng 4 chân 9, 10, 11, 12
// pinMode(9, OUTPUT);
 //pinMode(10, OUTPUT);
 //pinMode(11, OUTPUT);
 //pinMode(12, OUTPUT);
 Serial.begin(9600); // Kết nối bluetooth module ở tốc độ 9600
}
 
void loop() {
 
 if(Serial.available() > 0){
   // Đọc giá trị nhận được từ bluetooth
   state = Serial.read();
 } else 
   state = 0;
 
 Serial.println("sdjsj");
// Thực hiện điều khiển các chân 9, 10, 11, 12
// Ở đây tôi đã quy ước sẵn các giá trị gửi và nhận dữ liệu giữa điện thoại và Arduino
/*switch (state) {
  case '1':
    digitalWrite(9, HIGH);
    break;
  case '2':
    digitalWrite(9, LOW);
    break;
  case '3':
    digitalWrite(10, HIGH);
    break;
  case '4':
    digitalWrite(10, LOW);
    break;
  case '5':
    digitalWrite(11, HIGH);
    break;
  case '6':
    digitalWrite(11, LOW);
    break;
  case '7':
    digitalWrite(12, HIGH);
    break;
  case '8':
    digitalWrite(12, LOW);
    break;    
 
  default: 
   break;
}
 */
 
}
