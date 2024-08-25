#include "s21_decimal.h"

// СЛОЖЕНИЕ/ВЫЧИТАНИЕ ==========================================================

#define OP_HELPER(val_1, val_2, res, OPERATOR, CONDITION_SET)           \
  do {                                                                  \
    prepare_helpers(&val_1, &val_2, res);                               \
    int temp = 0;                                                       \
    for (int pos = 0; pos < BIT3_POS; pos++) {                          \
      int op_result = get_bit(val_1, pos) OPERATOR get_bit(val_2, pos); \
      CONDITION_SET                                                     \
    }                                                                   \
  } while (0)

#define SET_HANDLER(COND_1, VAL_1, COND_2, SET_1, SET_2, VAL_2)             \
  if (op_result COND_1)                                                     \
    (temp == VAL_1) ? set_bit(res, pos) : set_null(res, pos), temp = VAL_1; \
  else if (op_result COND_2)                                                \
    (temp == 0) ? SET_1 : SET_2, temp = VAL_2;                              \
  else                                                                      \
    (temp == 0) ? SET_2 : SET_1, temp = (temp == 0) ? 0 : 1;

#define SET_ADD \
  SET_HANDLER(== 2, 1, == 0, set_null(res, pos), set_bit(res, pos), 0)
#define SET_SUB \
  SET_HANDLER(> 0, 0, < 0, set_bit(res, pos), set_null(res, pos), 1)

// -----------------------------------------------------------------------------
void prepare_helpers(DEC *val_1, DEC *val_2, DEC *res) {
  int scale_1 = get_scale(*val_1);
  int scale_2 = get_scale(*val_2);

  if (scale_1 > 0 || scale_2 > 0) {
    set_scale(res, (scale_1 > scale_2) ? scale_1 : scale_2);
    set_scale((scale_1 > scale_2) ? val_2 : val_1, 0);
    DEC shift = {
        {(int)pow(10.0, (double)fabs((double)scale_1 - (double)scale_2)), 0, 0,
         0}};
    DEC temp_val_1 = {{0}};
    DEC temp_val_2 = {{0}};

    s21_mul((scale_1 > scale_2) ? *val_2 : *val_1, shift,
            (scale_1 > scale_2) ? &temp_val_2 : &temp_val_1);

    copy_decimal((scale_1 > scale_2) ? &temp_val_2 : &temp_val_1,
                 (scale_1 > scale_2) ? val_2 : val_1);
  }
}
// ----------------------------------------------------------------------------
void add_helper(DEC val_1, DEC val_2, DEC *res) {
  OP_HELPER(val_1, val_2, res, +, SET_ADD);
}
// ----------------------------------------------------------------------------
void sub_helper(DEC val_1, DEC val_2, DEC *res) {
  OP_HELPER(val_1, val_2, res, -, SET_SUB);
}
// ----------------------------------------------------------------------------

#define ADDSUB_ERRCHK(OP, SIGN)                                 \
  arith_res err_code = check_overflow_##OP(val_1, val_2, SIGN); \
  if (err_code != OKAY || !res) {                               \
    if (res) set_zero(res);                                     \
    return err_code;                                            \
  }

#define ADDSUB_COMMON(OP_HELPER)                                     \
  set_zero(res);                                                     \
  if (!get_bit(val_1, SIGN_POS) && !get_bit(val_2, SIGN_POS)) {      \
    OP_HELPER(val_1, val_2, res);                                    \
  } else if (get_bit(val_1, SIGN_POS) && get_bit(val_2, SIGN_POS)) { \
    set_null(&val_1, SIGN_POS);                                      \
    set_null(&val_2, SIGN_POS);                                      \
    OP_HELPER(val_1, val_2, res);                                    \
    set_bit(res, SIGN_POS);                                          \
  } else

