/*
       @file       Vars.h
       @brief      Declaración de variables y elementos usados en el programa

       @author     Jordi Gauchia

       @date       21/06/2022
*/


// **********************************************
//  Declaración funciones
// **********************************************
void init_ili9341();
void init_SPIFFS();
void touch_calibrate();
void init_encoder();
void get_encoder();
void Read_Encoder(void *pvParameters);
void set_I2S_mclk_pin(const uint8_t pin);
void set_I2S();
void process_Audio( void *pvParameters );