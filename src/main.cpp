/*
       @file       main.cpp
       @brief      SDR con ESP32 + ILI9341 + PCM1808 + PCM5102 + SI5351

       @author     Jordi Gauchia

       @date       21/06/2022

       Pinout:
       ILI9341        MICRO SD       ENCODER          PCM1808            PCM5102         I2C
       -----------------------------------------------------------------------------------------------------
       VCC  3,3v      VCC  3,3v      VCC  3,3v        VCC   3,3v-5v      VCC   5v        SCL   GPIO22
       GND  GND       GND  GND       GND  GND         GND   GND          GND   GND       SCA   GPIO21
       LED  3,3v      CS   GPIO4     A    GPIO16      BCK   GPIO26       SCK   GPIO0
       MISO GPIO27    MISO GPIO27    B    GPIO17      OUT   GPIO35       BCK   GPIO26
       SCK  GPIO14    SCK  GPIO14    SW   GPIO9       LRC   GPIO33       DIN   GPIO25
       MOSI GPIO13    MOSI GPIO13                     SCK   GPIO0        LCK   GPIO33
       DC   GPIO15
       RST  GPIO32
       CS   GPIO2
       T_CS GPIO18


       Librerías:
       SI5351  :  https://github.com/etherkit/Si5351Arduino
       ILI9341 :  https://github.com/Bodmer/TFT_eSPI
       ENCODER :  https://github.com/madhephaestus/ESP32Encoder
       FFT     :  https://github.com/kosme/arduinoFFT
*/

#include <Arduino.h>
#include "si5351.h"
#include "Wire.h"
#include <ESP32Encoder.h>
#include "arduinoFFT.h"
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <SD.h>
#include "driver/i2s.h"

#include "Vars.h"
#include "Conv_func.h"
#include "I2S_ADC_DAC.h"
#include "FFT.h"
#include "TFT.h"
#include "SI5351.h"
#include "ENCODER.h"
#include "UI/MAINSCREEN.h"

void setup()
{
  /* Inicializar DAC y ADC y procesar audio*/
  set_I2S();
  set_I2S_mclk_pin(MCK);
  xTaskCreatePinnedToCore(process_Audio, "process_Audio", 4096, NULL, 10, NULL, 0);

  /* Inicializar Puerto Serie*/
  Serial.begin(115200);

  /* Inicializar TFT*/
  init_SPIFFS();
  init_ili9341();
  touch_calibrate();

  /* Inicializar encoder*/
  init_encoder();
  xTaskCreatePinnedToCore(Read_Encoder, "Read Encoder", 4096, NULL, 4, NULL, 0);

  /* Inicializar SI5351*/
  init_si5351();
  si5351.set_freq(freq, SI5351_CLK0);
  si5351.update_status();
}

void loop()
{

  if (step_change)
  {
    step_change = false;
  }

  if (freq_change)
  {
    // update_freq(step_idx, freq);
    si5351.set_freq(freq, SI5351_CLK0);
    freq_change = false;
  }

  si5351.update_status();
  Compute_FFT();
  update_main_screen();
}