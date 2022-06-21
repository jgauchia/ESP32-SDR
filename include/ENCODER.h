/*
       @file       ENCODER.h
       @brief      Definiciones y rutinas para el encoder

       @author     Jordi Gauchia

       @date       21/09/2022
*/

// **********************************************
//  Definición pines encoder
// **********************************************
#define ENCODER_A 16
#define ENCODER_B 17
#define ENCODER_SW 9

// **********************************************
//  Declaración encoder
// **********************************************
ESP32Encoder encoder;
int32_t encoder_pos = 0;
int32_t encoder_newpos = 0;
int encoder_dir = 0;
int sw_lastState = HIGH;
int sw_currentState;

// **********************************************
//  Función para incializar el encoder
// **********************************************
void init_encoder()
{
  encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
  encoder.setCount(0);
}

// **********************************************
//  Función para leer posición de encoder y boton
// **********************************************
void get_encoder()
{
  sw_currentState = digitalRead(ENCODER_SW);
  if (sw_lastState == HIGH && sw_currentState == LOW)
  {
    encoder.pauseCount();
    // step_idx++;
    // if (step_idx > 4)
    //   step_idx = 0;
    // if (step_idx != 0)
    //   freq_oldstep = freq_step / steps_mult[step_idx - 1];
    // freq_step = freq_oldstep * steps_mult[step_idx];
    // step_change = true;
    encoder.resumeCount();
  }
  delay(5);
  sw_lastState = sw_currentState;

  encoder_newpos = encoder.getCount();
  if (encoder_newpos > encoder_pos)
    encoder_dir = 1;
  else if (encoder_newpos < encoder_pos)
    encoder_dir = -1;

  if (encoder_pos != encoder_newpos)
  {
    // if (freq == freq_min && encoder_dir == -1)
    //   freq = freq_min;
    // else
    //   freq += encoder_dir * freq_step;

    // if (freq <= freq_min)
    //   freq = freq_min;
    // if (freq >= freq_max)
    //   freq = freq_max;

    encoder_pos = encoder_newpos;
    // freq_change = true;
  }
}

// **********************************************
//  Función para tarea de leer el Encoder
// **********************************************
void Read_Encoder(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
    get_encoder();
    vTaskDelay(5);
  }
}
