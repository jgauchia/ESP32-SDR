/*
       @file       TFT.h
       @brief      Definiciones y rutinas para pantalla TFT

       @author     Jordi Gauchia

       @date       21/09/2022
*/


// **********************************************
//  Declaración para el TFT ILI9341
// **********************************************
#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

// **********************************************
//  Función para inicializar el LCD
// **********************************************
void init_ili9341()
{
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.initDMA();
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
  uint8_t calDataOK = 0;

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
    tft.setTouch(calData);
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
  }
}