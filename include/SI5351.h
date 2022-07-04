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
static const uint64_t pll_min = 40000000000ULL; //60000000000ULL;
static const uint64_t pll_max = 90000000000ULL;
uint64_t freq = 500000000ULL;
uint64_t freq_max = 16000000000ULL;
uint64_t freq_min = 800000ULL;
uint64_t freq_step = 10000ULL;
uint64_t freq_oldstep = 0;
uint64_t oldfreq = 0;
uint64_t pll_freq;
int multiple;

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
    si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA);
    si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_2MA);
    si5351.output_enable(SI5351_CLK0, 1);
    si5351.output_enable(SI5351_CLK1, 1);
    si5351.output_enable(SI5351_CLK2, 0);
  }
}

// **********************************************
//  Función para obtener el PLL el VFO
// **********************************************
void GetPLLFreq()
{
  float_t f_pll_freq;

  for (int i = 10; i <= 200; i = i + 2)
  {
    f_pll_freq = freq * i;
    if (f_pll_freq >= pll_min)
    {
      if (f_pll_freq <= pll_max)
      {
        if (f_pll_freq == floor(f_pll_freq))
        {
          pll_freq = f_pll_freq;
          multiple = pll_freq / freq;
          break;
        }
      }
    }
  }
}

// **********************************************
//  Función para enviar frecuencia a VFO
//  con desfase 90º en CLK1 respecto CLK0
// **********************************************
void SendFrequency()
{

  GetPLLFreq();

  si5351.set_pll(pll_freq, SI5351_PLLA);

  si5351.set_freq_manual(freq, pll_freq, SI5351_CLK0);
  si5351.set_freq_manual(freq, pll_freq, SI5351_CLK1);

  si5351.set_phase(SI5351_CLK0, 0);
  si5351.set_phase(SI5351_CLK1, multiple);  
  
  si5351.pll_reset(SI5351_PLLA);
}