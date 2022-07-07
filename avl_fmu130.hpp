/**
 * @file avl_fmu130.hpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __AVL_FMU130_HPP
#define __AVL_FMU130_HPP

    extern const char FMU130_SEPARATOR[2];
    extern const char FM1U30_AVLID_IDLING[4];
    extern const char FM1U30_AVLID_WARNING_SPEED[3];
    extern const char FM1U30_AVLID_OVERSPEED[4];
    extern const char FM1U30_AVLID_CRASH[4];
    extern const char FM1U30_AVLID_JAMMING[4];
    extern const char FM1U30_AVLID_TOWING[4];
    extern const char FM1U30_AVLID_GREEN_DRIVING[4];
    extern const char FM1U30_AVLID_ACCELERATION[2];
    extern const char FM1U30_AVLID_BREAKING[2];
    extern const char FM1U30_AVLID_CORNERING[2];
    extern const char FM1U30_AVLID_EVENT_START[2];
    extern const char FM1U30_AVLID_EVENT_STOP[2];
    extern const char FMU130_START[2];
    extern const int  IMEI_LENGHT;
        
    bool verify_fmu130_payload(char payload[1024]);
    bool parse_fmu130_payload(char payload[1024], char header[2], char imei[16], int *cmd_fmu, int *param_fmu);

#endif // __AVL_FMU130_HPP