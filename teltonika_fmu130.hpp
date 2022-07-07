/**
 * @file teltonika_fmu130.hpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
 
#ifndef __TELTONIKA_FMU130_HPP
#define __TELTONIKA_FMU130_HPP

    // COMMANDS
    extern const int    FMU130_COMMAND;
    extern const int    SERVER_COMMAND;  
    extern const char   FMU130_HEADER[5];
    extern const int    DESTINATION_FMU130;
    extern const int    DESTINATION_SERVER;

    int read_avl_uart(BufferedSerial *puertoCOM, char m_buffer[1024]);
    int identify_fmu130_payload(char m_buffer[1024]);
    bool tx_fmu130_message(char m_buffer[64], BufferedSerial *puertoCOM);
    bool tx_fmu130_command(const char m_buffer[64], BufferedSerial *puertoCOM);
    bool tx_fmu130_var_command(char m_buffer[30], BufferedSerial *puertoCOM);
    
#endif // __TELTONIKA_FMU130_HPP