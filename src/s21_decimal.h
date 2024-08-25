#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdint.h>  //виновник торжества
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT3_POS 96
#define SIGN_POS 127
#define DEC s21_decimal

#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

typedef struct DEC {
  unsigned int bits[4];
} DEC;

typedef enum { FALSE, TRUE } bool;
typedef enum { OK, ERR } retval;

// Биты по порядку
typedef enum { LOW, MID, HIGH, SCALE } pos;
// Знак выражения
typedef enum { PLUS, MIN, MUL, DIV } sign;
// Результаты арифметических операций
typedef enum { OKAY, INF, MIN_INF, DIV_BY_ZERO, ERROR } arith_res;
// Результаты преобразования
typedef enum { CONVERTATION_OK, CONVERTATION_ERROR } conv_res;

// ==== PROJECT FUNCTIONS ==== //

// arithmetics
int s21_add(DEC val_1, DEC val_2, DEC *res);
int s21_sub(DEC val_1, DEC val_2, DEC *res);
int s21_mul(DEC val_1, DEC val_2, DEC *res);
int s21_div(DEC val_1, DEC val_2, DEC *res);

// comparison
int s21_is_greater(DEC val_1, DEC val_2);
int s21_is_less(DEC val_1, DEC val_2);
int s21_is_less_or_equal(DEC val_1, DEC val_2);
int s21_is_greater_or_equal(DEC val_1, DEC val_2);
int s21_is_equal(DEC val_1, DEC val_2);
int s21_is_not_equal(DEC val_1, DEC val_2);

// convertation
int s21_from_int_to_decimal(int src, DEC *dst);
int s21_from_decimal_to_int(DEC src, int *dst);
int s21_from_float_to_decimal(float src, DEC *dst);
int s21_from_decimal_to_float(DEC src, float *dst);

// other
int s21_negate(DEC src, DEC *res);
int s21_floor(DEC src, DEC *res);
int s21_round(DEC src, DEC *res);
int s21_truncate(DEC src, DEC *res);

// ==== SUPPLEMENTARY FUNCTIONS ==== //

// bit manipulations
int get_bit(DEC num, int index);
int set_bit(DEC *num, int index);
void set_zero(DEC *num);
int set_null(DEC *num, int index);
int get_sign(DEC number);
void set_sign(DEC *num, int sign);

// scale manipulations
int get_scale(DEC num);
void set_scale(DEC *num, int exp);
void equalize_scale(DEC *dst1, DEC *dst2);
void lower_scale(DEC *val);

// overflow checks
int check_overflow_add(DEC val_1, DEC val_2, sign operator);
int check_overflow_sub(DEC val_1, DEC val_2, sign operator);
int check_overflow_mul(DEC val_1, DEC val_2, sign operator);
int check_overflow_div(DEC val_1, DEC val_2, sign operator);

// miscellaneous
bool decimal_is_null(DEC num);
void copy_decimal(DEC *src, DEC *dst);
int decimal_mod(DEC val_1, DEC val_2, DEC *res);
void decimal_to_string(char *dst, DEC src);
DEC string_to_decimal(char *string);

#endif