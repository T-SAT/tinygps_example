#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial ss(10, 9);

void recvGPS(void)
{
  Serial.print("byte_num = ");
  Serial.println(ss.available());

  while (ss.available() != 0)
    gps.encode(ss.read());

}

void getGPS(float *flat, float *flon, float *speed)
{
  *flat = gps.location.lat();
  *flon = gps.location.lng();
  *speed = gps.speed.mps();
}

unsigned long getDistance(float originFlat, float originFlon,
                          float destFlat, float destFlon)
{
  unsigned long distance;

  distance = (unsigned long)TinyGPSPlus::distanceBetween(
               originFlat, originFlon,
               destFlat, destFlon);

  return (distance);
}

void setup() {
  // put your setup code here, to run once:
  ss.begin(9600);
  Serial.begin(9600);

}

void loop() {
  float flat, flon, speed;
  
  // put your main code here, to run repeatedly:
  recvGPS();
  getGPS(&flat, &flon, &speed);
  Serial.print("flat = "); Serial.println(flat);
  Serial.print("flon = "); Serial.println(flon);
  Serial.print("speed = "); Serial.println(speed);
}
