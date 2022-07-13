/*
       @file       TFT.h
       @brief      Definiciones y rutinas para pantalla TFT

       @author     Jordi Gauchia

       @date       21/06/2022
*/

// **********************************************
// Configuración para LovyanGFX
// **********************************************
#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_XPT2046 _touch_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

      cfg.spi_host = HSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 79999999;
      cfg.freq_read = 70000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 14;
      cfg.pin_mosi = 13;
      cfg.pin_miso = 12;
      cfg.pin_dc = 15;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();

      cfg.pin_cs = 2;
      cfg.pin_rst = 32;
      cfg.pin_busy = -1;

      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;

      // 以下はST7735やILI9163のようにピクセル数が可変のドライバで表示がずれる場合にのみ設定してください。
      //    cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
      //    cfg.memory_height    =   320;  // ドライバICがサポートしている最大の高さ

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;
      cfg.x_max = 319;
      cfg.y_min = 0;
      cfg.y_max = 479;
      cfg.pin_int = 5;
      cfg.bus_shared = true;
      cfg.offset_rotation = 0;

      cfg.spi_host = HSPI_HOST;
      cfg.freq = 1000000;
      cfg.pin_sclk = 14;
      cfg.pin_mosi = 13;
      cfg.pin_miso = 27;
      cfg.pin_cs = 18;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};
#include <LGFX_TFT_eSPI.hpp>

// **********************************************
//  Declaración para el TFT
// **********************************************
static TFT_eSPI tft;
static TFT_eSprite spr = TFT_eSprite(&tft);
static TFT_eSprite freq_spr = TFT_eSprite(&tft);
static TFT_eSprite status_spr = TFT_eSprite(&tft);

// **********************************************
//  Función para inicializar el LCD
// **********************************************
void init_TFT()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BKG_COLOUR);
  tft.initDMA();
  freq_spr.setColorDepth(16);
  freq_spr.createSprite(FREQ_WIDTH, FREQ_HEIGHT);
  freq_spr.fillSprite(BKG_COLOUR);
  status_spr.setColorDepth(16);
  status_spr.createSprite(STATUS_WIDTH, STATUS_HEIGHT);
  status_spr.fillSprite(BKG_COLOUR);
}

// **********************************************
//  Función para inicializar almacen. SPIFFS
// **********************************************
void init_SPIFFS()
{
  if (!SPIFFS.begin(true))
    Serial.println("SPIFFS no montado");
  else
    Serial.println("SPIFFS montado correctamente");
}

// **********************************************
//  Función para calibrar TOUCH
// **********************************************
void touch_calibrate()
{
  uint16_t calData[5];
  bool calDataOK = 0;

  if (SPIFFS.exists(CALIBRATION_FILE))
  {
    if (REPEAT_CAL)
      SPIFFS.remove(CALIBRATION_FILE);
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f)
      {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL)
    tft.setTouchCalibrate(calData);
  else
  {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL)
    {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f)
    {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
    delay(1000);
    tft.fillScreen(TFT_BLACK);
  }
}