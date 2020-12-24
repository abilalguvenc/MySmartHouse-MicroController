#include <Arduino.h>
#include <Servo.h>
// #include "devices.h"
// #include "network.h"
// #include "mytime.h"
//#include "packet.h"

String ssid = "TacticForce";
String pass = "Hes20181920";

void setup() 
{
  Serial.begin(115200);
  Serial.println("");

  // MyDevices::init();
  // MyNetwork::init(ssid, pass);
  //String pack = "asd";
  //int in = 1;
  //bool res = MyPacket::OnUpdateIoTState(pack, in);
}

void loop() 
{
  // if (MyTime::isOneSecondPassed()) 
  // {
  //   // float temp = MyDevices::GetTemperature();
  //   // Create Packet
  //   // MyNetwork::SendToAll(packet);
  //   // Serial.print(" Sicaklik: ");
  //   // Serial.println(temp);

  //   delay(10);

    
  //   // uint8_t a = 16;
  //   // Serial.println(a);
  // }
  Serial.println("asd");
  delay(100);
  //MyNetwork::Handle();
  //MyPacket::OnUpdateIoTState();
  
  // digitalWrite(device::O_Lamba, HIGH);
  // delay(1000);
  // digitalWrite(device::O_Lamba, LOW);
  // delay(100);
  // digitalWrite(device::O_Lamba, HIGH);
  // delay(100);
  // digitalWrite(device::O_Lamba, LOW);
  // delay(100);
  // put your main code here, to run repeatedly:
}