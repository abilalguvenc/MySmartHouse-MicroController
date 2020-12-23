#include <Servo.h>
//#include <DHT.h>
#define DHTTYPE DHT11 // DHT sensor tipini belirliyoruz.

enum device : int
{
  O_Lamba = 16,
  O_Pencere = 05,
  O_Klima = 04,
  Y_Lamba = 00,
  Y_Klima = 02,
  M_Lamba = 14,
  M_Kettle = 12,
  M_Kahve = 13,
  //S_Hareket = 00,   // change this
  S_Sicaklik = 15
};

enum operation : int
{
  Login = 0,          // opcode + username (str) + password (str)
  UpdateIoTState,     // opcode + iotid (byte) + newstate (bool)
  UpdateValue,        // opcode + valueid (byte) + value (byte)     (temprature)
  UpdateState,        // opcode + stateid (byte) + newstate (bool)
  LoginResult,        // opcode + success (bool) ? iotstates[n] (bool[n]) : null
  Alert,              // opcode + alertid (byte) + alertstate (bool)
};


namespace MyDevices
{
  //DHT dht(S_Sicaklik, DHTTYPE);
  Servo O_ServoMotor;

  void init()
  {
    pinMode(device::O_Lamba, OUTPUT);
    pinMode(device::O_Klima, OUTPUT);
    pinMode(device::Y_Lamba, OUTPUT);
    pinMode(device::Y_Klima, OUTPUT);
    pinMode(device::M_Lamba, OUTPUT);
    pinMode(device::M_Kettle, OUTPUT);
    pinMode(device::M_Kahve, OUTPUT);
    O_ServoMotor.attach(device::O_Pencere);
    //S_Hareket
    //S_Sicaklik

    digitalWrite(device::O_Lamba, LOW);
    digitalWrite(device::O_Klima, LOW);
    digitalWrite(device::Y_Lamba, LOW);
    digitalWrite(device::Y_Klima, LOW);
    digitalWrite(device::M_Lamba, LOW);
    digitalWrite(device::M_Kettle, LOW);
    digitalWrite(device::M_Kahve, LOW);
    O_ServoMotor.write(0);
  }

  float GetTemperature()
  {
    float temp = 1.1;//dht.readTemperature();
    
    if (isnan(temp)) 
    {
      Serial.println(" HATA: Sicaklik Sensoru Okunamadi");
      return -1.1;
    }

    return temp;
  }
}