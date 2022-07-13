/*
       @file       Vars.h
       @brief      Declaración de variables y elementos usados en el programa

       @author     Jordi Gauchia

       @date       21/06/2022
*/

// **********************************************
//  Declaración variables
// **********************************************
bool REPEAT_CAL = false;
#define CALIBRATION_FILE "/TouchCalData1"
#define BKG_COLOUR TFT_BLACK
#define FREQ_FONT_COLOUR TFT_WHITE
#define STATUS_FONT_COLOUR TFT_YELLOW
#define FREQ_WIDTH  230
#define FREQ_HEIGHT 50
#define FREQ_POS_X  140
#define FREQ_POS_Y  65
#define STATUS_WIDTH 480
#define STATUS_HEIGHT 8


// **********************************************
//  Declaración funciones
// **********************************************
void init_TFT();
void init_SPIFFS();
void touch_calibrate();
void init_encoder();
void get_encoder();
void Read_Encoder(void *pvParameters);
void set_I2S_mclk_pin(const uint8_t pin);
void set_I2S();
void process_Audio(void *pvParameters);
void update_freq_main_screen();
void update_status_main_screen();
void draw_spectrum();
void Compute_FFT();
void init_si5351();
char *freq_to_string_mhz(uint64_t input);
char *freq_to_string_hz(uint64_t input);
void GetPLLFreq();
void SendFrequency();