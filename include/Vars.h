/*
       @file       Vars.h
       @brief      Declaración de variables y elementos usados en el programa

       @author     Jordi Gauchia

       @date       21/06/2022
*/

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
void draw_spectrum();
void Compute_FFT();
void init_si5351();
char *freq_to_string_mhz(uint64_t input);
char *freq_to_string_hz(uint64_t input);
void GetPLLFreq();
void SendFrequency();