/* 
	 行列の各種演算を行う関数
	 一部C言語アルゴリズム辞典より引用したプログラム有り
	 Time-stamp: <12:08:28 2004/12/21>
*/
#ifndef MAT_UTILS_H
#define MAT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include "ary_utils.h"

#define STR_LENGTH     256      // ファイル名の最大の長さ
#define MAX_TIME       100      // 反復回数の上限
#define STOP_THRESHOLD 0.00001  // 反復計算の収束判定

/* LU分解を経由し逆行列を計算する */
double **inv_mat(double **mat, double *det, int row);

/* GaussJordan法による逆行列の計算 */
double **matinv(int n, double **covmat, double *det);

/* 転置行列を求める */
double **trans_mat(double **mat, int row, int col);

/* 行列の積を求める */
double **mult_mat(double **a, int nrow1, int ncol1, 
											double **b, int nrow2, int ncol2);

/* ファイルにあるデータの次元数とサンプル数を解析する */
void get_size(char *filename, int *dim, int *num);

/* 1行当たりのバイト数の最大値を解析する */
void get_max_byte(char *filename, int *max_byte);

/* 内積を計算する */
double innerprod(int n, double *u, double *v);

/* 共分散行列を計算する */
double **calc_cov_mat(double **mat, double *mean,
													int nrow, int ncol);

/* 平均を求める */
double *calc_mean(double **mat, int nrow, int ncol);

/* 行列×ベクトルを計算する */
double *matxvec(double **mat, int nrow, int ncol,
										 double *v, int size);

/* ベクトル×行列を計算する */
double *vecxmat(double *v, int size, double **mat,
										 int nrow, int ncol);

/* 対角成分だけの行列(単位行列の整数倍)を返す */
double **unit_mat(int size, double val);

/* 行列の和A+Bを求める */
double **add_mat(double **a, double **b, int nrow, int ncol);

/* 行列の差A-Bを求める */
double **del_mat(double **a, double **b, int nrow, int ncol);

/* ベクトルの和を求める */
double *add_vec(double *a, double *b, int size);

/* ベクトルの差を求める */
double *del_vec(double *a, double *b, int size);

/* LU分解を利用した逆行列計算ルーチン */
double luinv(int n, double **a, double **a_inv);

/* LU分解 */
double ludec(int n, double **a, int *ip);

/* ベクトルをLpノルムで正規化する。ベクトル x は上書きされる */
void vec_normalize(int dim, double *x, int p);

/* ベクトルのLpノルムを計算する */
double get_vec_lp_norm(int dim, double *x, int p);

/* 二つのベクトルのなす角度をラジアン単位で返す */
double vec_arg(int dim, double *x, double *y);

/* 二つのベクトルのなす角度をcosの値で返す */
double vec_cos(int dim, double *x, double *y);

/* ランクを計算する */
int mat_rank(int dim, double **mat);
void hes(double **mat, int n);/* ヘッセンベルグ行列への変換 */
void hqr(double **mat, double *dr, double *di, int n);/* ヘッセンベルグ行列を用いたQR法 */

#endif
