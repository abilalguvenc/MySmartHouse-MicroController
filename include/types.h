#ifndef MYTYPES_H
#define MYTYPES_H

#define D0 16
#define D1 05

#define OFF false
#define ON true

enum device : int
{
  O_Lamba,
  O_Pencere,
  O_Klima,

  Y_Lamba,
  Y_Pencere,

  M_Lamba,
  M_Kettle,

  A_Hirsiz,
  A_Yangin
};

enum device_pin : int
{
  PO_Lamba    = 05,
  PO_Pencere  = 04,
  PO_Klima_H  = 00,
  PO_Klima_C  = 02,

  PY_Lamba    = 14,
  PY_Pencere  = 12,

  PM_Lamba    = 13,
  PM_Kettle   = 15,
  
  PS_Hareket  = 99,   // change this
  PS_Sicaklik = 16,

  P_None = 99
};

bool isDeviceValid(device dev)
{
  bool res = false;
  switch(dev)
  {
    case device::O_Lamba:
    case device::O_Pencere:
    case device::O_Klima:

    case device::Y_Lamba:
    case device::Y_Pencere:

    case device::M_Lamba:
    case device::M_Kettle:
    
    case device::A_Hirsiz:
    case device::A_Yangin:
      res = true;
      break;
    default:
      res = false;
  }
  return res;
}

device_pin getDevicePin(device dev)
{
  switch (dev)
  {
    case device::O_Lamba:
      return device_pin::PO_Lamba;
    case device::O_Pencere:
      return device_pin::PO_Pencere;
    case device::Y_Lamba:
      return device_pin::PY_Lamba;
    case device::M_Lamba:
      return device_pin::PM_Lamba;
    case device::M_Kettle:
      return device_pin::PM_Kettle;
    default:
      return device_pin::P_None;
  }
  return device_pin::P_None;
}

inline bool isBool(uint8_t val)
{
  return val == 1 || val == 0;
}

enum operation : uint8_t
{
  Login = 0,          // opcode + username (str) + password (str)
  UpdateDevice,       // opcode + iotid (byte) + newstate (bool)
  UpdateValue,        // opcode + valueid (byte) + value (byte)     (temprature)
  LoginResult,        // opcode + success (bool) ? iotstates[n] (bool[n]) : null
  Alert,              // opcode + alertid (byte) + alertstate (bool)
};



#endif