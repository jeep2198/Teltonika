/**
 * @file fingerprint_frame.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h" 
#include "fingerprint_frame.hpp"

/**
 * @brief 
 * 
 */

// CONSTANTES DE PROTOCOLO DE COMUNICACIÓN
const char  SERVER_SEPARATOR[]          = ";";
const char  FINGER_CMD_BEGIN[]          = "@";
const char  FINGER_CMD_EOF[]            = "#";

// COMANDOS DE HUELLA
const char  FINGERPRINT_DIS_CMD[]       = "FPF"; // DESHABILITAR HUELLA
const char  FINGERPRINT_ENA_CMD[]       = "FPN"; // HABILITAR HUELLA
const char  ADD_CMD[]                   = "ADD"; // AGREGAR HUELLA
const char  FINGERPRINT_QRY_CMD[]       = "ASK"; // INTERROGAR HUELLA
const char  Q_CHECK_ENROLLED_ID[]       = "CEI"; // query Check Enrolled fingerprint ID
const char  DEL_CMD[]                   = "DEL"; // ELIMINAR HUELLA
const char  Q_FINGERPRINT_STATUS[]      = "QFS"; // Query Fingerprint Status - 1 Enable, 0 Disable
const char  FP_OVERRIDE_ENABLE[]        = "FON"; // Fingerprint Override oN
const char  FP_OVERRIDE_DISABLE[]       = "FOF"; // Fingerprint Override oFF
const char  FP_OVERRIDE_COUNT[]         = "FOC"; // Fingerprint unauthorized Override Count
const char  Q_FP_OVERRIDE_CNT[]         = "QFO"; // Query Fingerprint Override

// COMANDOS DE PARLANTE
const char  VOL_CMD[]                   = "VOL"; // SET JQ8400 VOL
const char  Q_VOLUME_LEVEL[]            = "QVL"; // Query Volume level

// COMANDOS PARA SENSOR DE LLUVIA
const char  RAIN_ENA_CMD[]              = "RNN"; // RaiN oN
const char  RAIN_DIS_CMD[]              = "RNF"; // RaiN oFf
const char  Q_RAIN_SENSOR_STATUS[]      = "QRS"; // Query Rain Sensor Status - 1 Enable, 0 Disable
const char  CHANGE_RAIN_TIMER[]         = "RST"; // change Rain Sensor Timer
const char  Q_RAIN_TIMER[]              = "QRT"; // Query Rain Timer
const char  CHANGE_WSL_TXT[]            = "WSL"; // Wet Speed Limit
const char  CHANGE_WSW_TXT[]            = "WSW"; // Wet Speed Warning
const char  CHANGE_DSL_TXT[]            = "DSL"; // Dry Speed Limit
const char  CHANGE_DSW_TXT[]            = "DSW"; // Dry Speed Warning
const char  QUERY_SPEED_LIMIT[]         = "QSL"; // Query Speed Limit
const char  RAIN_SILENT_ENABLE[]        = "RSN"; //* Rain sensor Silent mode oN
const char  RAIN_SILENT_DISABLE[]       = "RSF"; //* Rain sensor Silent mode ofF
const char  RAIN_SILENT_QUERY[]         = "RSQ"; //* Rain sensor Silent mode Query

// COMANDOS PARA CINTURONES DE SEGURIDAD
const char  SEATBELT_ENA_CMD[]          = "SBN"; // SeatBelt reading oN
const char  SEATBELT_DIS_CMD[]          = "SBF"; // SeatBelt reading oFF
const char  SEATBELT_QUERY_CMD[]        = "SBQ"; // SeatBelt reading Query
const char  FORCE_BUCLKE_ENA_CMD[]      = "FBN"; // Force Buclke oN
const char  FORCE_BUCLKE_DIS_CMD[]      = "FBF"; // Force Buclke oFF
const char  Q_FORCE_SEATBELT_STATUS[]   = "FSS"; // query Force Seatbelt Status
const char  INPUT_NORMALLY_OPEN[]       = "INO"; // Inputs Normally Open
const char  INPUT_NORMALLY_CLOSE[]      = "INC"; // Inputs Normally Close
const char  Q_DIGITAL_INPUT_CONF[]      = "QDI"; // Query Digital Input Configuration
// Definición de cinturones Individual
const char  PILOT_BUCKLE_N_OPEN[4]      = "PBO"; // Pilot Buckle normally Open
const char  PILOT_BUCKLE_N_CLOSE[4]     = "PBC"; // Pilot Buckle normally Close
const char  Q_PILOT_BUCLE_TYPE[4]       = "QPB"; // Query Pilot Buckle type
const char  COPILOT_BUCKLE_N_OPEN[4]    = "CBO"; // Copilot Buckle normally Open
const char  COPILOT_BUCKLE_N_CLOSE[4]   = "CBC"; // Copilot Buckle normally Close
const char  Q_COPILOT_BUCLE_TYPE[4]     = "QCB"; // Query Copilot Buckle type
const char  CREW_BUCKLE_N_OPEN[4]       = "TBO"; // Crew Buckle normally Open
const char  CREW_BUCKLE_N_CLOSE[4]      = "TBC"; // Crew Buckle normally Close
const char  Q_CREW_BUCLE_TYPE[4]        = "QTB"; // Query Crew Buckle type

