/**
 * Stuctures and Functions for managing data products that are
 * produced by the PANOSETI project.
 * These include
 * 16 bit Imaging data
 *      --exposure using 16 bit counters
 * 8 bit Imaging data
 *      --exposure using 8 bit counters
 * Pulse Height data
 *      --triggered events which exceeed a predefined threshold
 * Dynamic Metadata
 *      --metadata generated by numerous instruments which is 
 *        subsequently logged by the data acquisition software
 *        These values are usually updated regularly throughout
 *        the observation
 * Static Metadata
 *      --metdata generated once per observational run and will
 *        rarely ever change for that observational run
 **/

#include <stdint.h>

#define PIXELSIZE 256
#define QUABOPERMODULE 4

#define WRPORTS 18

#define STRBUFFER 1024

/**
 * The instrinsic data format from the quabos.
 **/
struct DataHeader{
    char acq_mode;
    uint16_t pkt_num;
    uint16_t mod_num;
    uint8_t qua_num;
    uint32_t pkt_utc;
    uint32_t pkt_nsec;
    long int tv_sec;
    long int tv_usec;
};

struct bit16Img : DataHeader {
    char frame_data[PIXELSIZE*QUABOPERMODULE*2];
};

struct bit8Img : DataHeader {
    char frame_data[PIXELSIZE*QUABOPERMODULE];
};

struct PHData : DataHeader {
    char frame_data[PIXELSIZE];
};

struct GPSPrimary {
    char gps_time[STRBUFFER];
    uint32_t time_of_week;
    uint16_t week_number;
    int16_t utc_offset;
    char time_flag[STRBUFFER];
    char pps_flag[STRBUFFER];
    uint8_t time_set;
    uint8_t utc_info;
    uint8_t time_from_gps;
    char tv_sec[STRBUFFER];
};

struct GPSSecondary {
    char reciever_mode[STRBUFFER];
    char disciplining_mode[STRBUFFER];
    uint8_t self_survey_progress;
    uint32_t holdover_duration;
    uint8_t dac_at_rail;
    uint8_t dac_near_rail;
    uint8_t antenna_open;
    uint8_t antenna_shorted;
    uint8_t not_tracking_sat;
    uint8_t not_disciplining_osc;
    uint8_t survey_in_progress;
    uint8_t no_stored_position;
    uint8_t leap_second_pending;
    uint8_t in_test_mode;
    uint8_t position_questionable;
    uint8_t eeprom_corrupt;
    uint8_t almanac_not_complete;
    uint8_t pps_not_generated;
    char gps_decoding_status[STRBUFFER];
    char disciplining_activity[STRBUFFER];
    uint8_t spare_status1;
    uint8_t spare_status2;
    float pps_offset; //in units of ns
    float clock_offset; //in units of ppb
    uint32_t dac_value;
    float dac_volage;
    float temperature;
    double latitude;
    double longitude;
    double altitude;
    float pps_quantization_error;
    uint32_t spare;
};

struct GPSMeta{
    GPSPrimary gps_primary;
    GPSSecondary gps_secondary;
};

struct WRMeta {
    uint8_t port_status[18];
};

struct DyanmicMeta {
    GPSMeta gps_metadata;
    WRMeta wr_metadata;
};

struct StaticMeta {

};