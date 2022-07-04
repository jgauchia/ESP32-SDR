/*
       @file       Conv_func.h
       @brief      Funciones para conversiones varias

       @author     Jordi Gauchia

       @date       26/06/2022
*/

// **********************************************
//  Función para convertir frec. a string MHZ
// **********************************************
char *freq_to_string_mhz(uint64_t input)
{
  input /= 100000;
  static char in[9] = "";
  static char out[6] = "";
  memset(&out[0], 0, sizeof(out));
  memset(&in[0], 0, sizeof(in));
  sprintf(in, "%d", input);
  size_t len = strlen(in);
  if (len >= 6)
    strcpy(out, in);
  else
    sprintf(out, "%0*d%s", (int)(6 - len), 0, in);
  int final_pos = 6;
  int buff_pos = 5;
  int i = 0;
  while (final_pos >= 0)
  {
    in[final_pos--] = out[buff_pos--];
    i++;
    if (i % 3 == 0)
      in[final_pos--] = '.';
  }
  return in;
}

// **********************************************
//  Función para convertir frec. a string MHZ
// **********************************************
char *freq_to_string_hz(uint64_t input)
{
  input /= 100;
  static char in[10] = "";
  static char out[4] = "";
  memset(&out[0], 0, sizeof(out));
  memset(&in[0], 0, sizeof(in));
  sprintf(in, "%d", input);
  int final_pos = 4;
  int buff_pos = strlen(in);
  while (final_pos >= 0)
  {
    out[final_pos--] = in[buff_pos--];
  }
  out[0] = '.';
  return out;
}