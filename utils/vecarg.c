#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j;
	int flag = 0;
	int num_1, num_2;
	int dim_1, dim_2;
	double *vec_1, *vec_2;
	FILE *fp_1, *fp_2;

	if(argc < 3){
		fprintf(stderr, "\n[エラー] : 引数が足りません\n");
		fprintf(stderr, "[使用法] : vecarg <file1> <file2> (-rad)\n");
		exit(1);
	}

	/* ファイルから次元数とサンプル数を調べる。二つのファイルで一致しなけ
		 れば計算を行わない */
	get_size(argv[1], &dim_1, &num_1);
	get_size(argv[2], &dim_2, &num_2);

	if(is_opt(argc, argv, "-rad"))
		flag = 1;

	if((dim_1 != dim_2) || (num_1 != num_2)){
		fprintf(stderr, "\n[エラー] : 次元数、またはサンプル数が一致しません\n");
		exit(1);
	}

	/* ファイルからデータを一つ読み角度を計算する */
	if((fp_1 = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}
	if((fp_2 = fopen(argv[2], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[2]);
		exit(2);
	}

	vec_1 = new_double_vector(dim_1);
	vec_2 = new_double_vector(dim_2);

	for(i = 0; i < num_1; i++){

		for(j = 0; j < dim_1; j++)
			fscanf(fp_1, "%lf", &vec_1[j]);
		
		for(j = 0; j < dim_2; j++)
			fscanf(fp_2, "%lf", &vec_2[j]);

		/* 角度を計算して値を表示する */
		if(flag)
			fprintf(stdout, "%f\n", vec_arg(dim_1, vec_1, vec_2));
		else
			fprintf(stdout, "%f\n", vec_cos(dim_1, vec_1, vec_2));

	}

	free_double_vector(vec_1);
	free_double_vector(vec_2);
	
	fclose(fp_1);
	fclose(fp_2);

	exit(0);
}
