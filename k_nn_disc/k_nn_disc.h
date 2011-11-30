/* 
	 k近隣識別子を構成しテストサンプルを識別する 
	 Time-stamp: <09:56:28 2004/6/10> 
*/
#ifndef K_NN_DISC_H
#define K_NN_DISC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "pattern.h"

#define  NAME_LEN      50
#define  DEFAULT_KNUM  1
#define  TRUE          1
#define  FALSE         0

typedef struct {
	int class;                /* クラス数 */
	int feature;              /* 特徴数 */
	int *tr_sample;      /* 訓練サンプル数 */
	int *te_sample;      /* テストサンプル数 */
	int tr_total;             /* 訓練サンプルの総計 */
	int te_total;             /* テストサンプルの総計 */
} Spec;

typedef struct {
	char trname[NAME_LEN];    /* 訓練サンプルのファイル */
	char tename[NAME_LEN];    /* テストサンプルのファイル */
} File;

typedef struct {
	double **x_tr;        /* 訓練サンプル */
	double **x_te;        /* テストサンプル */
	int *label_tr;       /* 訓練サンプルのクラスラベル */
	int *label_te;       /* テストサンプルのクラスラベル */
} Data;

typedef struct {
	int knum;                 /* kの値 */
	double *dist_queue;  /* 各サンプルまでの距離 */
	int *index;          /* 訓練サンプルのindex */
	int **count;          /* 識別結果 */
} KNN;

/* 配列の管理、パラメータの初期化 */
int  read_opt(int argc, char **argv, Spec *spc, File *fil, KNN *knn);
void alloc_param(Spec *spc, Data *dat, KNN *knn);
void free_param(Spec *spc, Data *dat, KNN *knn);
void init_param(Spec *spc, Data *dat, KNN *knn);
void read_data(Spec *spc, File *fil, Data *dat);

/* テストサンプルとの距離を計算 */
void calc_dist(Spec *spc, Data *dat, KNN *knn, int x);
void quick_sort(double dist[], int index[], int first, int last);

/* テストサンプルを識別 */
int  disc(Spec *spc, Data *dat, KNN *knn);
void output(Spec *spc, KNN *knn);

#endif
