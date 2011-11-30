/* 
	 行列を和を出力
	 Time-stamp: <12:23:31 2003/11/5>
*/
#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int i, j;
	int row, col;
	double **a, **b, **c;
	FILE *fin;
	
	if(argc != 3) {
		fprintf(stderr, "\n[使用法] : addmat <file1> <file2>\n");
		exit(1);
	}

	/* 行列の大きさを確認 */
	get_size(argv[1], &col, &row);

	/* 配列を確保 */
	a = new_double_matrix(row, col);
	b = new_double_matrix(row, col);

	/* データを読み込む */
	if((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}
	
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fin, "%lf", &a[i][j]);

	fclose(fin);

	if((fin = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[2]);
		exit(1);
	}
	
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fin, "%lf", &b[i][j]);

	fclose(fin);

	/* 行列の積を出力 */
	c = add_mat(a, b, row, col);

	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			fprintf(stdout, "%f", c[i][j]);
			if(j != col - 1)
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
