/*
	データの次元毎の最大値と最小値を返す
*/

#include <stdio.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j;
	int dim, num;
	int aflag = 0;
	double *min, *max, Min, Max, tmp;
	FILE *fp;

	/* 引数を調べる */
	if(argc < 2){
		fprintf(stderr, "\n[使用法] : minmax <file> (-all)\n");
		exit(1);
	}

	if(argc == 3)
		if(strcmp(argv[2], "-all") == 0)
			aflag = 1;

	/* データから次元数とサンプル数を判定する */
	get_size(argv[1], &dim, &num);

	/* 配列の初期化 */
	min = new_double_vector(dim);
	max = new_double_vector(dim);

	for(i = 0; i < dim; i++){
		min[i] = DBL_MAX;
		max[i] = -DBL_MAX;
	}
	Min = DBL_MAX;
	Max = -DBL_MAX;

	/* ファイルを開いてデータを読み込み最大値、最小値を判定 */
	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : %sが開けません\n", argv[1]);
		exit(1);
	}

	for(i = 0; i < num; i++){
		for(j = 0; j < dim; j++){
			fscanf(fp, "%lf", &tmp);

			if(min[j] > tmp){
				min[j] = tmp;
				if(Min > min[j])
					Min = min[j];
			}

			if(max[j] < tmp){
				max[j] = tmp;
				if(Max < max[j])
					Max = max[j];
			}

		}
	}

	fclose(fp);
		
	if(aflag)
		printf("%f %f\n", Min, Max);
	else
		for(i = 0; i < dim; i++)
			printf("%f %f\n", min[i], max[i]);
	fflush(stdout);

	free_double_vector(min);
	free_double_vector(max);

	exit(0);
}
