/**
 * @file teltonika_fmu130.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "BufferedSerial.h"
#include "mbed.h"
#include "teltonika_crc.hpp"

// extern Serial //myPC_debug.

// COMMANDS
/**
 * @brief 
 * 
 */
const int   FMU130_COMMAND          = 65;
const int   SERVER_COMMAND          = 64;
const char  FMU130_HEADER[]         = {0x42, 0x54, 0x46, 0x4D, '\0'};
const int   DESTINATION_SERVER      = 0x01;
const int   DESTINATION_FMU130      = 0x00;

/**
 * @brief 
 * 
 * @param puertoCOM 
 * @param m_buffer 
 * @return int 
 */
int read_avl_uart(BufferedSerial *puertoCOM, char m_buffer[1024]) {
    int w = 0;
    wait_us(10000);
    while (puertoCOM -> readable()) {
        char incoming_char = puertoCOM -> getc();
        m_buffer[w] = incoming_char;
        w++;
    }
    wait_us(600000);
    while (puertoCOM -> readable()) {
        char incoming_char = puertoCOM -> getc();
        m_buffer[w] = incoming_char;
        w++;
    }
    m_buffer[w] = '\0';
    return(w);
}

/**
 * @brief 
 * 
 * @param m_buffer 
 * @return int 
 */
int identify_fmu130_payload(char m_buffer[1024]) {
    int type_of_payload = -1;
    char *pch;

    pch = strchr(m_buffer, FMU130_COMMAND);
    if (pch!=NULL) {
        type_of_payload = 1;
    } 

    pch = strchr(m_buffer, SERVER_COMMAND);
    if (pch!=NULL) {
        type_of_payload = 2;
    }
    return(type_of_payload);
}




/**
 * @brief 
 * 
 * @param m_buffer 
 * @param puertoCOM 
 * @return true 
 * @return false 
 */

bool tx_fmu130_message(char m_buffer[64], BufferedSerial *puertoCOM) {
    
   
    /**
     * @brief   Nota sobre el Formateador %04hhX 
     *          Se utiliza el 0 para indicar que se deben mostrar los ceros a la izquierda
     *          Se utiliza el 4 para indicar que se deben mostrar cuatro caracteres en total
     *          Se utilizan las dos letras h para indicar que el argumento es unsigned char
     *          Se utiliza la X en mayúsculas para indicar que se utilizará mayúsculas para héxadecimal
     */
    
    int  j = (strlen(m_buffer));
    int  k = j+3;
    char i = 0x00;
    char tx_message[128];
    char middle_message[128];
    int my_buff_length = 0;
    
    // Ensamble de cadena parcial desde Length hasta el Payload
    //myPC_debug.printf("\r\nPayload: %s\r\n", m_buffer);
    //myPC_debug.printf("Longitud Payload: %d\r\n", j);
    
    sprintf(middle_message, "%c%c%c%s", DESTINATION_SERVER, i , j, m_buffer);
    
    int resultCRC = teltonika_crc16(middle_message,k);
    //myPC_debug.printf("CRC = %d - %04x\r\n", resultCRC, resultCRC);
    
    int hi_CRC = ((resultCRC & 0xFF00)>>8);
    int lo_CRC = resultCRC & 0x00FF;
    
    // Ensamble de trama final
    my_buff_length = sprintf(tx_message, "%s%c%c%c%s%c%c", FMU130_HEADER, DESTINATION_SERVER, i , j, m_buffer, hi_CRC, lo_CRC);
    puertoCOM->write(tx_message, my_buff_length);
    return(true);
}

bool tx_fmu130_command(const char m_buffer[64], BufferedSerial *puertoCOM) {
    int  j = (strlen(m_buffer));
    int  k = j+3;
    char i = 0x00;
    char tx_message[128];
    char middle_message[128];
    int my_buff_length = 0;
    
     // Ensamble de cadena parcial desde Length hasta el Payload
    //myPC_debug.printf("\r\nPayload: %s\r\n", m_buffer);
    //myPC_debug.printf("Longitud Payload: %d\r\n", j);
    
    k = sprintf(middle_message, "%c%c%c%s", DESTINATION_FMU130, i , j, m_buffer);
    
    int resultCRC = teltonika_crc16(middle_message,k);
    //myPC_debug.printf("CRC = %d - %04x\r\n", resultCRC, resultCRC);

    int hi_CRC = ((resultCRC & 0xFF00)>>8);
    int lo_CRC = resultCRC & 0x00FF;
    
    // Ensamble de trama final
    my_buff_length = sprintf(tx_message, "%s%c%c%c%s%c%c", FMU130_HEADER, DESTINATION_FMU130, i , j, m_buffer, hi_CRC, lo_CRC);
    puertoCOM->write(tx_message, my_buff_length);
    return(true);
}

bool tx_fmu130_var_command(char m_buffer[30], BufferedSerial *puertoCOM) {
    int  j = (strlen(m_buffer));
    int  k = j+3;
    char i = 0x00;
    char tx_message[128];
    char middle_message[128];
    int my_buff_length = 0;
    
     // Ensamble de cadena parcial desde Length hasta el Payload
    //myPC_debug.printf("\r\nPayload: %s\r\n", m_buffer);
    //myPC_debug.printf("Longitud Payload: %d\r\n", j);
    
    k = sprintf(middle_message, "%c%c%c%s", DESTINATION_FMU130, i , j, m_buffer);
    
    int resultCRC = teltonika_crc16(middle_message,k);
    //myPC_debug.printf("CRC = %d - %04x\r\n", resultCRC, resultCRC);

    int hi_CRC = ((resultCRC & 0xFF00)>>8);
    int lo_CRC = resultCRC & 0x00FF;
    
    // Ensamble de trama final
    my_buff_length = sprintf(tx_message, "%s%c%c%c%s%c%c", FMU130_HEADER, DESTINATION_FMU130, i , j, m_buffer, hi_CRC, lo_CRC);
    puertoCOM->write(tx_message, my_buff_length);
    return(true);
}