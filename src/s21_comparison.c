#include "s21_decimal.h"

int s21_is_equal(DEC val_1, DEC val_2) {
  if (get_sign(val_1) != get_sign(val_2)) return OK;
  if (get_scale(val_1) > 0 || get_scale(val_2) > 0)
    equalize_scale(&val_1, &val_2);
  for (int i = 0; i < SCALE; i++)
    if (val_1.bits[i] != val_2.bits[i]) return OK;

  return ERR;
}

int s21_is_less(DEC val_1, DEC val_2) {
  int sign1 = get_sign(val_1);
  int sign2 = get_sign(val_2);

  if (sign1 != sign2) return sign1 > sign2;
  bool negatives = sign1 && sign2;
  if (negatives || get_scale(val_1) > 0 || get_scale(val_2) > 0)
    equalize_scale(&val_1, &val_2);
  for (int i = BIT3_POS; i >= 0; i--) {
    int bits1 = get_bit(val_1, i);
    int bits2 = get_bit(val_2, i);
    if (bits1 != bits2) return negatives ? bits1 > bits2 : bits1 < bits2;
  }

  return OK;
}

int s21_is_not_equal(DEC val_1, DEC val_2) {
  return !s21_is_equal(val_1, val_2);
}

int s21_is_less_or_equal(DEC val_1, DEC val_2) {
  return s21_is_less(val_1, val_2) || s21_is_equal(val_1, val_2);
}

int s21_is_greater(DEC val_1, DEC val_2) {
  return !s21_is_less_or_equal(val_1, val_2);
}

int s21_is_greater_or_equal(DEC val_1, DEC val_2) {
  return !s21_is_less(val_1, val_2) || s21_is_equal(val_1, val_2);
}