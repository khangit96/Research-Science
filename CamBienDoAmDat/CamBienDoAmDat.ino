#define Analog 5
#define Digital 8

int giatriAnalog, giatriDigital;
void setup() {
  Serial.begin(9600);
  pinMode(Digital,INPUT);
//  pinMode(Led,OUTPUT);
}
void loop() {
float ana=analogRead(Analog);
float anal=ana-223;
float analog=anal/800;
float doAmDat=100-(analog*100);
int test=(int)doAmDat;
giatriDigital=digitalRead(Digital);
Serial.print("Gia tri Analog: ");
Serial.println(ana);
Serial.println(anal);
Serial.println(analog);
Serial.println(test);
//Serial.print("Gia tri digital: ");
//Serial.println(giatriDigital);
delay(1000);
}

