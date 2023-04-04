#include <HX711.h>
#include <SoftwareSerial.h>
#define DOUT 5
#define CLK 4
int micpin =A0;
int airpin= A1;
int val;
int tempPin = A2;
int vibrationpin=3;
SoftwareSerial mySerial(9, 10);
HX711 scale;

float calibration_factor=20000;

bool isCrying(){
  int aValue=0;
  float volts;
  float maxvolts;
  float minvolts;
  static int sure=0;
  static int signalMax=0;
  static int signalMin=1024;
  
  aValue= analogRead(micpin);
  if(aValue >signalMax)
  {
    signalMax=aValue;
  }
  if(aValue < signalMin)
  {
    signalMin = aValue;
  }
  volts=(aValue*5.0)/1024.0;
  minvolts=(signalMin*5.0)/1024.0;
  maxvolts=(signalMax*5.0)/1024.0;

  float diff=(maxvolts-minvolts)*100;
  if(diff>3)
    {
      sure++;
      signalMax=0;
      signalMin = 1024;
    }
  if(sure==3)
    {
      sure=0;
      return 1;
    }
  else
    return 0;
}

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);

  //scale.tare(); 
}

void loop(){
  
  bool alarm=0;
  bool crying=0;
  bool hot=0;
  bool polluted=0;
  bool vibration=0;
  Serial.println(scale.get_units()-7.49);
  if(scale.get_units()-7.48>3)
  {
    Serial.println("active");
    val = analogRead(tempPin);
    vibration=!digitalRead(vibrationpin);
    float temp = ( val/1024.0)*500-20; //the -20 is an offset to calibrate faulty sensor
    crying=isCrying();
    int aqValue=analogRead(airpin);
    
  Serial.print("Is crying= ");
  Serial.println(crying);

  Serial.print("Is polluted= ");
  Serial.println(aqValue>150);
  
  Serial.print("Too hot = ");
  Serial.println(temp>40);
  
//  
//  if(crying)
//  {
//      sendCall();
//      SendSMS("Your child is crying.");
//  }
//  if(temp>32)
//  {
//      sendCall();
//      SendSMS("Car cabin tempreture too hot.");
//  }
//  if(aqValue>150)
//  {
//      sendCall();
//      SendSMS("Car cabin air quality is toxic.");
//  }
//  if(vibration)
//  {
//      sendCall();
//      SendSMS("Car vibration too high.");
//  }
  
  delay(1500);

  }
//  if( mySerial.available() )
//  {
//    char c = mySerial.read();
//    Serial.print(c);
//  }
//  if(Serial.available())
//  {
//    String Arsp = Serial.readString();
//
//    Serial.println("Serial available");
//    Serial.println(Arsp);
//    mySerial.println(Arsp);
//    Serial.println("Serial available end");
//  }
  
}

void SendSMS(String message)
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
//  mySerial.print("AT+CMGF=1\r");                   //Set the module to SMS mode
//  delay(100);
//  mySerial.print("AT+CMGS=\"+9647735836321\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
//  delay(500);
//  mySerial.print(message);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
//  delay(1500);
//  mySerial.print((char)26);// (required according to the datasheet)
//  delay(500);
//  mySerial.println();
//  Serial.println("Text Sent.");
//  delay(1000);

}
void sendCall()
{
  Serial.println("calling...");
//  mySerial.println("AT");
//  delay(500);
//  mySerial.println("ATD+9647735836321;");
//  delay(10000);
}