// COMANDOS DE RALENTI
const char  IDLE_SHUTDOWN_ENA_CMD[]     = "ISN"; // Idle Shutdown oN
const char  IDLE_SHUTDOWN_DIS_CMD[]     = "ISF"; // Idle Shutdown oFF
const char  IDLE_SHUTDOWN_QUERY[]       = "ISQ"; // Idle Shutdown Query
const char  Q_IDLE_SHUTDOWN_STATUS[]    = "ISS"; // query Idle Shutdown Status
const char  CHANGE_IDLE_TIMER[]         = "IST"; // Idle Shutdown Timer
const char  QUERY_IDLE_TIMER[]          = "QIT"; // Query Idle shutdown Timer
const char  IDLE_REMINDER_ENABLE[]      = "IRN"; // Idle Reminder oN
const char  IDLE_REMINDER_DISABLE[]     = "IRF"; // Idle Remider oFF
const char  QUERY_IDLE_REMINDER[]       = "QIR"; // Query Idle Reminder
const char  IDLE_REMINDER_TIMER[]       = "IRT"; // Idle Reminer Timer
const char  QUERY_IDLE_REMINDER_T[]     = "QRT"; // Query idle Reminder Timer

// COMANDOS DE TIP DE SEGURIDAD
const char  QUERY_SAFETY_TIP[]          = "QST"; // Query Safety Tip Time   
const char  CHANGE_SAFETY_TIME[]        = "STT"; // Safety Tip Time
const char  SAFETY_TIP_ENABLE[]         = "STN"; // Safety Tip oN
const char  SAFETY_TIP_DISABLE[]        = "STF"; // Safety Tip oFf

// COMANDOS DE VERSION DE ICS5
const char  Q_HARDWARE_VERSION[]        = "QHW"; // Query Hardware Version
const char  Q_FIRMWARE_VERSION[]        = "QFW"; // Query Firmware Version

// COMANDOS DE NOTIFICACION DE GEOCERCA
const char  GEO_WARNING_ENABLE[]        = "GWN"; //* Geozone Warning oN
const char  GEO_WARNING_DISABLE[]       = "GWF"; //* Geozone Warning ofF
const char  Q_GEO_WARNING_CONF[]        = "QGW"; //* Query Geozone Warning Status
const char  GEO_WARNING_GETIN[]         = "GNI"; //* Geozone Notification Inside
const char  GEO_WARNING_GETOUT[]        = "GNO"; //* Geozone Notification Outside
const char  GEO_WARNING_EVENT[]         = "GNE"; //* Geozone Notification Event

// COMANDOS DE AUTORESET BLUETOOTH
const char  BLE_AUTORESET_ENABLE[4]     = "BAN"; // Bluetooth Autoreset oN
const char  BLE_AUTORESET_DISABLE[4]    = "BAF"; // Bluetooth Autoreset ofF
const char  BLE_AUTORESET_TIME[4]       = "BAT"; // Bluetooth Autoreset change Time 
const char  BLE_AUTORESET_QUERY[4]      = "BAQ"; // Bluetooth Autoreset Query

// CONSTANTES DE CAMPOS DE TRAMA
const int   FINGER_CMD_START        = 1;
const int   FINGER_CMD_END          = 3;
const int   FINGER_ID_BEGIN         = 5;
const int   FINGER_ID_END           = 8;
const int   FINGER_PAYLOAD_EOL      = 9;
const int   FINGER_PAYLOAD_START    = 10;
const int   FINGER_PAYLOAD_END      = 1006;
 
