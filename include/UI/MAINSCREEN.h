/*
       @file       MAINSCREEN.h
       @brief      Definición pantalla principal

       @author     Jordi Gauchia

       @date       21/06/2022
*/

#define FREQ_FONT_COLOUR   TFT_WHITE

// **********************************************
//  Función para actualizar pantalla principal
// **********************************************
void update_main_screen()
{
    char freq_str[25] = "";
    memset(&freq_str[0], 0, sizeof(freq_str));

    spr.fillSprite(TFT_BLACK);
    spr.setTextSize(1);
    draw_spectrum();

    if (step_idx == 0)
    {
        spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        spr.drawString(freq_to_string_mhz(freq), 74, 7, 6);
        spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq), 1);
        spr.drawString(freq_str, 255, 25, 4);
        spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq) + 1, 2);
        spr.drawString(freq_str, 269, 25, 4);
    }
    else
    {
        switch (step_idx)
        {
        case 1:
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 6);
            spr.drawString(freq_str, 74, 7, 6);
            spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            spr.drawString(freq_str, 225, 7, 6);
            break;
        case 2:
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 5);
            spr.drawString(freq_str, 74, 7, 6);
            spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 1);
            spr.drawString(freq_str, 197, 7, 6);
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            spr.drawString(freq_str, 225, 7, 6);
            break;
        case 3:
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 4);
            spr.drawString(freq_str, 74, 7, 6);
            spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 4, 1);
            spr.drawString(freq_str, 169, 7, 6);
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 2);
            spr.drawString(freq_str, 197, 7, 6);
            break;
        case 4:
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 2);
            spr.drawString(freq_str, 74, 7, 6);
            spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 2, 1);
            spr.drawString(freq_str, 127, 7, 6);
            spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 3, 4);
            spr.drawString(freq_str, 155, 7, 6);
            break;
        default:
            break;
        }
        spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        spr.drawString(freq_to_string_hz(freq), 255, 25, 4);
    }
    spr.pushSprite(0, 0);
}

// **********************************************
//  Función para dibujar espectro audio
// **********************************************
void draw_spectrum()
{
    double first_fft_value;
    double next_fft_value;
    int max_k = 0;
    for (int i = 0; i <= 256; i++)
    {
        // first_fft_value = (vReal[i] / 10);
        // next_fft_value = (vReal[i + 1] /10);
        spr.drawLine(30 + i, 218 - (vReal[i] / 10), 30 + i, 218 - (vReal[i + 1] / 10), TFT_CYAN);
        // if (first_fft_value > 38)
        //     first_fft_value = 38;
        // if (next_fft_value > 38)
        //     next_fft_value = 38;
    }
}