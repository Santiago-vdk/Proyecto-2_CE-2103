#include "com.h"

com::com()
{
    QSerialPortInfo  serial=QSerialPortInfo("COM9");
    Port.setPort(serial);
    Port.setBaudRate(QSerialPort::Baud9600);
    Port.setDataBits(QSerialPort::Data8);
    Port.setFlowControl(QSerialPort::NoFlowControl);
    Port.setParity(QSerialPort::NoParity);
    Port.setStopBits(QSerialPort::OneStop);
    Port.open(QIODevice::ReadWrite);
}

void com::enviar(const char *info){
    Port.clear();
    std::string str(info);
    Port.write(info,str.length());
    Port.flush();
    Port.close();
}
