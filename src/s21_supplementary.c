#include "s21_decimal.h"

// Инициализирует число num нулями
void set_zero(DEC *num) { memset(&(num->bits), 0, sizeof(num->bits)); }

// Возвращает значение бита на указанной позиции в числе num
int get_bit(DEC num, int index) {
  unsigned int bit_mask = 1u << (index % 32);
  int bit = ((num.bits[index / 32] & bit_mask) >> (index % 32));
  return bit;
}

// Устанавливает значение бита на указанной позиции в числе num
int set_bit(DEC *num, int index) {
  unsigned int bit_mask = 1u << (index % 32);
  return num->bits[index / 32] = num->bits[index / 32] | bit_mask;
}

// Устанавливает значение бита на указанной позиции в числе
int set_null(DEC *num, int index) {
  unsigned int bit_mask = 1u << (index % 32);
  return num->bits[index / 32] = num->bits[index / 32] & ~bit_mask;
}

// Получение значения cтепени
int get_scale(DEC num) {
  int bit_mask = SIGN_POS << 16;
  int scale = (bit_mask & num.bits[3]) >> 16;
  return scale;
}

//Устанавливает значение cтепени
void set_scale(DEC *num, int exp) {
  int bit_mask = exp << 16;
  num->bits[3] = bit_mask;
}

bool decimal_is_null(DEC num) {
  for (int i = 0; i < SCALE; i++)
    if (num.bits[i] != 0) return FALSE;
  return TRUE;
}

// Возвращает знак числа num (0 - положительное, 1 - отрицательное)
int get_sign(DEC num) { return get_bit(num, SIGN_POS); }

// Копирует значение числа src в число dst
void copy_decimal(DEC *src, DEC *dst) {
  for (int index = LOW; index <= SCALE; index++) {
    dst->bits[index] = src->bits[index];
  }
}

#define EQ_SCALE_COMMON(dst, scale1, scale2)    \
  {                                             \
    set_scale(dst, 0);                          \
    for (int i = scale2 - scale1; i > 0; i--) { \
      s21_from_int_to_decimal(10, &ten);        \
      s21_mul(*dst, ten, &temp);                \
      *dst = temp;                              \
    }                                           \
    set_scale(dst, scale2);                     \
  }

// Уравнивает степень чисел dst1 и dst2
void equalize_scale(DEC *dst1, DEC *dst2) {
  unsigned int scale1 = get_scale(*dst1);
  unsigned int scale2 = get_scale(*dst2);
  DEC ten = {{0}};
  DEC temp = {{0}};

  if (scale1 > scale2) EQ_SCALE_COMMON(dst2, scale2, scale1);
  if (scale1 < scale2) EQ_SCALE_COMMON(dst1, scale1, scale2);
}

// Убирает лишние нули из чисел с плавающей точки
void lower_scale(DEC *value) {
  if (get_scale(*value) <= 0) return;

  int scale = get_scale(*value);
  int sign = get_sign(*value);
  set_scale(value, 0);
  set_null(value, SIGN_POS);
  DEC temp_mult = {{10, 0, 0, 0}};
  DEC temp_res = {{0}};
  DEC temp_val = {{0}};

  decimal_mod(*value, temp_mult, &temp_res);

  while (decimal_is_null(temp_res) && scale > 0) {
    s21_div(*value, temp_mult, &temp_val);
    scale--;
    copy_decimal(&temp_val, value);
  }

  set_scale(value, scale);
  if (sign) set_bit(value, SIGN_POS);
}

// Преобразует десятичное представление DEC в строку
void decimal_to_string(char *dst, DEC src) {
  if (dst) {
    bool flag = FALSE;
    char temp[255] = {'\0'};
    int length = 0;
    for (int pos = BIT3_POS; pos >= 0; pos--) {
      if (get_bit(src, pos)) {
        temp[pos] = '1';
        flag = TRUE;
        length++;
      } else {
        if (flag) {
          temp[pos] = '0';
          length++;
        }
      }
    }

    if (length == 0) dst[0] = '0';
    for (size_t i = 0, j = strlen(temp) - 1; i < strlen(temp); i++, j--)
      dst[i] = temp[j];
  }
}

// Преобразует строку в десятичное представление DEC
DEC string_to_decimal(char *str) {
  char temp[255] = {'\0'};
  for (size_t i = 0, j = strlen(str) - 1; i < strlen(str); i++, j--)
    temp[i] = str[j];

  DEC res = {0};
  for (int pos = 0; pos < BIT3_POS; pos++) {
    if (temp[pos] == '1')
      set_bit(&res, pos);
    else
      set_null(&res, pos);
  }

  return res;
}
