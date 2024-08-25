#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, DEC *dst) {
  if (!dst) return CONVERTATION_ERROR;
  memset(&(dst->bits), 0, sizeof(dst->bits));
  if (src < 0) set_bit(dst, SIGN_POS), src = -src;
  dst->bits[0] = src;

  return CONVERTATION_OK;
}

#define TRICKY_LOOP \
  while (pos >= 0 && int_str[pos] == '0') int_str[pos--] = '\0';
// while (int_str[pos] == '0') int_str[pos--] = '\0';

// ftod helpier
int s21_from_float_string(int whole, float fract, DEC *value) {
  char fr_str[255] = {0};
  char int_str[255] = {0};
  int pos = 0;
  int exp = 0;

  if (fract != 0.0) sprintf(fr_str, "%.9f", fract);
  if (whole != 0.0) sprintf(int_str, "%d", whole);
  memmove(fr_str, fr_str + 2, strlen(fr_str));
  exp = strlen(int_str);
  strcat(int_str, fr_str);

  size_t pos_sign_number = strlen(int_str);
  pos = pos_sign_number;

  if (pos_sign_number > 7 && strlen(fr_str) > 0) {
    while (pos != 7) int_str[pos--] = '\0';
    if ((int)int_str[pos] - '0' > 4) {
      pos--;
      if (int_str[pos] == '9') {
        while (int_str[pos] == '9') int_str[pos--] = '0';
        int_str[pos]++;
      } else
        int_str[pos]++;

      int_str[7] = '\0';
      pos = strlen(int_str) - 1;
      TRICKY_LOOP
    } else
      TRICKY_LOOP
  }
  exp = (strlen(int_str) - exp);
  set_scale(value, exp);

  return atoi(int_str);
}

int s21_from_float_to_decimal(float src, DEC *dst) {
  bool flag_minus = FALSE;

  if (dst && !is_inf(src) && !is_nan(src)) {
    set_zero(dst);
    if (src < 0) src *= -1.0f, flag_minus = TRUE;
    float fl_int = 0.0;

    float fl_fract = modff(src, &fl_int);
    int whole = s21_from_float_string((int)fl_int, fl_fract, dst);
    int scale_temp = get_scale(*dst);

    s21_from_int_to_decimal(whole, dst);
    set_scale(dst, scale_temp);
    if (flag_minus) set_bit(dst, SIGN_POS);
  } else {
    set_zero(dst);
    return CONVERTATION_ERROR;
  }

  return CONVERTATION_OK;
}

#define TOITOF_COMMON                                           \
  if (dst) {                                                    \
    uint64_t buffer = 0;                                        \
    *dst = 0;                                                   \
    int sign = get_sign(src);                                   \
    buffer = src.bits[0] + src.bits[1] * (uint64_t)UINT32_MAX + \
             src.bits[2] * (uint64_t)UINT32_MAX;

int s21_from_decimal_to_int(DEC src, int *dst) {
  TOITOF_COMMON
  if (buffer <= INT32_MAX)
    buffer = (sign) ? -buffer : buffer, *dst = (int32_t)buffer;
}
return CONVERTATION_ERROR;
}

int s21_from_decimal_to_float(DEC src, float *dst) {
  TOITOF_COMMON
  *dst = (float)buffer / powf(10.0, get_scale(src));
  if (buffer <= __FLT_MAX__) *dst = (sign) ? -*dst : *dst;
}
return CONVERTATION_ERROR;
}
