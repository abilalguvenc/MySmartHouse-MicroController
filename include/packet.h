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
}

#endif