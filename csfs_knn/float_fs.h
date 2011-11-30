/*
	k-nearest neighborのn-fold cross validation または leave-one-out法によ
	る識別率を評価関数にするfloating searchを実行するプログラム
	Time-stamp: <08:46:23 2004/8/3>

	[ 参考文献 ]
	P. Pudil, J. Novovicova and J. Kittler,
	Floating Search Methods in Feature Selection,
	Pattern Recognition Letters, 15(1994), 1119--1125.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include "pattern.h"

/* 動作の定義 */
#define  INITIAL   0   /* 初期状態 */
#define  BACKWARD  1   /* 後退状態 */
#define  FORWARD   2   /* 前進状態 */
#define  FINAL     3   /* 最終状態 */

/* 選択方法の定義 */
#define  SBFS      0   /* SBSのfloating版 */
#define  SFFS      1   /* SFSのfloating版 */
#define  SBS       2   /* 後向き逐次選択(SBS)*/
#define  SFS       3   /* 前向き逐次選択(SFS) */

typedef struct{
	int      class;      /* クラス数 */
	int      dim;        /* 次元数 */
	int     *trnum;      /* クラス毎のサンプル数 */
	int      total;      /* サンプル数の合計 */
	int     *label;      /* クラスラベル */
	char    *filename;   /* データのファイル名 */
	double **sample;     /* 訓練データ */
	int     *split_num;  /* 各分割におけるデータの個数 */
}Data;

typedef struct{
	int       size;      /* 個数 */
	int      *label;     /* クラスラベル */
	double  **x;         /* データ */
}DInfo;

typedef struct{
	int num;             /* 特徴集合の要素数 */
	int *fi;             /* 特徴集合 */
}Subset;

typedef struct{
	int     ext_num;     /* 選択する特徴の個数 */
	Subset  cur;         /* 現在の特徴集合 */
	Subset  rej;         /* 使用していない特徴集合 */
	Subset  sel;         /* 選択された特徴集合 */
	Subset  best;        /* traceモードで使用。一番良い結果を保存 */
	double  best_rate;   /* 識別率の最大値 */
	double *C;           /* 評価関数の値 */
}FInfo;

typedef struct{
	double  *dist;       /* 距離を保存する。距離でソートする際に必要。*/
	int     *index;      /* 訓練サンプルの番号を保存する。ソートに必要。 */
}KInfo;


/* 関数のプロトタイプ宣言 */
void   read_data(Data *dat);
void   read_opt(int argc, char **argv, Data *dat, FInfo *fs, int method, 
								int *tmode, int *knum, int *fold, unsigned int *seed);
void   print_fs(FInfo *fs, int time, int mode);
void   add_one(FInfo *fs, int target, double ans_value);
void   check(Data *dat, FInfo *fs, int *target, double *ans_value, int fold,
						 int *eval_time, int method, int knum);
void   output(FInfo *fs, int trace_flag, int time);
void   remove_one(FInfo *fs, int target, double ans_value);
void   eval_best(FInfo *fs);
int    *fs_sort(int num, int *list);
void   alloc_prm(Data *dat, FInfo *fs);
void   free_prm(Data *dat, FInfo *fs);
void   sbs(Data *dat, FInfo *fs, double *ans_value, int fold, int *target,
					 int *eval_time, int knum);
void   sfs(Data *dat, FInfo *fs, double *ans_value, int fold, int *target,
					 int *eval_time, int knum);
int    init_step(Data *dat, FInfo *fs, int *eval_time, int mode, int fold,
								 int knum, int method);
void   shuffle(Data *dat, unsigned int seed);
void   calc_dist(DInfo *train, DInfo *test, KInfo *knn, FInfo *fs, int k);
int    find_class(int class, int knum, DInfo *train, KInfo *knn);
void   dist_sort(double *dist, int *index, int first, int last);
double k_nn_disc(Data *dat, FInfo *fs, int fold, int knum);
int    get_min_index(double *dist, int *index, int num);
void   data_split(Data *dat, int start, int last, DInfo *train, DInfo *test,
									KInfo *knn, FInfo *fs);
int    *set_split(int fold, int total);
