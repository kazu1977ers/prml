/* 数値演算を行う関数群 */
#ifndef CALC_UTILS_H
#define CALC_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "ary_utils.h"
#include "mat_utils.h"

#define  N_gamma 8.0
#define  B0      1.0
#define  B1      (-1.0 / 2.0)
#define  B2      (+1.0 / 6.0)
#define  B4      (-1.0 / 30.0)
#define  B6      (+1.0 / 42.0)
#define  B8      (-1.0 / 30.0)
#define  B10     (+5.0 / 66.0)
#define  B12     (-691.0 / 2730.0)
#define  B14     (+7.0 / 6.0)
#define  B16     (-3617.0 / 510.0)


/* 演算に関する関数。桁溢れ防止機能付き */
double pow2(double x);                   /* 2乗の計算 */
double add(double x, double y);          /* 足し算 */
double del(double x, double y);          /* 引き算 */
double dvid(double x, double y);         /* 割り算 */
double mult(double x, double y);         /* 掛け算 */
double safe_exp(double x);               /* exp()の計算 */

/* その他の演算に関する関数 */
double roundoff(double val, int pos);    /* 四捨五入した値を返す */
int gcd(int x, int y);                   /* 最大公約数を求める */
int lcm(int x, int y);                   /* 最小公倍数を求める */

/* 分布や統計量に関する関数 */
/* 単変量正規分布 N(μ,σ)の X における値を計算する */
double get_val_norm(double mean, double sigma, double X);
/* 多変量正規分布 N(Μ,Σ)の X に対する値を計算する */
double get_multi_norm(double *mean, double **covmat, double *X, int dim);
/* 平均を計算する */
double *calc_mean(double **mat, int nrow, int ncol);
/* 共分散行列を計算する */
double **calc_cov_mat(double **mat, double *mean, int nrow, int ncol);
/* 相関係数行列を計算する */
double **calc_corr_mat(double **mat, int dim);

/* 乱数に関する関数 */
double uni_rnd(void);                        /* 一様乱数 */
double norm_rnd(double sigma, double mean);  /* 正規分布 */
double beta_rnd(double a, double b);         /* ベータ分布 */
double cauchy_rnd(void);                     /* コーシー分布 */
double chisq_rnd(double n);                  /* カイ2乗分布 */
double exp_rnd(void);                        /* 指数分布 */
double f_rnd(double n1, double n2);          /* F分布 */
double gamma_rnd(double a);                  /* ガンマ分布 */
double pow_rnd(double n);                    /* 累乗分布 */
double tri_rnd(void);                        /* 三角分布 */
double t_rnd(double n);                      /* t分布 */
int geome_rnd(double p);                     /* 幾何分布 */
int bin_rnd(int n, double p);                /* 2項分布 */
int poi_rnd(double lambda);                  /* ポアソン分布 */
double *rnd_vect(int dim);                   /* 単位球上のランダムな点 */
double get_volume_sphere(double r, int dim); /* 半径rの超球の体積 */

/* 組合せに関する関数 */
unsigned int num_comb(int n, int k);              /* 組合せの数 */
int **gen_comb(int n, int k, unsigned int *size); /* 組合せのリスト */

/* Γ関数の値を計算 */
double gamma(double x);
double loggamma(double x);

#endif
