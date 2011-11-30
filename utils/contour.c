#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

#define  DIM      2
#define  NAMELEN  50

int main(int argc, char **argv)
{
	int    l, i, j;
	int    dim, num;
	int    step;
	int    level;
	char   name[NAMELEN];
	double min, max, shift, threshold;
	double **data;
	FILE   *fp;

	if(argc != 4){
		fprintf(stderr, "\n[使用法] : contour <file> <step> <level>\n");
		exit(1);
	}

	get_size(argv[1], &dim, &num);

	if(dim != DIM + 1){
		fprintf(stderr, "\n[エラー] : このプログラムは2次元データのみ対応\n");
		exit(1);
	}

	step = atoi(argv[2]);
	level = atoi(argv[3]);
	data = new_double_matrix(num, dim);

	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : %s が開けません\n", argv[1]);
		exit(1);
	}
	
	for(i = 0; i < num; i++)
		for(j = 0; j < dim; j++)
			fscanf(fp, "%lf", &data[i][j]);
	
	fclose(fp);
	
	min = DBL_MAX;
	max = -DBL_MAX;
	for(i = 0; i < num; i++){
		if(min > data[i][2])
			min = data[i][2];
		if(max < data[i][2])
			max = data[i][2];
	}

	shift = (max - min) / ((double)level + 1.0);
	threshold = min + shift;
	
	for(l = 1; l <= level; l++){
	
		sprintf(name, "level%d.dat", l);
		if((fp = fopen(name, "w")) == NULL){
			fprintf(stderr, "\n[エラー] : %sが用意できませんでした\n", name);
			exit(1);
		}

		for(i = 0; i < num; i++){

			if(((i+1) % step) != 1){

				/* 指定された等高線かどうか判定 */
				if((data[i][2] - threshold) * (data[i-1][2] - threshold) < 0.0){

					for(j = 0; j < 2; j++)
						fprintf(fp, "%f ", (data[i][j] + data[i-1][j]) / 2.0);
					fprintf(fp, "\n");

				}

			}

		}

		threshold += shift;
		fclose(fp);
	}

	free_double_matrix(data);

	exit(0);
}