int s21_add(DEC val_1, DEC val_2, DEC *res) {
  ADDSUB_ERRCHK(add, PLUS)

  ADDSUB_COMMON(add_helper) {
    DEC *val_neg = get_bit(val_1, SIGN_POS) ? &val_1 : &val_2;
    DEC *val_pos = get_bit(val_1, SIGN_POS) ? &val_2 : &val_1;
    DEC temp_val;
    set_zero(&temp_val);
    s21_negate(*val_neg, &temp_val);
    set_scale(&temp_val, get_scale(*val_neg));

    if (s21_is_greater(temp_val, *val_pos))
      sub_helper(temp_val, *val_pos, res), set_bit(res, SIGN_POS);
    else if (s21_is_less(temp_val, *val_pos))
      sub_helper(*val_pos, temp_val, res);
    else
      set_zero(res);
  }

  return OKAY;
}

int s21_sub(DEC val_1, DEC val_2, DEC *res) {
  ADDSUB_ERRCHK(sub, MIN)

  ADDSUB_COMMON(sub_helper) {
    add_helper(val_1, val_2, res);
    if (get_bit(val_1, SIGN_POS)) set_bit(res, SIGN_POS);
  }

  return OKAY;
}

// ДЕЛЕНИЕ ====================================================================

void div_adjust_scale(DEC *val, int scale, int sign) {
  DEC temp_mul = {{(int)pow(10, scale), 0, 0, 0}};
  DEC temp_val = {{0}};
  set_scale(val, 0);
  s21_mul(*val, temp_mul, &temp_val);
  copy_decimal(&temp_val, val);
  if (sign) set_bit(val, SIGN_POS);
}

// ----------------------------------------------------------------------------

int div_format(DEC *val_1, DEC *val_2) {
  int scale_1 = get_scale(*val_1);
  int scale_2 = get_scale(*val_2);
  int sign_1 = get_sign(*val_1);
  int sign_2 = get_sign(*val_2);

  if (scale_1 == 0 && scale_2 > 0)
    div_adjust_scale(val_1, scale_2, sign_1), set_scale(val_2, 0);
  else if (scale_1 > 0 && scale_2 == 0)
    div_adjust_scale(val_2, scale_1, sign_1), set_scale(val_1, 0);
  else if (scale_1 > 0 && scale_2 > 0)
    div_adjust_scale(val_1, scale_2, sign_1),
        div_adjust_scale(val_2, scale_1, sign_2);

  return OKAY;
}

// ----------------------------------------------------------------------------

void div_set_sign_scale(DEC *val_1, DEC *val_2, DEC *res, int *sign,
                        int *scale) {
  if ((get_bit(*val_1, SIGN_POS) && !get_bit(*val_2, SIGN_POS)) ||
      (!get_bit(*val_1, SIGN_POS) && get_bit(*val_2, SIGN_POS)))
    set_bit(res, SIGN_POS);
  if ((get_sign(*val_1) == 0 && get_sign(*val_2) == 1) ||
      (get_sign(*val_1) == 1 && get_sign(*val_2) == 0))
    *sign = 1;

  set_null(val_1, SIGN_POS);
  set_null(val_2, SIGN_POS);

  if (get_scale(*val_1) + get_scale(*val_2) > 0)
    *scale = div_format(val_1, val_2);
}

// ----------------------------------------------------------------------------

void div_shift_remain(char *val_1_string, char *remain_string, DEC val_2,
                      int *pos_shift) {
  for (; s21_is_less(string_to_decimal(remain_string), val_2); (*pos_shift)++)
    remain_string[*pos_shift] = val_1_string[*pos_shift];
  memmove(val_1_string, val_1_string + *pos_shift, strlen(val_1_string));
}

// ----------------------------------------------------------------------------

