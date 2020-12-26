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

        MyDevices::SetDeviceState(dev, state);
        return true;
    }

    bool Handle(String pkt)
    {
        if (pkt.isEmpty())
            return false;

        Packet packet(pkt);

        bool result = false;
        operation op = (operation)packet.getByte();

        switch (op)
        {
        case operation::Login:
            
            break;

        case operation::UpdateDevice:
            Serial.print("Update device: ");
            return OnUpdateIoTState(packet);
            break;

        case operation::UpdateValue:

            break;

        default:
            result = false;
            break;
        }
        return result;
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