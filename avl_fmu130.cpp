/**
 * @file avl_fmu130.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h"
#include "avl_fmu130.hpp"

// Teltonika AVL ID Events
    const char FM1U30_SEPARATOR[]               = ",";
    const char FM1U30_AVLID_IDLING[]           = "251";
    const char FM1U30_AVLID_WARNING_SPEED[]    = "24";
    const char FM1U30_AVLID_OVERSPEED[]        = "255";
    const char FM1U30_AVLID_CRASH[]            = "317";
    const char FM1U30_AVLID_JAMMING[]          = "249";
    const char FM1U30_AVLID_TOWING[]           = "246";
    const char FM1U30_AVLID_GREEN_DRIVING[]    = "253";
    const char FM1U30_AVLID_ACCELERATION[]     = "1";
    const char FM1U30_AVLID_BREAKING[]         = "2";
    const char FM1U30_AVLID_CORNERING[]        = "3";
    const char FM1U30_AVLID_EVENT_START[]      = "1";
    const char FM1U30_AVLID_EVENT_STOP[]       = "0";
    const char FMU130_START[]           = "A";
    const int  IMEI_LENGHT               = 15;

/**
 * @brief 
 * 
 * @param payload 
 * @return true 
 * @return false 
 */
bool verify_fmu130_payload(char payload[1024]) {
    bool a_encontrada = false;  // Tipo Bool
    bool coma_encontrada = false;     // Tipo Bool
    char *ret;

    // Verificar si se encuentra el inicio del comando A
    ret = strchr(payload, FMU130_START[0]);
    if (ret!=NULL) {
        a_encontrada = true;
    }

    // Verificar si se encuentra el separador "," 
    ret = strchr(payload, FM1U30_SEPARATOR[0]);
    if (ret!=NULL) {
        coma_encontrada = true;
    }

    // a_encontrada el tamaño de la trama
    if (a_encontrada && coma_encontrada) { // Trama para procesar
        return(true);
    } else  { // Trama para ignorar
        return(false);  
    }
}

/**
 * @brief 
 * 
 * @param payload 
 * @param header 
 * @param imei 
 * @param cmd_fmu 
 * @param param_fmu 
 * @return true 
 * @return false 
 */
bool parse_fmu130_payload(char payload[1024], char header[2], char imei[16], int *cmd_fmu, int *param_fmu) {
    int i = 0;
    char avl_id[4];
    char status[2];
    char *p;


    p = strtok(payload, FM1U30_SEPARATOR);
    strcpy(header,p);

    while (p != NULL) {
        i++;
        p = strtok(NULL, FM1U30_SEPARATOR);
        switch(i) {
            case 1:
                strcpy(imei,p);
                break;
            
            case 2:
                strcpy(avl_id,p); // ["01","3D",'\0']
                *cmd_fmu = atoi(avl_id); // "3" "1" "7" ==> 317
                if (*cmd_fmu == 0) {
                    if (strlen(avl_id) >= 2) {
                        *cmd_fmu = 256 + (int) avl_id[1]; 
                    } else {
                        *cmd_fmu = (int) avl_id[0]; 
                    }
                }
                break;

            case 3:
                strcpy(status,p);
                *param_fmu = atoi(status);
                if (*param_fmu == 0) {
                    *param_fmu = (int) status[0];
                }
                break;
        }
    }
    return(true);
}
