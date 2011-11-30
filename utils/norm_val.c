#include <stdio.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j;
	int dim, num;
	double *mean, **sigma, *X;
	FILE *fp;

	if(argc < 4){
		fprintf(stderr, "\n[エラー] : 引数が足りません");
		fprintf(stderr, "\n[使用法] : norm_val <file> <mean> <sigma>\n");
		exit(1);
	}
	
	get_size(argv[1], &dim, &num);

	/* 平均を読み込む */
	mean = new_double_vector(dim);
	if((fp = fopen(argv[2], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : %s が開けません\n", argv[2]);
		exit(1);
	}
	for(i = 0; i < dim; i++)
		fscanf(fp, "%lf", &mean[i]);
	fclose(fp);

	/* 共分散行列を読み込む */
	sigma = new_double_matrix(dim, dim);
	if((fp = fopen(argv[3], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : %s が開けません\n", argv[3]);
		exit(1);
	}
	for(i = 0; i < dim; i++)
		for(j = 0; j < dim; j++)
			fscanf(fp, "%lf", &sigma[i][j]);
	fclose(fp);

	/* データを1点ずつ読み込みながら正規分布の値を計算する */
	X = new_double_vector(dim);
	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : %s が開けません\n", argv[1]);
		exit(1);
	}
	
	for(i = 0; i < num; i++){
		for(j = 0; j < dim; j++)
			fscanf(fp, "%lf", &X[j]);
		
		printf("%f\n", get_multi_norm(mean, sigma, X, dim));
		fflush(stdout);
	}
	
	fclose(fp);
	
	free_double_vector(mean);
	free_double_matrix(sigma);
	free_double_vector(X);

	exit(0);
}
