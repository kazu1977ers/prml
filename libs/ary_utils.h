/* 
	 動的に配列を確保するための関数群
	 Time-stamp: <14:49:22 2004/11/23>
*/
#ifndef ARY_UTILS_H
#define ARY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

/* 浮動小数点(double)型の配列管理 */
/* 1次元配列 */
double *alloc_double_vector(int n);
double *new_double_vector(int n);
void   free_double_vector(double *v);

/* 2次元配列。大きさは一定。 */
double **alloc_double_matrix(int nrow, int ncol);
double **new_double_matrix(int nrow, int ncol);
void   free_double_matrix(double **a);

/* 整数(int)型の配列管理 */
/* 1次元配列 */
int  *alloc_int_vector(int n);
int  *new_int_vector(int n);
void free_int_vector(int *v);

/* 2次元配列。大きさは一定。 */
int  **alloc_int_matrix(int nrow, int ncol);
int  **new_int_matrix(int nrow, int ncol);
void free_int_matrix(int **a);

/* 浮動小数点(float)型の配列管理 */
/* 1次元配列 */
float *alloc_float_vector(int n);
float *new_float_vector(int n);
void  free_float_vector(float *v);

/* 2次元配列。大きさは一定。 */
float **alloc_float_matrix(int nrow, int ncol);
float **new_float_matrix(int nrow, int ncol);
void  free_float_matrix(float **a);

/* 文字列(char)型の配列管理 */
/* 1次元配列 */
char *alloc_char_vector(int n);
char *new_char_vector(int n);
void free_char_vector(char *v);

/* 2次元配列。大きさは一定。 */
char **alloc_char_matrix(int nrow, int ncol);
char **new_char_matrix(int nrow, int ncol);
void free_char_matrix(char **a);

#endif