void div_process_remain(char *val_1_string, char *remain_string, DEC val_2,
                        DEC *remain, int *pos_bit_res, char *res_string,
                        size_t remain_string_size) {
  do {
    int pos_shift;
    s21_sub(string_to_decimal(remain_string), val_2, remain);
    res_string[(*pos_bit_res)++] = '1';
    memset(remain_string, '\0', remain_string_size);
    if (!decimal_is_null(*remain)) decimal_to_string(remain_string, *remain);
    pos_shift = 1;
    while (s21_is_less(*remain, val_2) && strlen(val_1_string) > 0) {
      pos_shift++;
      strncat(remain_string, val_1_string, 1);
      memmove(val_1_string, val_1_string + 1, strlen(val_1_string));
      *remain = string_to_decimal(remain_string);
      if (pos_shift > 2) res_string[(*pos_bit_res)++] = '0';
      if (!strlen(val_1_string) && s21_is_less(*remain, val_2) &&
          !decimal_is_null(*remain))
        res_string[(*pos_bit_res)++] = '0';
      if (decimal_is_null(string_to_decimal(val_1_string)) &&
          decimal_is_null(*remain)) {
        for (size_t i = 0; i < strlen(val_1_string) + 1; i++)
          res_string[(*pos_bit_res)++] = '0';
        break;
      }
    }
  } while (s21_is_greater_or_equal(*remain, val_2));
}

// ----------------------------------------------------------------------------

void div_perform(DEC val_1, DEC val_2, DEC *res, int scale, int sign) {
  int pos_bit_res = 0, pos_shift = 0;
  char val_1_string[255] = {'\0'}, remain_string[255] = {'\0'},
       res_string[255] = {'\0'};
  DEC remain = {{0, 0, 0, 0}};

  decimal_to_string(val_1_string, val_1);

  div_shift_remain(val_1_string, remain_string, val_2, &pos_shift);
  div_process_remain(val_1_string, remain_string, val_2, &remain, &pos_bit_res,
                     res_string, sizeof(remain_string));

  *res = string_to_decimal(res_string);

  set_scale(res, scale);
  if (sign) set_bit(res, SIGN_POS);
  if (scale > 0) lower_scale(res);
}

// ----------------------------------------------------------------------------

int s21_div(DEC val_1, DEC val_2, DEC *res) {
  if (!res || decimal_is_null(val_2) ||
      check_overflow_div(val_1, val_2, DIV) != 0)
    return (!res) ? ERR : check_overflow_div(val_1, val_2, DIV);

  int sign = 0, scale = 0;
  div_set_sign_scale(&val_1, &val_2, res, &sign, &scale);

  if (s21_is_less(val_1, val_2))
    res->bits[LOW] = 0;
  else if (s21_is_equal(val_1, val_2))
    res->bits[LOW] = 1;
  else
    div_perform(val_1, val_2, res, scale, sign);

  return OKAY;
}

// УМНОЖЕНИЕ ===============================================================

int s21_mul(DEC val_1, DEC val_2, DEC *res) {
  if (!res || check_overflow_mul(val_1, val_2, MUL) != 0) {
    if (res) set_zero(res);
    return check_overflow_mul(val_1, val_2, MUL);
  }

  DEC temp_sum;
  set_zero(&temp_sum);
  set_zero(res);

  int res_scale = fmin(get_scale(val_1) + get_scale(val_2), 28);
  DEC ten = {{10, 0, 0, 0}};
  if (s21_is_equal(val_2, ten) && (res_scale > 0)) {
    *res = val_1;
    set_scale(res, get_scale(val_1) - 1);
  } else {
    int temp_pos = 0;
    for (int pos_val_2 = 0; pos_val_2 < BIT3_POS; pos_val_2++) {
      set_zero(res);
      for (int pos_val_1 = 0; pos_val_1 < BIT3_POS; pos_val_1++) {
        int mul = get_bit(val_1, pos_val_1) * get_bit(val_2, pos_val_2);
        if (mul) set_bit(res, pos_val_1 + temp_pos);
      }
      s21_add(*res, temp_sum, res);
      copy_decimal(res, &temp_sum);
      temp_pos++;
    }
    set_scale(res, res_scale);
    if (get_sign(val_1) ^ get_sign(val_2)) set_bit(res, SIGN_POS);
    if (get_scale(*res) > 0) lower_scale(res);
  }
  return OKAY;
}

// ОСТАТОК ДЕЛЕНИЯ ======================================================

