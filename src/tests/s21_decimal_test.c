#include "../s21_decimal.h"

#include <check.h>

#define MAX_UINT 4294967295

#define VOILA(x) \
  puts("\n" x);  \
  puts("=========================================");

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

#define COLOR_SUITE(x) "\033[1;37;45m" x "\033[0;0;0m"
#define COLOR_CASE(x) "\033[1;37;44m" x "\033[0;0;0m"

//=========================================================
// 4 арифметических оператора

//Сложение---------------------------------------------

START_TEST(add_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int = 0;
  s21_from_int_to_decimal(1899999, &test_v_1);
  s21_from_int_to_decimal(100001, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 2000000);
}
END_TEST

START_TEST(add_2) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(199421, &test_v_1);
  s21_from_int_to_decimal(-4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 199421 + (-4433));
}
END_TEST

START_TEST(add_3) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(-199421, &test_v_1);
  s21_from_int_to_decimal(4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -199421 + 4433);
}
END_TEST

START_TEST(add_4) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-199421, &test_v_1);
  s21_from_int_to_decimal(-4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
}
END_TEST

START_TEST(add_5) {
  s21_decimal test_v_1 = {{10000, 3, 10, 0}};
  s21_decimal test_v_2 = {{1234, 2, 500, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 10000 + 1234);
  ck_assert_uint_eq(result_dec.bits[1], 3 + 2);
  ck_assert_uint_eq(result_dec.bits[2], 10 + 500);
}
END_TEST

START_TEST(add_6) {
  s21_decimal test_v_1 = {{MAX_UINT, 10, 10, 0}};
  s21_decimal test_v_2 = {{1, 2, 20, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 0);
  ck_assert_uint_eq(result_dec.bits[1], 13);
  ck_assert_uint_eq(result_dec.bits[2], 30);
}
END_TEST

START_TEST(add_7) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(add_8) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  set_bit(&test_v_1, 127);
  set_bit(&test_v_2, 127);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(add_9) {}
END_TEST

START_TEST(add_10) {
  s21_decimal test_v_1 = {{4294967294, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_v_2 = {{1, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[1], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[2], MAX_UINT);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_11) {
  s21_decimal src1, src2, result;
  int a = -1234;
  float b = 1.234;
  float res_origin = -1232.766;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_12) {
  s21_decimal src1, src2, result;

  int a = -1234;
  float b = -1.234;
  float res_origin = -1235.234;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_13) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = -221.23401;
  float res_origin = -1455.234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_14) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 0.00234;
  float res_origin = -9402.9976600;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_15) {
  s21_decimal src1, src2, result;
  float a = -940.3;
  float b = 0.234;
  float res_origin = -940.0660000;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_16) {
  s21_decimal src1, src2, result;
  float a = -0.940301;
  float b = 22.023401;
  float res_origin = 21.0831;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_17) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = -112.0234;
  float res_origin = -112.9637;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_18) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0234;
  float res_origin = -1052.0234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_19) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_origin = -12140;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_20) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x300000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xF;
  src1.bits[0] = 0x67E4FEEF;
  src2.bits[3] = 0x300000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFF;
  src2.bits[0] = 0x67E4FFFF;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x300000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x10E;
  result_origin.bits[0] = 0xCFC9FEEE;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(add_21) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(add_22) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 0}};
  s21_decimal test_v_2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 99);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_23) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 131072}};
  s21_decimal test_v_2 = {{0, 1, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], MAX_UINT);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_24) {
  s21_decimal test_v_1 = {{MAX_UINT, MAX_UINT, 4294967290, 131072}};
  s21_decimal test_v_2 = {{5, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967292);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_25) {
  s21_decimal test_v_1 = {{428, 0, 0, 0}};
  s21_decimal test_v_2 = {{165, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42965);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 0);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

//Вычитание---------------------------------------------

START_TEST(sub_1) {
  s21_decimal src1, src2, result;
  int a = 9403;
  int b = 202;
  int res_origin = 9201;
  int res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_int(result, &res_our);
  ck_assert_int_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal src1, src2, result;
  int a = 9403;
  float b = 202.098;
  float res_origin = 9200.902;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 202.098;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal src1, src2, result;
  float a = 9403.0;
  float b = 202.0098421232;
  float res_origin = 9200.9901578768;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal src1, src2, result;
  float a = -9403.000;
  float b = 202.0098421232;
  float res_origin = -9605.0098421232;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal src1, src2, result;
  float a = -9403.0e2;
  int b = -202;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x00010000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0x66F0;
  src2.bits[3] = 0x00030000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0x000451D6;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x00030000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0x0023E3EA;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal test_v_1 = {{1, 10, 0, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal test_v_1 = {{1, 4, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal test_v_1 = {{1, 0, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal test_v_1 = {{1, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  set_bit(&test_v_2, 127);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1234 + 1);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

//Умножение---------------------------------------------

START_TEST(mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0;
  float b = 9403.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 88416409;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{10000, 0, 0, 131072}};
  s21_decimal val2 = {{100000, 0, 0, 131072}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(val1, val2, &res);
  ck_assert_int_eq(res.bits[0], 100000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

//Деление---------------------------------------------

START_TEST(div_1) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_3) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal src1 = {{1000, 0, 0, 131072}};
  s21_decimal src2 = {{50, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal src1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal src1 = {{0, 12, MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//=========================================================
// 6 операторов сравнения

//Меньше---------------------------------------------

START_TEST(less_1) {
  s21_decimal test_v_1 = {{10, 0, 0, 0}};
  s21_decimal test_v_2 = {{15, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_2) {
  s21_decimal test_v_1 = {{6739, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_3) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_4) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_5) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_6) {
  s21_decimal test_v_1 = {{19876, 0, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_7) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_8) {
  s21_decimal test_v_1 = {{19876, 1, 0, 2147483648}};
  s21_decimal test_v_2 = {{19876, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

//Меньше/равно---------------------------------------------

START_TEST(less_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(less_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(less_eq_5) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

//Больше---------------------------------------------

START_TEST(greater_1) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_2) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);
}
END_TEST

START_TEST(greater_3) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_4) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(greater_5) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
}
END_TEST

//Больше/равно-----------------------------------------

START_TEST(greater_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(greater_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(greater_eq_5) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

//Равно-----------------------------------------

START_TEST(eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(eq_5) {
  s21_decimal test_v_1 = {{1234, 1, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 2, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

//Неравно-----------------------------------------

START_TEST(not_eq_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(not_eq_2) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234 + 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(not_eq_3) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(not_eq_4) {
  s21_decimal test_v_1 = {{1234, 0, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(not_eq_5) {
  s21_decimal test_v_1 = {{1234, 1, 0, 0}};
  s21_decimal test_v_2 = {{1234, 0, 2, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

//=========================================================
// 4 функции конвертации

// int -> decimal --------------------------------------

START_TEST(itod_1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_3) {
  s21_decimal result;
  s21_from_int_to_decimal(1234, &result);
  ck_assert_int_eq(result.bits[0], 1234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(itod_5) {
  s21_decimal result;
  s21_from_int_to_decimal(__INT_MAX__, &result);
  ck_assert_int_eq(result.bits[0], __INT_MAX__);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_6) {
  s21_decimal result;
  s21_from_int_to_decimal(__INT_MAX__ + 0.1234234, &result);
  ck_assert_int_eq(result.bits[0], __INT_MAX__);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(itod_7) {
  s21_decimal *dst = NULL;
  int result = s21_from_int_to_decimal(123, dst);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"

START_TEST(itod_8) {
  s21_decimal *dst = NULL;
  int result = s21_from_int_to_decimal(-__INT_MAX__ - 1, dst);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

#pragma GCC diagnostic pop

// float -> decimal --------------------------------------

START_TEST(ftod_1) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(ftod_2) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(ftod_3) {
  s21_decimal result;
  s21_from_float_to_decimal(1.02E+09, &result);
  ck_assert_int_eq(result.bits[0], 1020000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(ftod_4) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147745792);
}
END_TEST

START_TEST(ftod_5) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(ftod_6) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(-1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(ftod_7) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(0.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

// decimal -> int --------------------------------------

START_TEST(dtoi_1) {
  int number = 0;
  s21_decimal src = {{__INT_MAX__, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, __INT_MAX__);
}
END_TEST

START_TEST(dtoi_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(dtoi_3) {
  int number = 0;
  s21_decimal src = {{1234, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -1234);
}
END_TEST

START_TEST(dtoi_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 1);
}
END_TEST

START_TEST(dtoi_5) {
  int number = 0;
  s21_decimal src = {{100, 0, 0, 65536}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 100);
}
END_TEST

START_TEST(dtoi_6) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 65536}};
  // s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 1);
  // CONVERTATION_ERROR
}
END_TEST

START_TEST(dtoi_7) {
  int number = 0;
  s21_decimal src = {{1234567890, 0, 0, 21476802}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 1);
  // CONVERTATION_ERROR
}
END_TEST

// decimal -> float --------------------------------------

START_TEST(dtof_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(dtof_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(dtof_3) {
  float number = 0.0;
  s21_decimal src = {{MAX_UINT, MAX_UINT, 0, 0}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

//=========================================================
// 4 математические функции

// floor_decimal --------------------------------------

START_TEST(floor_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal v_1 = {{679988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal v_1 = {{679988, 0, 0, 2147745796}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 25);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

// round_decimal --------------------------------------

START_TEST(round_1) {
  s21_decimal v_1 = {{5, 0, 1, 0}};
  // set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 5);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_2) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_3) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(round_4) {
  s21_decimal v_1 = {{0, 1, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 0);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_5) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 26);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_6) {
  s21_decimal v_1 = {{257345, 0, 0, 0}};
  set_scale(&v_1, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 26);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

// negate_decimal --------------------------------------

START_TEST(negate_1) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

// truncate_decimal --------------------------------------

START_TEST(truncate_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal v_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-2744406, &v_1);
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 2744406);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

//=========================================================

//=========================================================
// 4 арифметических оператора

// Сложение ---------------------------------------------

Suite *add(void) {
  Suite *s1_1 = suite_create(COLOR_SUITE("-- ADD --"));
  TCase *tc1 = tcase_create(COLOR_CASE("ADD"));

  tcase_add_test(tc1, add_1);
  tcase_add_test(tc1, add_2);
  tcase_add_test(tc1, add_3);
  tcase_add_test(tc1, add_4);
  tcase_add_test(tc1, add_5);
  tcase_add_test(tc1, add_6);
  tcase_add_test(tc1, add_7);
  tcase_add_test(tc1, add_8);
  tcase_add_test(tc1, add_9);
  tcase_add_test(tc1, add_10);
  tcase_add_test(tc1, add_11);
  tcase_add_test(tc1, add_12);
  tcase_add_test(tc1, add_13);
  tcase_add_test(tc1, add_14);
  tcase_add_test(tc1, add_15);
  tcase_add_test(tc1, add_16);
  tcase_add_test(tc1, add_17);
  tcase_add_test(tc1, add_18);
  tcase_add_test(tc1, add_19);
  tcase_add_test(tc1, add_20);
  tcase_add_test(tc1, add_21);
  tcase_add_test(tc1, add_22);
  tcase_add_test(tc1, add_23);
  tcase_add_test(tc1, add_24);
  tcase_add_test(tc1, add_25);

  suite_add_tcase(s1_1, tc1);
  return s1_1;
}

// Вычитание ---------------------------------------------

Suite *sub(void) {
  Suite *s2 = suite_create(COLOR_SUITE("-- SUB --"));
  TCase *tc2 = tcase_create(COLOR_CASE("SUB"));

  tcase_add_test(tc2, sub_1);
  tcase_add_test(tc2, sub_2);
  tcase_add_test(tc2, sub_3);
  tcase_add_test(tc2, sub_4);
  tcase_add_test(tc2, sub_5);
  tcase_add_test(tc2, sub_6);
  tcase_add_test(tc2, sub_7);
  tcase_add_test(tc2, sub_8);
  tcase_add_test(tc2, sub_9);
  tcase_add_test(tc2, sub_10);
  tcase_add_test(tc2, sub_11);

  suite_add_tcase(s2, tc2);
  return s2;
}

// Умножение ---------------------------------------------

Suite *mul(void) {
  Suite *s3 = suite_create(COLOR_SUITE("-- MUL --"));
  TCase *tc3 = tcase_create(COLOR_CASE("MUL"));

  tcase_add_test(tc3, mul_1);
  tcase_add_test(tc3, mul_2);
  tcase_add_test(tc3, mul_3);
  tcase_add_test(tc3, mul_4);
  tcase_add_test(tc3, mul_5);
  tcase_add_test(tc3, mul_6);
  tcase_add_test(tc3, mul_7);
  tcase_add_test(tc3, mul_8);
  tcase_add_test(tc3, mul_9);
  tcase_add_test(tc3, mul_10);

  suite_add_tcase(s3, tc3);
  return s3;
}

// Деление -----------------------------------------------

Suite *div_suit(void) {
  Suite *s4 = suite_create(COLOR_SUITE("-- DIV --"));
  TCase *tc4 = tcase_create(COLOR_CASE("DIV"));

  tcase_add_test(tc4, div_1);
  tcase_add_test(tc4, div_2);
  tcase_add_test(tc4, div_3);
  tcase_add_test(tc4, div_4);
  tcase_add_test(tc4, div_5);
  tcase_add_test(tc4, div_6);
  tcase_add_test(tc4, div_7);
  tcase_add_test(tc4, div_8);

  suite_add_tcase(s4, tc4);
  return s4;
}

//=========================================================
// 6 операторов сравнения

// Меньше -----------------------------------------------

Suite *less(void) {
  Suite *s5 = suite_create(COLOR_SUITE("-- LESS --"));
  TCase *tc5 = tcase_create(COLOR_CASE("LESS"));

  tcase_add_test(tc5, less_1);
  tcase_add_test(tc5, less_2);
  tcase_add_test(tc5, less_3);
  tcase_add_test(tc5, less_4);
  tcase_add_test(tc5, less_5);
  tcase_add_test(tc5, less_6);
  tcase_add_test(tc5, less_7);
  tcase_add_test(tc5, less_8);

  suite_add_tcase(s5, tc5);
  return s5;
}

// Меньше/равно -----------------------------------------

Suite *less_eq(void) {
  Suite *s6 = suite_create(COLOR_SUITE("-- LESS_EQ --"));
  TCase *tc6 = tcase_create(COLOR_CASE("LESS_EQ"));

  tcase_add_test(tc6, less_eq_1);
  tcase_add_test(tc6, less_eq_2);
  tcase_add_test(tc6, less_eq_3);
  tcase_add_test(tc6, less_eq_4);
  tcase_add_test(tc6, less_eq_5);

  suite_add_tcase(s6, tc6);
  return s6;
}

// Больше -----------------------------------------------

Suite *greater(void) {
  Suite *s7 = suite_create(COLOR_SUITE("-- GR8R --"));
  TCase *tc7 = tcase_create(COLOR_CASE("GR8R"));

  tcase_add_test(tc7, greater_1);
  tcase_add_test(tc7, greater_2);
  tcase_add_test(tc7, greater_3);
  tcase_add_test(tc7, greater_4);
  tcase_add_test(tc7, greater_5);

  suite_add_tcase(s7, tc7);
  return s7;
}

// Больше/равно -----------------------------------------

Suite *greater_eq(void) {
  Suite *s8 = suite_create(COLOR_SUITE("-- GR8R_EQ --"));
  TCase *tc8 = tcase_create(COLOR_CASE("GR8R_EQ"));

  tcase_add_test(tc8, greater_eq_1);
  tcase_add_test(tc8, greater_eq_2);
  tcase_add_test(tc8, greater_eq_3);
  tcase_add_test(tc8, greater_eq_4);
  tcase_add_test(tc8, greater_eq_5);

  suite_add_tcase(s8, tc8);
  return s8;
}

// Равно -----------------------------------------------

Suite *eq(void) {
  Suite *s9 = suite_create(COLOR_SUITE("-- EQ --"));
  TCase *tc9 = tcase_create(COLOR_CASE("EQ"));

  tcase_add_test(tc9, eq_1);
  tcase_add_test(tc9, eq_2);
  tcase_add_test(tc9, eq_3);
  tcase_add_test(tc9, eq_4);
  tcase_add_test(tc9, eq_5);

  suite_add_tcase(s9, tc9);
  return s9;
}

// Неравно ---------------------------------------------

Suite * not_eq (void) {
  Suite *s10 = suite_create(COLOR_SUITE("-- !EQ --"));
  TCase *tc10 = tcase_create(COLOR_CASE("!EQ"));

  tcase_add_test(tc10, not_eq_1);
  tcase_add_test(tc10, not_eq_2);
  tcase_add_test(tc10, not_eq_3);
  tcase_add_test(tc10, not_eq_4);
  tcase_add_test(tc10, not_eq_5);

  suite_add_tcase(s10, tc10);
  return s10;
}

//=========================================================
// 4 функции конвертации

// int -> decimal --------------------------------------

Suite *itod(void) {
  Suite *s11 = suite_create(COLOR_SUITE("-- ITOD --"));
  TCase *tc11 = tcase_create(COLOR_CASE("ITOD"));

  tcase_add_test(tc11, itod_1);
  tcase_add_test(tc11, itod_2);
  tcase_add_test(tc11, itod_3);
  tcase_add_test(tc11, itod_4);
  tcase_add_test(tc11, itod_5);
  tcase_add_test(tc11, itod_6);
  tcase_add_test(tc11, itod_7);
  tcase_add_test(tc11, itod_8);

  suite_add_tcase(s11, tc11);
  return s11;
}

// float -> decimal --------------------------------------

Suite *ftod(void) {
  Suite *s12 = suite_create(COLOR_SUITE("-- FTOD --"));
  TCase *tc12 = tcase_create(COLOR_CASE("FTOD"));

  tcase_add_test(tc12, ftod_1);
  tcase_add_test(tc12, ftod_2);
  tcase_add_test(tc12, ftod_3);
  tcase_add_test(tc12, ftod_4);
  tcase_add_test(tc12, ftod_5);
  tcase_add_test(tc12, ftod_6);
  tcase_add_test(tc12, ftod_7);

  suite_add_tcase(s12, tc12);
  return s12;
}

// decimal -> int --------------------------------------

Suite *dtoi(void) {
  Suite *s13 = suite_create(COLOR_SUITE("-- DTOI --"));
  TCase *tc13 = tcase_create(COLOR_CASE("DTOI"));

  tcase_add_test(tc13, dtoi_1);
  tcase_add_test(tc13, dtoi_2);
  tcase_add_test(tc13, dtoi_3);
  tcase_add_test(tc13, dtoi_4);
  tcase_add_test(tc13, dtoi_5);
  tcase_add_test(tc13, dtoi_6);
  tcase_add_test(tc13, dtoi_7);

  suite_add_tcase(s13, tc13);
  return s13;
}

// decimal -> float ------------------------------------

Suite *dtof(void) {
  Suite *s14 = suite_create(COLOR_SUITE("-- DTOF --"));
  TCase *tc14 = tcase_create(COLOR_CASE("DTOF"));

  tcase_add_test(tc14, dtof_1);
  tcase_add_test(tc14, dtof_2);
  tcase_add_test(tc14, dtof_3);

  suite_add_tcase(s14, tc14);
  return s14;
}

//=========================================================
// 4 матемаматические функции

Suite *floor_s(void) {
  Suite *s15 = suite_create(COLOR_SUITE("-- FLR --"));
  TCase *tc15 = tcase_create(COLOR_CASE("FLR"));

  tcase_add_test(tc15, floor_1);
  tcase_add_test(tc15, floor_2);
  tcase_add_test(tc15, floor_3);
  tcase_add_test(tc15, floor_4);

  suite_add_tcase(s15, tc15);
  return s15;
}

Suite *round_s(void) {
  Suite *s16 = suite_create(COLOR_SUITE("-- RND --"));
  TCase *tc16 = tcase_create(COLOR_CASE("RND"));

  tcase_add_test(tc16, round_1);
  tcase_add_test(tc16, round_2);
  tcase_add_test(tc16, round_3);
  tcase_add_test(tc16, round_4);
  tcase_add_test(tc16, round_5);
  tcase_add_test(tc16, round_6);

  suite_add_tcase(s16, tc16);
  return s16;
}

Suite *negate(void) {
  Suite *s17 = suite_create(COLOR_SUITE("-- NEGT --"));
  TCase *tc17 = tcase_create(COLOR_CASE("NEGT"));

  tcase_add_test(tc17, negate_1);
  tcase_add_test(tc17, negate_2);

  suite_add_tcase(s17, tc17);
  return s17;
}

Suite *truncate(void) {
  Suite *s18 = suite_create(COLOR_SUITE("-- TRUNC --"));
  TCase *tc18 = tcase_create(COLOR_CASE("TRUNC"));

  tcase_add_test(tc18, truncate_1);
  tcase_add_test(tc18, truncate_2);

  suite_add_tcase(s18, tc18);
  return s18;
}

//=========================================================

void case_test(Suite *s) {
  SRunner *all_test = srunner_create(s);
  srunner_set_fork_status(all_test, CK_NOFORK);
  srunner_run_all(all_test, CK_NORMAL);
  srunner_free(all_test);
}

int main() {
  int success = 0;

  printf(
      "\033[30;43m\n\t(∩｡•́‿•̀｡)⊃--☆ﾟ ==== YOU SHALL PASS ==== "
      "ﾟ☆--⊂(｡•́‿•̀｡∩)\033[0m\n");

  VOILA("4 арифметических оператора:")
  case_test(add());
  case_test(sub());
  case_test(mul());
  case_test(div_suit());
  VOILA("6 операторов сравнения:")
  case_test(less());
  case_test(less_eq());
  case_test(greater());
  case_test(greater_eq());
  case_test(eq());
  case_test(not_eq ());
  VOILA("4 функции конвертации:")
  case_test(itod());
  case_test(ftod());
  case_test(dtoi());
  case_test(dtof());
  VOILA("4 математические функции:")
  case_test(floor_s());
  case_test(round_s());
  case_test(negate());
  case_test(truncate());

  printf(
      "\033[30;43m\n\t∩(｡•́‿•̀｡)∩ ==== TEST END (yaaay) ==== "
      "∩(｡•́‿•̀｡)∩\033[0m\n\n");

  return success;
}