/*
       @file       MAINSCREEN.h
       @brief      Definición pantalla principal

       @author     Jordi Gauchia

       @date       21/06/2022
*/

#define FREQ_FONT_COLOUR TFT_WHITE

// **********************************************
//  Función para actualizar pantalla principal
// **********************************************
void update_freq_main_screen()
{
    char freq_str[25] = "";
    memset(&freq_str[0], 0, sizeof(freq_str));

    freq_spr.fillSprite(TFT_BLACK);
    freq_spr.setTextSize(1);
    // draw_spectrum();

    if (step_idx == 0)
    {
        freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        freq_spr.drawString(freq_to_string_mhz(freq), 0, 0, 6);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq), 1);
        freq_spr.drawString(freq_str, 180, 18, 4);
        freq_spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq) + 1, 1);
        freq_spr.drawString(freq_str, 186, 18, 4);
        freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq) + 2, 2);
        freq_spr.drawString(freq_str, 201, 18, 4);
    }
    else
    {
        switch (step_idx)
        {
        case 1:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 6);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            freq_spr.drawString(freq_str, 150, 0, 6);
            break;
        case 2:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 5);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 1);
            freq_spr.drawString(freq_str, 123, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            freq_spr.drawString(freq_str, 150, 0, 6);
            break;
        case 3:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 4);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 4, 1);
            freq_spr.drawString(freq_str, 95, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 2);
            freq_spr.drawString(freq_str, 123, 0, 6);
            break;
        case 4:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 2);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(TFT_BLACK, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 2, 1);
            freq_spr.drawString(freq_str, 53, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 3, 4);
            freq_spr.drawString(freq_str, 81, 0, 6);
            break;
        default:
            break;
        }
        freq_spr.setTextColor(FREQ_FONT_COLOUR, TFT_BLACK);
        freq_spr.drawString(freq_to_string_hz(freq), 180, 18, 4);
    }
    freq_spr.pushSprite(140, 65);
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
        spr.drawLine(30 + i, 218 - abs(vReal[i] / 10), 30 + i, 218 - abs(vReal[i + 1] / 10), TFT_CYAN);
        // if (first_fft_value > 38)
        //     first_fft_value = 38;
        // if (next_fft_value > 38)
        //     next_fft_value = 38;
    }
}