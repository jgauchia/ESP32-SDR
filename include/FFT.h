/*
       @file       FFT.h
       @brief      Definición Definiciones y rutinas para el FFT

       @author     Jordi Gauchia

       @date       21/06/2022
*/

// **********************************************
//  Declaración FFT
// **********************************************
arduinoFFT FFT = arduinoFFT();
const uint16_t samples = 256;
double vReal[samples];
double vImag[samples];

// **********************************************
//  Función que realiza el FFT de entr. analógica
// **********************************************
void Compute_FFT()
{
    for (int i = 0; i < samples; i++)
    {
        vReal[i] = (double)((double)left_in[i] / (double)0x7fffff);
        vImag[i] = 0;
    }
    FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, samples);
}
