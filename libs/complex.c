#include "complex.h"

/* x, y を複素数 z = x + iy に変換 */
complex c_conv(double x, double y)
{
	complex z;

	z.re = x;  z.im = y;
	return z;
}

/* 複素数 z = x + iy を文字列に変換 */
char *c_string(complex z)
{
	static char s[40];

	sprintf(s, "%g%+gi", z.re, z.im);
	return s;
}

/* 共役複素数 */
complex c_conj(complex z)
{
	z.im = - z.im;
	return z;
}

/* 絶対値 |z| */
double c_abs(complex z)
{
	double t;

	if (z.re == 0) return fabs(z.im);
	if (z.im == 0) return fabs(z.re);
	if (fabs(z.im) > fabs(z.re)) {
		t = z.re / z.im;
		return fabs(z.im) * sqrt(1 + t * t);
	} else {
		t = z.im / z.re;
		return fabs(z.re) * sqrt(1 + t * t);
	}
}

/* 偏角 */
double c_arg(complex z)
{
	return atan2(z.im, z.re);
}

/* 和 x + y */
complex c_add(complex x, complex y)
{
	x.re += y.re;
	x.im += y.im;
	return x;
}

/* 差 x - y */
complex c_sub(complex x, complex y)
{
	x.re -= y.re;;
	x.im -= y.im;
	return x;
}

/* 積 xy */
complex c_mul(complex x, complex y)
{
	complex z;

	z.re = x.re * y.re - x.im * y.im;
	z.im = x.re * y.im + x.im * y.re;
	return z;
}

/* 商 x / y (上位桁あふれ対策版) */
complex c_div(complex x, complex y)
{
	double w, d;
	complex z;

	if (fabs(y.re) >= fabs(y.im)) {
		w = y.im / y.re;  d = y.re + y.im * w;
		z.re = (x.re + x.im * w) / d;
		z.im = (x.im - x.re * w) / d;
	} 
  else {
		w = y.re / y.im;  d = y.re * w + y.im;
		z.re = (x.re * w + x.im) / d;
		z.im = (x.im * w - x.re) / d;
	}
	return z;
}

/* 指数関数 */
complex c_exp(complex x)
{
	double a;

	a = exp(x.re);
	x.re = a * cos(x.im);
	x.im = a * sin(x.im);
	return x;
}

/* 自然対数 */
complex c_log(complex x)
{
	complex z;

	z.re = 0.5 * log(x.re * x.re + x.im * x.im);
	z.im = atan2(x.im, x.re);
	return z;
}

/* 累乗 */
complex c_pow(complex x, complex y)
{
	return c_exp(c_mul(y, c_log(x)));
}

/* 正弦 */
complex c_sin(complex x)
{
	double e, f;

	e = exp(x.im);  f = 1 / e;
	x.im = 0.5 * cos(x.re) * (e - f);
	x.re = 0.5 * sin(x.re) * (e + f);
	return x;
}

/* 余弦 */
complex c_cos(complex x)
{
	double e, f;

	e = exp(x.im);  f = 1 / e;
	x.im = 0.5 * sin(x.re) * (f - e);
	x.re = 0.5 * cos(x.re) * (f + e);
	return x;
}

/* 正接 */
complex c_tan(complex x)
{
	double e, f, d;

	e = exp(2 * x.im);  f = 1 / e;
	d = cos(2 * x.re) + 0.5 * (e + f);
	x.re = sin(2 * x.re) / d;
	x.im = 0.5 * (e - f) / d;
	return x;
}

/* 双曲線正弦 */
complex c_sinh(complex x)
{
	double e, f;

	e = exp(x.re);  f = 1 / e;
	x.re = 0.5 * (e - f) * cos(x.im);
	x.im = 0.5 * (e + f) * sin(x.im);
	return x;
}

/* 双曲線余弦 */
complex c_cosh(complex x)
{
	double e, f;

	e = exp(x.re);  f = 1 / e;
	x.re = 0.5 * (e + f) * cos(x.im);
	x.im = 0.5 * (e - f) * sin(x.im);
	return x;
}

/* 双曲線正接 */
complex c_tanh(complex x)
{
	double e, f, d;

	e = exp(2 * x.re);  f = 1 / e;
	d = 0.5 * (e + f) + cos(2 * x.im);
	x.re = 0.5 * (e - f) / d;
	x.im = sin(2 * x.im) / d;
	return x;
}

/* 平方根 */
complex c_sqrt(complex x)
{
	double r, w;

	r = c_abs(x);
	w = sqrt(r + fabs(x.re));
	if (x.re >= 0) {
		x.re = SQRT05 * w;
		x.im = SQRT05 * x.im / w;
	} else {
		x.re = SQRT05 * fabs(x.im) / w;
		x.im = (x.im >= 0) ? SQRT05 * w : -SQRT05 * w;
	}
	return x;
}
