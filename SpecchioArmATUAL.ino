#include <SoftwareSerial.h>
#include <Servo.h>
 
#define SERVO 6 // Porta Digital 6 PWM

SoftwareSerial BT(2, 3); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

Servo s; // Variável Servo
int pos; // Posição Servo
int gx,gy,gz;

void setup()  
{

  s.attach(SERVO);

  // set digital pin to control as an output
  pinMode(13, OUTPUT);

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero



  // Send test message to other device
  BT.println("Hello from Arduino");
}

char a; // stores incoming character from other device


boolean BTconnected = false;
char c = ' ';
int period;
String readString;


void loop() 
{
  if (BT.available()){
//    a=(BT.read());
//    Serial.print(a);
    char c = BT.read();  //gets one byte from serial buffer
      if (c == ',') {       //delimited ',' string parse 
        if (readString.length() >1) {
          int n = readString.toInt();  //convert readString into a number 
          if(readString.indexOf('x') >0) { 
            period=n;
            gx=period;
            Serial.print("GX= ");
            Serial.print(period);  
          }
          if(readString.indexOf('y') >0) { 
            period=n;
            gy=period;
            Serial.print(" GY= ");
            Serial.print(period);  
          }
          if(readString.indexOf('z') >0) { 
            period=n;
            gz=period;
            Serial.print(" GZ= ");
            Serial.println(period);  
          }
          readString=""; //clears variable for new input
        }
      }  
      else {     
        readString += c; //makes the string readString
      }
  }

  if(gx > -180 && gx < 180){
    s.write(gx);
  }
//  for(gx = 0; gx < 180;)
//    {
//      s.write(gx);
//      delay(1);
//    }
//  delay(200);
//    for(gx = 180; gx >= 0;)
//    {
//      s.write(gx);
//      delay(1);
//    }

  
}