int decimal_mod(DEC val_1, DEC val_2, DEC *res) {
  if (!res || decimal_is_null(val_2)) return ERR;

  set_null(&val_1, SIGN_POS), set_null(&val_2, SIGN_POS);
  equalize_scale(&val_1, &val_2);

  if (s21_is_less(val_1, val_2)) {
    copy_decimal(&val_1, res);
    return OKAY;
  }

  char val_1_str[255] = {'\0'};
  char remain_str[255] = {'\0'};
  DEC remain;
  set_zero(&remain);

  decimal_to_string(val_1_str, val_1);
  int pos_shift = 0;
  for (; s21_is_less(string_to_decimal(remain_str), val_2); pos_shift++)
    remain_str[pos_shift] = val_1_str[pos_shift];
  memmove(val_1_str, val_1_str + pos_shift, strlen(val_1_str));

  do {
    s21_sub(string_to_decimal(remain_str), val_2, &remain);
    memset(remain_str, '\0', sizeof(remain_str));
    if (!decimal_is_null(remain)) decimal_to_string(remain_str, remain);
    while (s21_is_less(remain, val_2) && strlen(val_1_str))
      strncat(remain_str, val_1_str, 1),
          memmove(val_1_str, val_1_str + 1, strlen(val_1_str)),
          remain = string_to_decimal(remain_str);
  } while (s21_is_greater_or_equal(remain, val_2));

  copy_decimal(&remain, res);
  set_bit(res, SIGN_POS);

  return OKAY;
}

// ПЕРЕЛИВЫ =================================================================

int check_overflow_add(DEC val_1, DEC val_2, sign oper) {
  if (oper != PLUS) return ERR;

  long long int res =
      (long long int)val_1.bits[HIGH] + (long long int)val_2.bits[HIGH];

  if (res > (long)__UINT32_MAX__) {
    if (get_bit(val_1, SIGN_POS) == 1 && get_bit(val_2, SIGN_POS) == 1)
      return MIN_INF;
    return INF;
  }
  return OK;
}
// ----------------------------------------------------------------------------
int check_overflow_sub(DEC val_1, DEC val_2, sign oper) {
  if (oper != MIN) return ERR;

  long long int res = 0;

  if ((get_sign(val_1) && !get_sign(val_2)) ||
      (!get_sign(val_1) && get_sign(val_2)))
    res = (long long int)val_1.bits[HIGH] + (long long int)val_2.bits[HIGH];
  else
    res = (long long int)val_1.bits[HIGH] - (long long int)val_2.bits[HIGH];
  if (res > (long)__UINT32_MAX__ || res < -(long)__UINT32_MAX__) {
    if (get_bit(val_1, SIGN_POS) == 1 && get_bit(val_2, SIGN_POS) == 1)
      return MIN_INF;
    return INF;
  }
  return OK;
}
// ----------------------------------------------------------------------------
int check_overflow_muldiv(DEC val_1, DEC val_2, sign oper, bool check_scale) {
  if (oper != MUL && oper != DIV) return ERR;

  int i = BIT3_POS;
  int j = BIT3_POS;
  while (get_bit(val_1, i) != 1 && i != 0) i--;
  while (get_bit(val_2, j) == 0 && j != 0) j--;

  if (i + j >= BIT3_POS && (!check_scale || get_scale(val_2) > 0)) {
    if ((get_sign(val_1) == 1 && get_sign(val_2) == 0) ||
        (get_sign(val_1) == 0 && get_sign(val_2) == 1))
      return MIN_INF;
    return INF;
  }
  return OK;
}

int check_overflow_div(DEC val_1, DEC val_2, sign oper) {
  if (decimal_is_null(val_1))
    return INF;
  else if (decimal_is_null(val_2))
    return DIV_BY_ZERO;
  return check_overflow_muldiv(val_1, val_2, oper, TRUE);
}

int check_overflow_mul(DEC val_1, DEC val_2, sign oper) {
  return check_overflow_muldiv(val_1, val_2, oper, FALSE);
}