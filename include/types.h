#ifndef MYTYPES_H
#define MYTYPES_H

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



#endif