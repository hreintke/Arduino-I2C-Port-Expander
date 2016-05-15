#include "Arduino_I2C_Port_Expander.h" //include the declaration for this class

//<<constructor>>
EXPAND::EXPAND(uint8_t addr){
  _addr = addr;
  //Wire.begin();
}

//<<destructor>>
EXPAND::~EXPAND(){/*nothing to destruct*/}

void EXPAND::digitalWrite(byte pin,byte val){
  io_DataPacket[0] = DIGITALWRITE;    // method
  io_DataPacket[1] = pin;  // pin
  io_DataPacket[2] = val;  // val
  sendDataPacket(3);
}

int EXPAND::digitalRead(byte pin){
  io_DataPacket[0] = DIGITALREAD;    // method
  io_DataPacket[1] = pin;  // pin
  sendDataPacket(2);
  int received = receiveResponse();
  return received;
}

void EXPAND::analogWrite(byte pin,byte val){
  io_DataPacket[0] = ANALOGWRITE;    // method
  io_DataPacket[1] = pin;  // pin
  io_DataPacket[2] = val;  // val
  sendDataPacket(3);
}

int EXPAND::analogRead(byte pin){
  io_DataPacket[0] = ANALOGREAD;    // method
  io_DataPacket[1] = pin;  // pin
  sendDataPacket(2);
  int received = receiveResponse();
  return received;
}

void EXPAND::pinMode(byte mode){
  io_DataPacket[0] = PINMODE;		//method
  io_DataPacket[1] = mode;	// pinMode
  sendDataPacket(2);
}

int EXPAND::status(byte reqValue) {
  io_DataPacket[0] = STATUS;
  io_DataPacket[1] = reqValue;
  sendDataPacket(1);
}
  void EXPAND::sendDataPacket(int reqBytes){
  Wire.beginTransmission(_addr);
  Wire.write(io_DataPacket, reqBytes);
  Wire.endTransmission(true);
  delay(1);
}

int EXPAND::receiveResponse(){
  unsigned int receivedValue;
  byte buffer[2];
  int available = Wire.requestFrom(_addr, (byte)2);
  buffer[0] = Wire.read();
  buffer[1] = Wire.read();
  receivedValue = buffer[0] << 8 | buffer[1];
  Serial.printf("Avail : %d, Rec : %d, b0 : %d, b1 : %d\r\n",available, receivedValue,buffer[0],buffer[1]);
  
  return receivedValue;  
}

