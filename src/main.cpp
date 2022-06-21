/*
       @file       main.cpp
       @brief      SDR con ESP32 + ILI9341 + PCM1808 + PCM5102

       @author     Jordi Gauchia

       @date       21/06/2022

       Pinout:
       ILI9341        MICRO SD       ENCODER          PCM1808            PCM5102
       ---------------------------------------------------------------------------------------
       VCC  3,3v      VCC  3,3v      VCC  3,3v        VCC   3,3v-5v      VCC   5v
       GND  GND       GND  GND       GND  GND         GND   GND          GND   GND
       LED  3,3v      CS   GPIO4     A    GPIO16      BCK   GPIO26       SCK   GPIO0
       MISO GPIO27    MISO GPIO27    B    GPIO17      OUT   GPIO35       BCK   GPIO26
       SCK  GPIO14    SCK  GPIO14                     LRC   GPIO33       DIN   GPIO25
       MOSI GPIO13    MOSI GPIO13                     SCK   GPIO0        LCK   GPIO33
       DC   GPIO15
       RST  GPIO32
       CS   GPIO2
       T_CS GPIO18


       Librerías:
       ILI9341 :  https://github.com/Bodmer/TFT_eSPI
       ENCODER :  https://github.com/madhephaestus/ESP32Encoder
       FFT     :  https://github.com/kosme/arduinoFFT
*/       

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <SD.h>
#include "driver/i2s.h"

#include "Vars.h"
#include "TFT.h"
#include "I2S_ADC_DAC.h"

void setup() 
{
  /* Inicializar DAC y ADC y procesar audio*/
  set_I2S();
  set_I2S_mclk_pin(MCK);
  xTaskCreatePinnedToCore(process_Audio, "process_Audio", 4096 , NULL, 10,  NULL, 0);
  /* Inicializar Puerto Serie*/  
  Serial.begin(115200);
  /* Inicializar TFT*/
  init_SPIFFS();
  init_ili9341();
  touch_calibrate();
}

void loop() 
{
  // put your main code here, to run repeatedly:
}