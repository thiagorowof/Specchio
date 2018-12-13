//install this MPU library
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SoftwareSerial.h>


//Gyroscope
MPU6050 mpu6050(Wire);
int gyx,gyy,gyz;

//bluetooth
SoftwareSerial btSerial(2, 3); // RX, TX


void setup() {
  //buzzer
  pinMode(9,OUTPUT);
  
  Serial.begin(9600);
  btSerial.begin(9600);
  btSerial.println("Bluetooth Conectado");
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  //buzzer
  tone(9,440);
  delay(100);
  noTone(9);
}

void loop() {
  mpu6050.update();
  gyx = mpu6050.getAngleX();
  gyy = mpu6050.getAngleY();
  gyz = mpu6050.getAngleZ();
  Serial.print("angleX : "); Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : "); Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : "); Serial.println(mpu6050.getAngleZ());

  if (btSerial.available()){
    btSerial.print(gyx); btSerial.print("x,");
    btSerial.print(gyy); btSerial.print("y,");
    btSerial.print(gyz); btSerial.print("z,");
  }
  
  delay(300);
  
}
