/*
  複素数計算ライブラリ。複素数 complex 型の変数 z を宣言するには、
  complex z;
  とする。この z に対して、実数部分は z.re 、虚数部分は z.im として参照
  する。
  Time-stamp: <11:36:42 2003/5/28>
*/
#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SQRT05 0.707106781186547524  /* sqrt(0.5) */

typedef struct{
  double re, im;
}complex;

complex c_conv(double x, double y);  /* x, y を複素数 z = x + iy に変換 */
char *c_string(complex z);           /* 複素数 z = x + iy を文字列に変換 */

complex c_conj(complex z);  /* 共役複素数 */
double c_abs(complex z);    /* 絶対値 |z| */
double c_arg(complex z);    /* 偏角 */

complex c_add(complex x, complex y); /* 和 x + y */
complex c_sub(complex x, complex y); /* 差 x - y */
complex c_mul(complex x, complex y); /* 積 xy */
complex c_div(complex x, complex y); /* 商 x / y (上位桁あふれ対策版) */

complex c_exp(complex x);            /* 指数関数 */
complex c_log(complex x);            /* 自然対数 */
complex c_pow(complex x, complex y); /* 累乗 */
complex c_sin(complex x);            /* 正弦 */
complex c_cos(complex x);            /* 余弦 */
complex c_tan(complex x);            /* 正接 */
complex c_sinh(complex x);           /* 双曲線正弦 */
complex c_cosh(complex x);           /* 双曲線余弦 */
complex c_tanh(complex x);           /* 双曲線正接 */
complex c_sqrt(complex x);           /* 平方根 */

#endif
