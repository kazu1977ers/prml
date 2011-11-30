/* 
	 転置行列を出力
	 Time-stamp: <12:31:49 2003/11/5>
*/
#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j;
	int row, col;
	double **a, **b;
	FILE *fin;

	if(argc != 2) {
		fprintf(stderr, "\n[使用法] : transmat <file>\n");
		exit(1);
	}

	/* 次元数を確認 */
	get_size(argv[1], &row, &col);

	/* 配列を確保 */
	a = new_double_matrix(col, row);

	/* ファイルの有無を確認 */
	if((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(2);
	}

	for(i = 0; i < col; i++)
		for(j = 0; j < row; j++)
			fscanf(fin, "%lf", &a[i][j]);

	fclose(fin);

	/* 転置した行列を出力 */
	b = trans_mat(a, row, col);
	
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			fprintf(stdout, "%.6f", b[i][j]);

			if(j != row-1)
				printf(" ");
		}
		fprintf(stdout, "\n");
	}

	/* 配列を確保 */
	free_double_matrix(a);
	free_double_matrix(b);

	exit(0);
}
