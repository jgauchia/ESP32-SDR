/*
       @file       SI5351.h
       @brief      Definiciones y rutinas para el SI5351

       @author     Jordi Gauchia

       @date       26/06/2022
*/

// **********************************************
//  Declaración para el SI5351
// **********************************************
Si5351 si5351;

// **********************************************
//  Definición frecuencias
// **********************************************
// uint64_t freq = 73700000ULL;
uint64_t freq = 7600000000ULL;
uint64_t freq_max = 16000000000ULL;
uint64_t freq_min = 800000ULL;
uint64_t freq_step = 10000ULL;
uint64_t freq_oldstep = 0;

// **********************************************
//  Definición steps
// **********************************************
#define NUM_STEPS 5
int steps_mult[NUM_STEPS] = {1, 10, 100, 1000, 10000};
int step_idx = 0;
int step_oldidx = 0;

// **********************************************
//  Función para inicializar el VFO
// **********************************************
void init_si5351()
{
  bool i2c_found;
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  if (!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }
  else
  {
    // si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);
    si5351.output_enable(SI5351_CLK0, 1);
    si5351.output_enable(SI5351_CLK1, 0);
    si5351.output_enable(SI5351_CLK2, 0);
  }
}