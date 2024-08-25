#include "s21_decimal.h"

int s21_negate(DEC src, DEC *res) {
  if (!res) return ERR;

  set_zero(res);
  set_scale(res, get_scale(src));

  (get_bit(src, SIGN_POS) == 0) ? set_bit(res, SIGN_POS)
                                : set_null(res, SIGN_POS);
  for (size_t pos = 0; pos < BIT3_POS; pos++)
    (get_bit(src, pos) == 0) ? set_null(res, pos) : set_bit(res, pos);

  return OK;
}

int s21_round(DEC src, DEC *res) {
  if (!res) return ERR;

  set_zero(res);
  int scale = get_scale(src);

  if (scale > 0) {
    DEC round_factor;
    s21_from_int_to_decimal(pow(1, scale - 1), &round_factor);
    if (get_sign(src)) s21_negate(src, &src);
    s21_add(src, round_factor, res);
    s21_truncate(*res, res);
    if (get_sign(src)) s21_negate(*res, res);
  } else
    *res = src;

  return OK;
}

int s21_truncate(DEC src, DEC *res) {
  if (!res) return ERR;

  int src_scale = get_scale(src);
  int sign = get_sign(src);
  set_zero(res);
  set_scale(&src, 0);
  DEC ten = {{10, 0, 0, 0}};
  for (int i = 0; i < src_scale; i++) s21_div(src, ten, res), src = *res;
  *res = src;
  if (sign) set_bit(res, SIGN_POS);
  return OK;
}

int s21_floor(DEC src, DEC *res) {
  if (!res) return ERR;
  set_zero(res);
  int sign = get_sign(src);
  DEC one = {{1, 0, 0, 0}};
  DEC val_tmp = {{0}};
  s21_truncate(src, &val_tmp);
  if (sign)
    s21_sub(val_tmp, one, res);
  else
    *res = val_tmp;

  return OK;
}
