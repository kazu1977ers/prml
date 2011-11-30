/* 
	 行列を積を計算する 
	 Time-stamp: <12:31:23 2003/11/5>
*/
#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j, k = 0;
	int row[2], col[2];
	double **a, **b, **c;
	FILE *fin;

	if(argc != 3) {
		fprintf(stderr, "\n[使用法] : multmat <file1> <file2>\n");
		exit(1);
	}

	while(k < 2){
		/* 次元数を確認 */
		i = 0;
		j = 0;
		get_size(argv[k+1], &j, &i);
		row[k] = i;
		col[k] = j;
		k++;
	};

	/* 配列を確保 */
	a = new_double_matrix(row[0], col[0]);
	b = new_double_matrix(row[1], col[1]);

	/* データを読み込む */
	if((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}
	
	for(i = 0; i < row[0]; i++)
		for(j = 0; j < col[0]; j++)
			fscanf(fin, "%lf", &a[i][j]);

	fclose(fin);

	if((fin = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[2]);
		exit(1);
	}
	
	for(i = 0; i < row[1]; i++)
		for(j = 0; j < col[1]; j++)
			fscanf(fin, "%lf", &b[i][j]);

	fclose(fin);

	/* 行列の積を出力 */
	c = mult_mat(a, row[0], col[0], b, row[1], col[1]);

	for(i = 0; i < row[0]; i++){
		for(j = 0; j < col[1]; j++){
			fprintf(stdout, "%f", c[i][j]);
			if(j != col[1] - 1)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}

	/* 配列を解放 */
	free_double_matrix(a);
	free_double_matrix(b);
	free_double_matrix(c);

	exit(0);
}
