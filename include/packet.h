#ifndef MYPACKET_H
#define MYPACKET_H

#include <Arduino.h>
#include "devices.h"
#include "types.h"

namespace MyPacket
{
    class Packet 
    {
        String packet;
        unsigned int index;

    public:
        Packet()
        {
            packet = "";
            index = 0;
        }

        Packet(String pkt)
        {
            packet = pkt;
            index = 0;
        }

        uint8_t getByte()
        {
            return packet[index++];
        }

        unsigned int size()
        {
            return packet.length();
        }

        unsigned int sizeLeft()
        {
            return packet.length() - index;
        }
    };

    bool OnLogin(Packet packet)
    {
        Serial.println("'OnLogin' fonksiyonu tanimli degil!");
        return false;
    }

    bool OnUpdateDevice(Packet packet)
    {
        if(packet.sizeLeft() < 2) 
        {
            Serial.println("HATA[P1]: Hatali paket boyutu!");
            return false;
        }

        device dev = (device)packet.getByte();
        uint8_t state = packet.getByte();
        
        if (!isBool(state))
        {
            Serial.print("HATA[P1]: Girilen deger bool degil! (");
            Serial.print(state);
            Serial.println(")");

            return false;
        } 

        if (dev == device::O_Klima) 
        {
            if (packet.sizeLeft()<1)
            {
                Serial.println("Hata[P1]: Klima derecesi gonderilmedi!");
                return false;
            }
            
            uint8_t degree = packet.getByte();
            return MyDevices::SetDeviceState(dev, state, degree);
        }

        return MyDevices::SetDeviceState(dev, state);
    }

    bool OnUpdateValue(Packet packet)
    {
        Serial.println("'OnUpdateValue' fonksiyonu tanimli degil!");
        return false;
    }

    bool Handle(String pkt)
    {
        if (pkt.isEmpty())
            return false;

        Packet packet(pkt);

        operation op = (operation)packet.getByte();

        switch (op)
        {
        case operation::Login:
            return OnLogin(packet);

        case operation::UpdateDevice:
            return OnUpdateDevice(packet);

        case operation::UpdateValue:
            return OnUpdateValue(packet);

        default:
            break;
        }
        return false;
    }

    String NewTempPacket()
    {
        String packet;
        packet += (char)operation::UpdateValue;
        packet += (char)device::O_Klima;
        packet += (char)MyDevices::device_states[O_Klima];
        packet += (char)(uint8_t)MyDevices::GetTemperature();
        return packet;
    }

    String NewAlarmPacket(device dev)
    {
        String packet;
        packet += (char)operation::Alert;
        packet += (char)dev;
        return packet;
    }

    String DeviceStatesPacket()
    {
        String packet;
        packet += (char)operation::LoginResult;
        packet += (char)MyDevices::device_states[device::O_Lamba];
        packet += (char)MyDevices::device_states[device::O_Pencere];
        packet += (char)MyDevices::device_states[device::O_Klima];
        packet += (char)MyDevices::device_states[device::Y_Lamba];
        packet += (char)MyDevices::device_states[device::Y_Pencere];
        packet += (char)MyDevices::device_states[device::M_Lamba];
        packet += (char)MyDevices::device_states[device::M_Kettle];
        packet += (char)MyDevices::device_states[device::A_Hirsiz];
        packet += (char)MyDevices::device_states[device::A_Yangin];
        packet += (char)MyDevices::O_Klima_Derece;
        return packet;
    }
}

#endif