/**
 * @brief 
 * 
 * @param cadena 
 * @return int 
 */
int strID_to_intID(char cadena[5]) {
    /*
    Esta función recibe una cadena de 5 posiciones
    multiplica cada posición de la cadena por su peso
    decimal y lo acumula en una variable de tipo long.
    La posición 5 no se opera por tratarse del caracter
    de fin de cadena \0.
    */
    int result = 0;
    int temp = 0;
 
    temp = (int) cadena[0];
    temp = temp - 48.0;
    temp = temp * 1000;
    result = result + temp;
 
    temp = (int) cadena[1];
    temp = temp - 48.0;
    temp = temp * 100;
    result = result + temp;
 
    temp = (int) cadena[2];
    temp = temp - 48.0;
    temp = temp * 10;
    result = result + temp;
 
    temp = (int) cadena[3];
    temp = temp - 48.0;
    result = result + temp;
 
    return(result);
}
 
/**
 * @brief 
 * 
 * @param payload 
 * @return true 
 * @return false 
 */
bool verify_finger_payload(char payload[1011]) {
    bool inicio_encontrado = false;  // Tipo Bool
    bool fin_encontrado = false;     // Tipo Bool
    char *ret;
 
    // Verificar si se encuentra el inicio del comando @
    ret = strchr(payload, FINGER_CMD_BEGIN[0]);
    if (ret!=NULL) {
        inicio_encontrado = true;
    }
 
    // Verificar si se encuentra el fin de comando #
    ret = strchr(payload, FINGER_CMD_EOF[0]);
    if (ret!=NULL) {
        fin_encontrado = 1;
    }
 
    if (inicio_encontrado && fin_encontrado) { // Trama para procesar
        return(true);
    } else  { // Trama para ignorar
        return(false);  
    }
}
 
/**
 * @brief 
 * 
 * @param payload 
 * @param comando 
 * @param id_huella 
 * @param huella_hex 
 * @return true 
 * @return false 
 */
bool parse_finger_payload(char payload[1011], char comando[4], int *id_huella, char huella_hex[997]) {
    char id_txt[5]; // Almacenar temporalmente el ID a procesar.
    char * pch;
    int i = 0;
    int j = 0;
    memset(id_txt, '\0', sizeof(id_txt));
    memset(huella_hex, '\0', sizeof(huella_hex));
    
    if (payload[0] == '@') {
        
        pch = strtok (payload, "@;#"); 
    
        while (pch != NULL) {
            j++;
            //debug -> printf("BLE - Puntero-%d = %s\r\n", j, pch);
            if (j == 1) {
                strcpy(comando, pch);
                //debug -> printf("BLE - Comando TXT = %s\r\n", comando);
            } else if (j ==2) {
                strcpy(id_txt, pch);
                //debug -> printf("BLE - ID TXT = %s\r\n", id_txt);
                *id_huella =  atoi(id_txt); 
                //debug -> printf("BLE - ID NUM=%d\r\n", *id_huella);
            } else if (j == 3) {
                strcpy(huella_hex, pch);
                //debug -> printf("BLE - Huella ASCII\r\n=%s\r\n\r\n", huella_hex);
            }
            pch = strtok (NULL, "@;#"); 
        }
        
        //debug -> printf("BLE - Repeticiones de Lazo = %d\r\n", j);  
        if (j == 4) { 
            //debug -> printf("BLE - Trama con Huella TRUE\r\n");
            return true;
        } else {
            //debug -> printf("BLE - Trama con Huella FALSE\r\n");
            return false;
        }
    }
    return true;
}

 
/**
 * @brief 
 * 
 * @param huella_hex 
 * @param huella_ascii 
 * @return true 
 * @return false 
 */
bool fingerprint_HEX2CHAR(char huella_hex[997], char huella_ascii[499]) {
    /*
    Esta función se encarga de analisar el payload de una
    huella que es enviada dentro de una cadena (char array)
    expresada de manera hexadecimal. en su equivalente de código
    ASCII que es guardado en otra cadena.
    */
 
    int i = 0;
    int j = 0;
    int k = 0;
    int limite = strlen(huella_hex);
    char pre_buffer[] = "--\0";
 
    for (i=0; i<limite; i++) {
        pre_buffer[j] = huella_hex[i];
        j++;
 
        if ((i%2)&&(i>=1)) { // Si es impar.
            j=0;
            huella_ascii[k] =  (int)strtol(pre_buffer, NULL, 16);
            k++;
        }
    }
    return(true);
}

