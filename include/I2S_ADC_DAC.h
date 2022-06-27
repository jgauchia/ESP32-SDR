/*
       @file       I2S_ADC_DAC.h
       @brief      Definiciones y rutinas para el ADC y DAC I2S

       @author     Jordi Gauchia

       @date       21/06/2022
*/

// **********************************************
//  Definición variables ADC y DAC
// **********************************************
#define SAMPLING_RATE 96000
#define BUFFER 256
#define CHANNEL_BUF 512

int ADC_buf[CHANNEL_BUF], DAC_buf[CHANNEL_BUF], FFT_buf[CHANNEL_BUF];
float left_in[CHANNEL_BUF / 2], right_in[CHANNEL_BUF / 2];
float left_out[CHANNEL_BUF / 2], right_out[CHANNEL_BUF / 2];

float gain_input = 1.0f;
float gain_output = 3.0f;

// **********************************************
//  Definición pines ADC y DAC
// **********************************************
#define BCK 26
#define LRC 33
#define DIN 35
#define DOUT 25
#define MCK 0

i2s_pin_config_t i2s_pin_config = {.bck_io_num = BCK, .ws_io_num = LRC, .data_out_num = DOUT, .data_in_num = DIN};

void set_I2S_mclk_pin(const uint8_t pin)
{
  if (pin != 0 && pin != 1 && pin != 3)
    Serial.printf("Only support GPIO0/GPIO1/GPIO3, gpio_num:%d", pin);
  switch (pin)
  {
  case 0:
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
    WRITE_PERI_REG(PIN_CTRL, 0xFFF0);
    break;
  case 1:
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD_CLK_OUT3);
    WRITE_PERI_REG(PIN_CTRL, 0xF0F0);
    break;
  case 3:
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0RXD_CLK_OUT2);
    WRITE_PERI_REG(PIN_CTRL, 0xFF00);
    Serial.println("ok");
    break;
  default:
    break;
  }
}

// **********************************************
//  Configuración I2S
// **********************************************
i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = SAMPLING_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_24BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = BUFFER,
    .use_apll = true,
    .tx_desc_auto_clear = true,
    .fixed_mclk = SAMPLING_RATE * 384};

// **********************************************
//  Inicialización I2S
// **********************************************
void set_I2S()
{
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_pin_config);
  i2s_set_sample_rates(I2S_NUM_0, SAMPLING_RATE);
  i2s_set_clk(I2S_NUM_0, SAMPLING_RATE, I2S_BITS_PER_SAMPLE_24BIT, I2S_CHANNEL_STEREO);
  i2s_start(I2S_NUM_0);
}

// **********************************************
//  Función para procesar el audio I2S
// **********************************************
void process_Audio(void *pvParameters)
{
  (void)pvParameters;
  float sample = 0;
  for (;;)
  {
    size_t readsize = 0;

    esp_err_t ADCfb = i2s_read(I2S_NUM_0, &ADC_buf[0], CHANNEL_BUF * 2, &readsize, 1000);

    if (ADCfb == ESP_OK && readsize == CHANNEL_BUF * 2)
    {
      /*split L an R input*/
      int y = 0;
      for (int i = 0; i < CHANNEL_BUF; i += 2)
      {
        right_out[y] = (float)ADC_buf[i];
        left_out[y] = (float)ADC_buf[i + 1];

        right_in[y] = (float)ADC_buf[i];
        left_in[y] = (float)ADC_buf[i + 1];
        y++;
      }

      /*gain input*/
      for (int i = 0; i < CHANNEL_BUF / 2; i++)
      {
        right_out[i] = gain_input * right_out[i];
        left_out[i] = gain_input * left_out[i];
      }

      /*gain output*/
      for (int i = 0; i < CHANNEL_BUF / 2; i++)
      {
        right_out[i] = gain_output * right_out[i];
        left_out[i] = gain_output * left_out[i];
      }
      y = 0;
      for (int i = 0; i < CHANNEL_BUF / 2; i++)
      {
        DAC_buf[y] = (int)left_out[i];
        DAC_buf[y + 1] = (int)right_out[i];
        y = y + 2;
      }

      i2s_write(I2S_NUM_0, &DAC_buf[0], CHANNEL_BUF * 2, &readsize, 1000);
    }
  }
  vTaskDelete(NULL);
}