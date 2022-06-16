MQ135 gasSensor = MQ135(A0); 
float air_quality = gasSensor.getPPM();
 #include "MQ135.h" void setup ()
 {
  Serial.begin (9600); 
}
         void loop() 
         {
         MQ135 gasSensor = MQ135(A0);
         // Attach sensor to pin A0 
         float rzero = gasSensor.getRZero();
         Serial.println (rzero);
         delay(1000); 
         }
         #include <SoftwareSerial.h> 
         #define DEBUG true SoftwareSerial esp8266(9,10);
         #include <LiquidCrystal.h> LiquidCrystal lcd(12,11, 5, 4, 3, 2);
         const int sensorPin= 0; 
         int air_quality; 
         pinMode(8, OUTPUT);
         lcd.begin(16,2);
         lcd.setCursor (0,0);
         lcd.print ("circuitdigest "); 
         lcd.setCursor (0,1);
         lcd.print ("Sensor Warming ");
         delay(1000); 
         Serial.begin(115200); 
         esp8266.begin(115200);
         sendData("AT+RST\r\n",2000,DEBUG);
         sendData("AT+CWMODE=2\r\n",1000,DEBUG); 
         sendData("AT+CIFSR\r\n",1000,DEBUG);
         sendData("AT+CIPMUair_quality=1\r\n",1000,DEBUG); 
         sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); 
         pinMode(sensorPin, INPUT);
         lcd.clear();
         if(esp8266.available())
         { 
         if(esp8266.find("+IPD,")) 
         { 
         delay(1000); 
         int connectionId = esp8266.read()-48; 
         String webpage = "<h1>IOT Air Pollution Monitoring System</h1>"; 
         webpage += "<p><h2>"; 
         webpage+= " Air Quality is "; 
         webpage+= air_quality; 
         webpage+=" PPM"; 
         webpage += "<p>"; 
         sendData(cipSend,1000,DEBUG); 
         sendData(webpage,1000,DEBUG); 
         cipSend = "AT+CIPSEND="; 
         cipSend += connectionId; 
         cipSend += ","; 
         cipSend +=webpage.length(); 
         cipSend +="\r\n"; lcd.setCursor (0, 0); 
         lcd.print ("Air Quality is "); 
         lcd.print (air_quality); 
         lcd.print (" PPM "); 
         lcd.setCursor (0,1); 
         if (air_quality<=1000) 
         {
         lcd.print("Fresh Air"); 
         digitalWrite(8, LOW); 
         String sendData(String command, const int timeout, boolean debug) 
         {
         String response = ""; 
         esp8266.print(command); // send the read character to the esp8266 
         long int time = millis(); 
         while( (time+timeout) > millis()) 
         { 
         while(esp8266.available()) 
         { 
         // The esp has data so display its output to the serial window 
         char c = esp8266.read(); // read the next character. 
         response+=c; 
         } 
         } 
         if(debug) 
         { 
         Serial.print(response); 
         } 
         return response;