/**
 * @brief 
 * 
 * @param comando 
 * @return int 
 */
int identify_server_cmd(char comando[4]) {
    /*
       Esta función se encarga de verificar que el comando a ejecutar es soportado
       por el código y que no se ha generado una mala interpretación de la trama
       al momento de extraer los caracteres correspondientes al comando.
       Esta función retorna 1 si el comando es ADD. Retorna 2 para el comando DEL.
       Retorna 0 si no es ninguno de los dos.
    */
    char* p; 
    int comand_int = 0;


    /** **********************************
     *  COMANDOS DE GEOCERCA
     *  ********************************** */
    p = strstr(comando, GEO_WARNING_GETIN);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_GETIN;
        return(comand_int);
    }

    p = strstr(comando, GEO_WARNING_GETOUT);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_GETOUT;
        return(comand_int);
    }

    p = strstr(comando, GEO_WARNING_EVENT);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_EVENT;
        return(comand_int);
    }

    p = strstr(comando, GEO_WARNING_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, GEO_WARNING_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, Q_GEO_WARNING_CONF);
    if (p!=NULL) {
        comand_int = CMD_GEO_WARNING_QUERY;
        return(comand_int);
    }



    /** **********************************
     *  COMANDOS DE LECTOR DE HUELLA
     *  ********************************** */
    p = strstr(comando, ADD_CMD);
    if (p!=NULL) {
        comand_int = CMD_FINGER_ADD;
        return(comand_int);
    } 

    p = strstr(comando, DEL_CMD);
    if (p!=NULL) {
        comand_int = CMD_FINGER_DELETE;
        return(comand_int);
    }

    p = strstr(comando, FINGERPRINT_DIS_CMD);
    if (p!=NULL) {
        comand_int = CMD_FINGER_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, FINGERPRINT_ENA_CMD);
    if (p!=NULL) {
        comand_int = CMD_FINGER_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, Q_FINGERPRINT_STATUS);
    if (p!=NULL) {
        comand_int = CMD_FINGERPRINT_QUERY;
        return(comand_int);
    }

    p = strstr(comando, FINGERPRINT_QRY_CMD);
    if (p!=NULL) {
        comand_int = CMD_FINGER_ENROLL_CNT;
        return(comand_int);
    }

    p = strstr(comando, Q_CHECK_ENROLLED_ID);
    if (p!=NULL) {
        comand_int = CMD_CHECK_ENROLLED_ID;
        return(comand_int);
    }

    p = strstr(comando, FP_OVERRIDE_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_FP_OVERRIDE_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, FP_OVERRIDE_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_FP_OVERRIDE_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, FP_OVERRIDE_COUNT);
    if (p!=NULL) {
        comand_int = CMD_FP_OVERRIDE_COUNT;
        return(comand_int);
    }

    p = strstr(comando, Q_FP_OVERRIDE_CNT);
    if (p!=NULL) {
        comand_int = CMD_FP_OVERRIDE_QUERY;
        return(comand_int);
    }


    
    /** **********************************
     *  COMANDOS DE PARLANTE
     *  ********************************** */
    p = strstr(comando, VOL_CMD);
    if (p!=NULL) {
        comand_int = CMD_SET_VOLUME;
        return(comand_int);
    }

    p = strstr(comando, Q_VOLUME_LEVEL);
    if (p!=NULL) {
        comand_int = CMD_QUERY_VOLUME_LEVEL;
        return(comand_int);
    }



    /** **********************************
     *  COMANDOS DE SENSOR DE LLUVIA
     *  ********************************** */
    p = strstr(comando, RAIN_ENA_CMD);
    if (p!=NULL) {
        comand_int = CMD_RAIN_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, RAIN_DIS_CMD);
    if (p!=NULL) {
        comand_int = CMD_RAIN_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, Q_RAIN_SENSOR_STATUS);
    if (p!=NULL) {
        comand_int = CMD_RAIN_QUERY;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_RAIN_TIMER);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_RAIN_TIMER;
        return(comand_int);
    }

    p = strstr(comando, Q_RAIN_TIMER);
    if (p!=NULL) {
        comand_int = CMD_QUERY_RAIN_TIMER;
        return(comand_int);
    }

    p = strstr(comando, RAIN_SILENT_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_RAIN_SILENT_MODE_ENA;
        return(comand_int);
    }

    p = strstr(comando, RAIN_SILENT_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_RAIN_SILENT_MODE_DIS;
        return(comand_int);
    }

    p = strstr(comando, RAIN_SILENT_QUERY);
    if (p!=NULL) {
        comand_int = CMD_RAIN_SILENT_MODE_Q;
        return(comand_int);
    }




    /** **********************************
     *  COMANDOS DE LIMITE DE VELOCIDAD
     *  ********************************** */
    p = strstr(comando, CHANGE_WSL_TXT);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_WSL;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_WSW_TXT);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_WSW;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_DSL_TXT);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_DSL;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_DSW_TXT);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_DSW;
        return(comand_int);
    }

    p = strstr(comando, QUERY_SPEED_LIMIT);
    if (p!=NULL) {
        comand_int = CMD_QUERY_SPEED_LIMIT;
        return(comand_int);
    }




    /** **********************************
     *  COMANDOS DE CINTURON DE SEGURIDAD
     *  ********************************** */
    p = strstr(comando, SEATBELT_ENA_CMD);
    if (p!=NULL) {
        comand_int = CMD_SEATBELT_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, SEATBELT_DIS_CMD);
    if (p!=NULL) {
        comand_int = CMD_SEATBELT_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, SEATBELT_QUERY_CMD);
    if (p!=NULL) {
        comand_int = CMD_SEATBELT_QUERY;
        return(comand_int);
    }

    p = strstr(comando, FORCE_BUCLKE_ENA_CMD);
    if (p!=NULL) {
        comand_int = CMD_FORCE_BUCLKE_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, FORCE_BUCLKE_DIS_CMD);
    if (p!=NULL) {
        comand_int = CMD_FORCE_BUCLKE_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, Q_FORCE_SEATBELT_STATUS);
    if (p!=NULL) {
        comand_int = CMD_QUERY_FORCE_SEATBELT;
        return(comand_int);
    }

    p = strstr(comando, INPUT_NORMALLY_OPEN);
    if (p!=NULL) {
        comand_int = CMD_SET_INPUT_NORMAL_O;
        return(comand_int);
    }

    p = strstr(comando, INPUT_NORMALLY_CLOSE);
    if (p!=NULL) {
        comand_int = CMD_SET_INPUT_NORMAL_C;
        return(comand_int);
    }

    p = strstr(comando, Q_DIGITAL_INPUT_CONF);
    if (p!=NULL) {
        comand_int = CMD_QUERY_DIN_CONFIG;
        return(comand_int);
    }

    p = strstr(comando, PILOT_BUCKLE_N_OPEN);
    if (p!=NULL) {
        comand_int = CMD_PILOT_BUCKLE_NO;
        return(comand_int);
    }

    p = strstr(comando, PILOT_BUCKLE_N_CLOSE);
    if (p!=NULL) {
        comand_int = CMD_PILOT_BUCKLE_NC;
        return(comand_int);
    }

    p = strstr(comando, Q_PILOT_BUCLE_TYPE);
    if (p!=NULL) {
        comand_int = CMD_QUERY_PILOT_BT;
        return(comand_int);
    }

    p = strstr(comando, COPILOT_BUCKLE_N_OPEN);
    if (p!=NULL) {
        comand_int = CMD_COPILOT_BUCKLE_NO;
        return(comand_int);
    }

    p = strstr(comando, COPILOT_BUCKLE_N_CLOSE);
    if (p!=NULL) {
        comand_int = CMD_COPILOT_BUCKLE_NC;
        return(comand_int);
    }

    p = strstr(comando, Q_COPILOT_BUCLE_TYPE);
    if (p!=NULL) {
        comand_int = CMD_QUERY_COPILOT_BT;
        return(comand_int);
    }

    p = strstr(comando, CREW_BUCKLE_N_OPEN);
    if (p!=NULL) {
        comand_int = CMD_CREW_BUCKLE_NO;
        return(comand_int);
    }

    p = strstr(comando, CREW_BUCKLE_N_CLOSE);
    if (p!=NULL) {
        comand_int = CMD_CREW_BUCKLE_NC;
        return(comand_int);
    }

    p = strstr(comando, Q_CREW_BUCLE_TYPE);
    if (p!=NULL) {
        comand_int = CMD_QUERY_CREW_BT;
        return(comand_int);
    }




    /** **********************************
     *  COMANDOS DE APAGADO POR RALENTI
     *  ********************************** */
    p = strstr(comando, IDLE_SHUTDOWN_ENA_CMD);
    if (p!=NULL) {
        comand_int = CMD_IDLE_SHUTDOWN_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, IDLE_SHUTDOWN_DIS_CMD);
    if (p!=NULL) {
        comand_int = CMD_IDLE_SHUTDOWN_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, IDLE_SHUTDOWN_QUERY);
    if (p!=NULL) {
        comand_int = CMD_IDLE_SHUTDOWN_QUERY;
        return(comand_int);
    }

    p = strstr(comando, Q_IDLE_SHUTDOWN_STATUS);
    if (p!=NULL) {
        comand_int = CMD_IDLE_SHUTDOWN_QUERY;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_IDLE_TIMER);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_IDLE_SHUTDOWN_T;
        return(comand_int);
    }

    p = strstr(comando, QUERY_IDLE_TIMER);
    if (p!=NULL) {
        comand_int = CMD_QUERY_IDLE_SHUTDOWN_T;
        return(comand_int);
    }

    


    /** **********************************
     *  COMANDOS DE RECORDATORIO POR RALENTI
     *  ********************************** */
    p = strstr(comando, IDLE_REMINDER_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_IDLE_REMINDER_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, IDLE_REMINDER_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_IDLE_REMINDER_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, QUERY_IDLE_REMINDER);
    if (p!=NULL) {
        comand_int = CMD_IDLE_REMINDER_QUERY;
        return(comand_int);
    }

    p = strstr(comando, IDLE_REMINDER_TIMER);
    if (p!=NULL) {
        comand_int = CMD_CHANGE_IDLE_REMINDER_T;
        return(comand_int);
    }        

    p = strstr(comando, QUERY_IDLE_REMINDER_T);
    if (p!=NULL) {
        comand_int = CMD_QUERY_IDLE_REMINDER_T;
        return(comand_int);
    }




    /** **********************************
     *  COMANDOS DE TIP DE SEGURIDAD
     *  ********************************** */
    p = strstr(comando, SAFETY_TIP_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_SAFETY_TIP_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, SAFETY_TIP_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_SAFETY_TIP_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, QUERY_SAFETY_TIP);
    if (p!=NULL) {
        comand_int = CMD_QUERY_SAFETY_TIP_TIME;
        return(comand_int);
    }

    p = strstr(comando, CHANGE_SAFETY_TIME);
    if (p!=NULL) {
        comand_int = CHANGE_SAFETY_TIP_TIME;
        return(comand_int);
    }




    /** **********************************
     *  COMANDOS SOBRE INFO DE ICS5
     *  ********************************** */
    p = strstr(comando, Q_HARDWARE_VERSION);
    if (p!=NULL) {
        comand_int = CMD_QUERY_HARDWARE_VER;
        return(comand_int);
    }

    p = strstr(comando, Q_FIRMWARE_VERSION);
    if (p!=NULL) {
        comand_int = CMD_QUERY_FIRMWARE_VER;
        return(comand_int);
    }

    
    

    /** **********************************
     *  COMANDOS DE AUTORESET DE BLUETOOTH
     *  ********************************** */
    p = strstr(comando, BLE_AUTORESET_ENABLE);
    if (p!=NULL) {
        comand_int = CMD_BLE_AUTORESET_ENABLE;
        return(comand_int);
    }

    p = strstr(comando, BLE_AUTORESET_DISABLE);
    if (p!=NULL) {
        comand_int = CMD_BLE_AUTORESET_DISABLE;
        return(comand_int);
    }

    p = strstr(comando, BLE_AUTORESET_TIME);
    if (p!=NULL) {
        comand_int = CMD_BLE_AUTORESET_TIME;
        return(comand_int);
    }

    p = strstr(comando, BLE_AUTORESET_QUERY);
    if (p!=NULL) {
        comand_int = CMD_BLE_AUTORESET_QUERY;
        return(comand_int);
    }

    return(comand_int);
}
