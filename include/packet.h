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

    bool OnUpdateIoTState(Packet packet)
    {
        if(packet.sizeLeft() < 2) 
        {
            Serial.println("HATA[P1]: Hatali paket boyutu!");

            return false;
        }

        device dev = (device)packet.getByte();

        if (!isDeviceValid(dev))
        {
            Serial.print("HATA[P1]: Cihaz bulunamadi! (");
            Serial.print(dev);
            Serial.println(")");

            return false;
        }

        uint8_t state = packet.getByte();
        
        if (!isBool(state))
        {
            Serial.print("HATA[P1]: Bool komut hatali! (");
            Serial.print(state);
            Serial.println(")");

            return false;
        } 

        digitalWrite(dev, state);
        return true;
    }

    bool Handle(String pkt)
    {
        if (pkt.isEmpty())
            return false;

        Packet packet(pkt);

        bool result = true;
        operation op = (operation)packet.getByte();

        switch (op)
        {
        case operation::Login:
            
            break;

        case operation::UpdateIoTState:
            return OnUpdateIoTState(packet);
            break;

        case operation::UpdateValue:

            break;

        case operation::UpdateState:

            break;

        default:
            result = false;
            break;
        }
        return result;
    }

    String NewTempPacket(float temp)
    {
        String packet;
        packet += operation::UpdateValue;
        packet += device::S_Sicaklik;
        packet += (uint8_t)temp;
        return packet;
    }
}

#endif