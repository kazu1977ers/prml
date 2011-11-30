/*
	相関係数行列を計算する
	Time-stamp: <12:13:15 2004/10/29>
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int      i, j;
	int      flag = 0;
	int      dim, size;
	double **data;
	double  *mean;
	double **sigma;
	double **corr;
	FILE    *fp;

	if(argc < 2){
		fprintf(stderr, "\n[使用法] : corrmat <file> (-s)\n");
		exit(1);
	}

	/* 出力フラグを調べる */
	if(is_opt(argc, argv, "-s"))
		flag = 1;
	
	/* 次元数とサンプル数を調べる */
	get_size(argv[1], &dim, &size);
	data = new_double_matrix(size, dim);

	/* データを読み込む */
	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}
	
	for(i = 0; i < size; i++)
		for(j = 0; j < dim; j++)
			fscanf(fp, "%lf", &data[i][j]);

	fclose(fp);

	/* 平均を計算する */
	mean = calc_mean(data, size, dim);

	/* 共分散行列を計算する */
	sigma = calc_cov_mat(data, mean, size, dim);

	/* 相関係数行列を計算する */
	corr = calc_corr_mat(sigma, dim);

	/* 結果を出力 */
	if(!flag)
		printf("Correlation Matrix:\n");

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			printf("%#+.2f", corr[i][j]);
			if(j < dim - 1)
				printf(" ");
		}
		printf("\n");
		fflush(stdout);
	}

	/* 終了処理 */
	free_double_matrix(data);
	free_double_vector(mean);
	free_double_matrix(sigma);
	free_double_matrix(corr);

	exit(0);
}
