/**
 * @file fingerprint_frame.hpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __FINGERPRINT_FRAME_HPP
#define __FINGERPRINT_FRAME_HPP


    // Definiciones
    /**
     * @brief 
     * 
     */

    // Tipo de trama
    #define TRAMA_AVL_FMU130        1
    #define TRAMA_SERVIDOR          2

    // Eventos AVL
    #define AVLID_OVERSPEED         24
    #define AVLID_TOWING            246
    #define AVLID_JAMMING           249
    #define AVLID_IDLE              251
    #define AVLID_HARSH_BEHAVIOUR   253
    #define AVLID_WARNING_SPEED     255
    #define AVLID_CRASH             317

    // ID Comandos Lector de Huellas
    #define CMD_FINGER_ADD              1
    #define CMD_FINGER_DELETE           2
    #define CMD_FINGER_DISABLE          3
    #define CMD_FINGER_ENABLE           4
    #define CMD_FINGERPRINT_QUERY       5
    #define CMD_FINGER_ENROLL_CNT       6
    #define CMD_CHECK_ENROLLED_ID       7

    // ID Comandos Anulación de Lector de Huella
    #define CMD_FP_OVERRIDE_ENABLE      8
    #define CMD_FP_OVERRIDE_DISABLE     9
    #define CMD_FP_OVERRIDE_QUERY       10
    #define CMD_FP_OVERRIDE_COUNT       11

    // ID Comandos de Parlante
    #define CMD_SET_VOLUME              12
    #define CMD_QUERY_VOLUME_LEVEL      13

    // ID Comandos de Sensor de Lluvia
    #define CMD_RAIN_ENABLE             14
    #define CMD_RAIN_DISABLE            15
    #define CMD_RAIN_QUERY              16
    #define CMD_CHANGE_WSL              17
    #define CMD_CHANGE_WSW              18
    #define CMD_CHANGE_DSL              19
    #define CMD_CHANGE_DSW              20
    #define CMD_QUERY_SPEED_LIMIT       21
    #define CMD_CHANGE_RAIN_TIMER       22
    #define CMD_QUERY_RAIN_TIMER        23
    #define CMD_RAIN_SILENT_MODE_ENA    24
    #define CMD_RAIN_SILENT_MODE_DIS    25
    #define CMD_RAIN_SILENT_MODE_Q      26


    // ID Comandos de Cinturones
    #define CMD_SEATBELT_ENABLE         27
    #define CMD_SEATBELT_DISABLE        28
    #define CMD_SEATBELT_QUERY          29
    #define CMD_FORCE_BUCLKE_ENABLE     30
    #define CMD_FORCE_BUCLKE_DISABLE    31
    #define CMD_QUERY_FORCE_SEATBELT    32
    #define CMD_SET_INPUT_NORMAL_O      33
    #define CMD_SET_INPUT_NORMAL_C      34
    #define CMD_QUERY_DIN_CONFIG        35
    #define CMD_PILOT_BUCKLE_NO         36
    #define CMD_PILOT_BUCKLE_NC         37
    #define CMD_COPILOT_BUCKLE_NO       38
    #define CMD_COPILOT_BUCKLE_NC       39
    #define CMD_CREW_BUCKLE_NO          40
    #define CMD_CREW_BUCKLE_NC          41
    #define CMD_QUERY_PILOT_BT          42
    #define CMD_QUERY_COPILOT_BT        43
    #define CMD_QUERY_CREW_BT           44

  
    // ID Comandos de Apagado por Ralenti
    #define CMD_IDLE_SHUTDOWN_ENABLE    45
    #define CMD_IDLE_SHUTDOWN_DISABLE   46
    #define CMD_IDLE_SHUTDOWN_QUERY     47
    #define CMD_QUERY_IDLE_SHUTDOWN_T   48
    #define CMD_CHANGE_IDLE_SHUTDOWN_T  49

    // ID Comandos de Recordatorio por Ralenti
    #define CMD_IDLE_REMINDER_ENABLE    50
    #define CMD_IDLE_REMINDER_DISABLE   51
    #define CMD_IDLE_REMINDER_QUERY     52
    #define CMD_CHANGE_IDLE_REMINDER_T  53
    #define CMD_QUERY_IDLE_REMINDER_T   54
    
    // ID Comandos de Tip de Seguridad
    #define CMD_SAFETY_TIP_ENABLE       55
    #define CMD_SAFETY_TIP_DISABLE      56
    #define CMD_SAFETY_TIP_QUERY        57
    #define CMD_QUERY_SAFETY_TIP_TIME   58
    #define CHANGE_SAFETY_TIP_TIME      59
     
    // ID Comandos de información ICS
    #define CMD_QUERY_HARDWARE_VER      60
    #define CMD_QUERY_FIRMWARE_VER      61

    // ID Comandos para Notificacion de Geocercas
    #define CMD_GEO_WARNING_ENABLE      62
    #define CMD_GEO_WARNING_DISABLE     63
    #define CMD_GEO_WARNING_QUERY       64
    #define CMD_GEO_WARNING_GETIN       65
    #define CMD_GEO_WARNING_GETOUT      66
    #define CMD_GEO_WARNING_EVENT       67
    
    // ID Comandos para Autoreset de Bluetooth
    #define CMD_BLE_AUTORESET_ENABLE    68
    #define CMD_BLE_AUTORESET_DISABLE   69
    #define CMD_BLE_AUTORESET_TIME      70
    #define CMD_BLE_AUTORESET_QUERY     71

    // Cadenas de comandos
    extern const char   SERVER_SEPARATOR[2];
    extern const char   FINGER_CMD_BEGIN[2];
    extern const char   FINGER_CMD_EOF[2];

    // Cadenas CMD de Lector de Huella
    extern const char   ADD_CMD[4];
    extern const char   DEL_CMD[4];
    extern const char   FINGERPRINT_DIS_CMD[4]; 
    extern const char   FINGERPRINT_ENA_CMD[4]; 
    extern const char   FINGERPRINT_QRY_CMD[4];
    extern const char   FP_OVERRIDE_ENABLE[4];
    extern const char   FP_OVERRIDE_DISABLE[4];
    extern const char   FP_OVERRIDE_COUNT[4];
    extern const char   Q_FP_OVERRIDE_CNT[4];

    // Cadenas CMD de Sensor de Lluvia
    extern const char   RAIN_ENA_CMD[4];
    extern const char   RAIN_DIS_CMD[4];
    extern const char   CHANGE_RAIN_TIMER[4]; 
    extern const char   Q_RAIN_TIMER[4]; 
    extern const char   RAIN_SILENT_ENABLE[4];
    extern const char   RAIN_SILENT_DISABLE[4];
    extern const char   RAIN_SILENT_QUERY[4];  
    
    // Cadenas CMD para Limites de Velocidad
    extern const char   CHANGE_WSL_TXT[4];
    extern const char   CHANGE_WSW_TXT[4];
    extern const char   CHANGE_DSL_TXT[4];
    extern const char   CHANGE_DSW_TXT[4];
    extern const char   QUERY_SPEED_LIMIT[4];

    // Cadenas CMD Cinturones de Seguridad
    extern const char   SEATBELT_ENA_CMD[4];
    extern const char   SEATBELT_DIS_CMD[4];
    extern const char   SEATBELT_QUERY_CMD[4];
    extern const char   FORCE_BUCLKE_ENA_CMD[4];
    extern const char   FORCE_BUCLKE_DIS_CMD[4];
    extern const char   INPUT_NORMALLY_OPEN[4];
    extern const char   INPUT_NORMALLY_CLOSE[4];
    extern const char   Q_DIGITAL_INPUT_CONF[4]; 
    extern const char   PILOT_BUCKLE_N_OPEN[4];
    extern const char   PILOT_BUCKLE_N_CLOSE[4];
    extern const char   Q_PILOT_BUCLE_TYPE[4];
    extern const char   COPILOT_BUCKLE_N_OPEN[4];
    extern const char   COPILOT_BUCKLE_N_CLOSE[4];
    extern const char   Q_COPILOT_BUCLE_TYPE[4];
    extern const char   CREW_BUCKLE_N_OPEN[4];
    extern const char   CREW_BUCKLE_N_CLOSE[4];
    extern const char   Q_CREW_BUCLE_TYPE[4];

    // Cadenas CMD Apagado por Ralentí
    extern const char   IDLE_SHUTDOWN_ENA_CMD[4];
    extern const char   IDLE_SHUTDOWN_DIS_CMD[4];
    extern const char   IDLE_SHUTDOWN_QUERY[4];
    extern const char   CHANGE_IDLE_TIMER[4];
    extern const char   QUERY_IDLE_TIMER[4];

    // Cadenas CMD Recordatorio por Ralentí
    extern const char   IDLE_REMINDER_ENABLE[4];
    extern const char   IDLE_REMINDER_DISABLE[4];
    extern const char   QUERY_IDLE_REMINDER[4];
    extern const char   IDLE_REMINDER_TIMER[4];
    extern const char   QUERY_IDLE_REMINDER_T[4];

    // Cadenas CMD de Volumen
    extern const char   VOL_CMD[4];
    
    // Cadenas CMD para Geocercas
    extern const char  GEO_WARNING_ENABLE[4];
    extern const char  GEO_WARNING_DISABLE[4];
    extern const char  Q_GEO_WARNING_CONF[4];
    extern const char  GEO_WARNING_GETIN[4];
    extern const char  GEO_WARNING_GETOUT[4];
    extern const char  GEO_WARNING_EVENT[4];

    // Cadenas CMD para Autoreset de BLE
    extern const char  BLE_AUTORESET_ENABLE[4];
    extern const char  BLE_AUTORESET_DISABLE[4];
    extern const char  BLE_AUTORESET_TIME[4];
    extern const char  BLE_AUTORESET_QUERY[4];
    
    // Tramas
    extern const int    FINGER_CMD_START;
    extern const int    FINGER_CMD_END;
    extern const int    FINGER_ID_BEGIN;
    extern const int    FINGER_ID_END;
    extern const int    FINGER_PAYLOAD;
    extern const int    FINGER_PAYLOAD_EOL;
    extern const int    FINGER_PAYLOAD_START;
    extern const int    FINGER_PAYLOAD_END;

    // Funciones
    int strID_to_intID(char cadena[5]);
    bool verify_finger_payload(char payload[1011]);
    int strID_to_intID(char cadena[5]);
    bool parse_finger_payload(char payload[1011], char comando[4], int *id_huella, char huella_hex[997]);
    bool fingerprint_HEX2CHAR(char huella_hex[997], char huella_ascii[499]);
    int identify_server_cmd(char comando[4]);

#endif // __FINGERPRINT_FRAME_HPP