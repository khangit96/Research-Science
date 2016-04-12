volatile int flow_frequency; // Đo xung cảm biến lưu lượng
unsigned int l_hour; // Tính toán số lít/giờ
unsigned char flowsensor = 2; // Cảm biến nối với chân 2
unsigned long currentTime;
unsigned long cloopTime; 
int tongxung=0; 
int luongnuoc=0;
void flow () // Hàm ngắt
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      tongxung+=(l_hour); 
 luongnuoc+=(l_hour*1000)/450;     
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
      Serial.print("tong xung:"); 
      Serial.println(tongxung);
      Serial.println("xung");
      Serial.print("tong luong nuoc:"); 
      Serial.println(luongnuoc);
      Serial.print("mL");
      Serial.print("\n");
      
   }
}
