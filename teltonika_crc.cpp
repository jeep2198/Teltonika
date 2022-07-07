/**
 * @file    teltonika_crc.cpp
 * @author  Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date    2020-11-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

int teltonika_crc16(char buffer[], int bufLen) 
{
    int offset  = 0;
    int preset  = 0;
    int polynom = 0xA001;
    preset      &= 0xFFFF;
    polynom     &= 0xFFFF;

    int crc = preset;

    for (int i = 0; i < bufLen; i++) {
        int data = buffer[(i + offset) % bufLen] & 0xFF;
        crc ^= data;
        for (int j = 0; j < 8; j++) {
            if ((crc & 0x0001) != 0) {
                crc = (crc >> 1) ^ polynom;
            } else {
                crc = crc >> 1;
            }
        }
    }
    return crc & 0xFFFF;
}