/*
	正規化を行うプログラム
	Time-stamp: <15:37:21 2004/1/21>
	[ 参考文献 ]
	(1) 標準正規分布で正規化する
	S.Theodoridis, K. Koutroumbas, Pattern Recognition.
	Preprocessing (Section 2.2), Feature Selection (Chatper 5), pp.141.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "pattern.h"

#define  MEAN_SIGMA  1
#define  MIN_MAX     2
#define  LP_NORM     3

int
main(int argc, char **argv)
{
	int i, j;
	int feat, num, type = MEAN_SIGMA;
	int max_index;
	int p, pflag = 0, rflag = 0;
	double mean, sigma, min, max;
	double **data;
	FILE *fp;

	if(argc < 2) {
		fprintf(stderr, "\n[使用法] : normalize <file> (-mean_sigma / -min_max / -lp (num) or inf) (-revert)\n");
		exit(1);
	}
	
	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}

	get_size(argv[1], &feat, &num);
	data = new_double_matrix(num, feat);
	for(i = 0; i < num; i++)
		for(j = 0; j < feat; j++)
			fscanf(fp, "%lf", &data[i][j]);
	
	fclose(fp);

	if(is_opt(argc, argv, "-mean_sigma"))
		type = MEAN_SIGMA;
	else if(is_opt(argc, argv, "-min_max"))
		type = MIN_MAX;
	else if(is_opt(argc, argv, "-lp")){
		type = LP_NORM;
		if(strcmp(get_char_arg(argc, argv, "-lp"), "inf") == 0){
			pflag = 1;
			p = 1;
		}
		if(!pflag)
			p = get_int_arg(argc, argv, "-lp");
		if(is_opt(argc, argv, "-revert"))
			rflag = 1;
	}
	
	if(type == MEAN_SIGMA){
		/* 平均と分散で正規化 */
		for(i = 0; i < feat; i++){
			
			mean = 0.0;  /* 平均を求める */
			for(j = 0; j < num; j++)
				mean += data[j][i];
			
			mean = mean / num;
			
			sigma = 0.0; /* 分散を求める */
			for(j = 0; j < num; j++)
				sigma += pow((data[j][i] - mean), 2.0);
			
			sigma = sqrt(sigma / (double)(num - 1));
			if(sigma < DBL_MIN)
				sigma = DBL_MIN;
			
			for(j = 0; j < num; j++) /* 正規化する */
				data[j][i] = (data[j][i] - mean) / sigma;
		}
	}
	else if(type == MIN_MAX){
		/* 最大値、最小値で[-1,1]に正規化 */
		for(i = 0; i < feat; i++){

			min = DBL_MAX;
			max = -DBL_MAX;
			for(j = 0; j < num; j++){
				if(min > data[j][i])
					min = data[j][i];
				else if(max < data[j][i])
					max = data[j][i];
			}

			for(j = 0; j < num; j++)
				data[j][i] = 
					(2.0 / (max - min)) * data[j][i] - ((max + min) / (max - min));
		}
	}
	else{
		/* Lp-ノルムで正規化する */
		if(pflag){  // L-∞ノルム
			for(i = 0; i < num; i++){
				max = fabs(data[i][0]);
				max_index = 0;
				for(j = 1; j < feat; j++){
					if(max < fabs(data[i][j])){
						max = fabs(data[i][j]);
						max_index = j;
					}
				}
				for(j = 0; j < feat; j++){
					if(j == max_index)
						data[i][j] = 1.0;
					else
						data[i][j] = 0.0;
				}
			}
		}
		else{       // Lp-ノルム
			for(i = 0; i < num; i++)
				vec_normalize(feat, data[i], p);
		}

		if(rflag)
			for(i = 0; i < num; i++)
				for(j = 0; j < feat; j++)
					data[i][j] = pow(data[i][j], (double)p);
	}

	/* 出力 */
	for(i = 0; i < num; i++){
		for(j = 0; j < feat; j++){
			fprintf(stdout, "%lf", data[i][j]);
			if(j != feat - 1)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}

	free_double_matrix(data);
	exit(0);
}
