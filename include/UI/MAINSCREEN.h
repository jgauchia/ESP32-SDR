/*
       @file       MAINSCREEN.h
       @brief      Definición pantalla principal

       @author     Jordi Gauchia

       @date       21/06/2022
*/

// **********************************************
//  Función para actualizar frecuencia pant.princ
// **********************************************
void update_freq_main_screen()
{
    char freq_str[12] = "";
    memset(&freq_str[0], 0, sizeof(freq_str));

    freq_spr.fillSprite(BKG_COLOUR);
    freq_spr.setTextSize(1);
    // draw_spectrum();

    if (step_idx == 0)
    {
        freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
        freq_spr.drawString(freq_to_string_mhz(freq), 0, 0, 6);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq), 1);
        freq_spr.drawString(freq_str, 180, 18, 4);
        freq_spr.setTextColor(BKG_COLOUR, FREQ_FONT_COLOUR);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq) + 1, 1);
        freq_spr.drawString(freq_str, 186, 18, 4);
        freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
        memset(&freq_str[0], 0, sizeof(freq_str));
        strncpy(freq_str, freq_to_string_hz(freq) + 2, 2);
        freq_spr.drawString(freq_str, 201, 18, 4);
    }
    else
    {
        switch (step_idx)
        {
        case 1:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 6);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(BKG_COLOUR, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            freq_spr.drawString(freq_str, 150, 0, 6);
            break;
        case 2:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 5);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(BKG_COLOUR, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 1);
            freq_spr.drawString(freq_str, 123, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 6, 1);
            freq_spr.drawString(freq_str, 150, 0, 6);
            break;
        case 3:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 4);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(BKG_COLOUR, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 4, 1);
            freq_spr.drawString(freq_str, 95, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 5, 2);
            freq_spr.drawString(freq_str, 123, 0, 6);
            break;
        case 4:
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq), 2);
            freq_spr.drawString(freq_str, 0, 0, 6);
            freq_spr.setTextColor(BKG_COLOUR, FREQ_FONT_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 2, 1);
            freq_spr.drawString(freq_str, 53, 0, 6);
            freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
            memset(&freq_str[0], 0, sizeof(freq_str));
            strncpy(freq_str, freq_to_string_mhz(freq) + 3, 4);
            freq_spr.drawString(freq_str, 81, 0, 6);
            break;
        default:
            break;
        }
        freq_spr.setTextColor(FREQ_FONT_COLOUR, BKG_COLOUR);
        freq_spr.drawString(freq_to_string_hz(freq), 180, 18, 4);
    }
    freq_spr.pushSprite(FREQ_POS_X, FREQ_POS_Y);
    memset(&freq_str[0], 0, sizeof(freq_str));
}

// **********************************************
//  Función para actualizar status pant.princ
// **********************************************
void update_status_main_screen()
{
    char status_str[200] = "";
    memset(&status_str[0],0,sizeof(status_str));

    status_spr.fillSprite(BKG_COLOUR);
    status_spr.setTextSize(1);
    status_spr.setTextColor(STATUS_FONT_COLOUR, BKG_COLOUR);
        
    memset(&status_str[0],0,sizeof(status_str)); 
    sprintf(status_str, "Model:%s %dMhz - Free mem:%dK %d%%",ESP.getChipModel(),ESP.getCpuFreqMHz(),(ESP.getFreeHeap()/1024),(ESP.getFreeHeap()*100)/ESP.getHeapSize() );
    status_spr.drawString(status_str, 0, 0, 1);
    
    status_spr.pushSprite(0, 0);
    memset(&status_str[0],0,sizeof(status_str)); 
}

// **********************************************
//  Función para dibujar espectro audio
// **********************************************
void draw_spectrum()
{
    //double first_fft_value;
    //double next_fft_value;
    //int max_k = 0;
    for (uint16_t i = 0; i <= 256; i++)
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