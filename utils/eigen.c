#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pattern.h"

int
main(int argc, char **argv)
{
	int i, j;
	int row, col;
	double **mat;		 /* 行列のデータ */
	double *dr, *di;	 /* 固有値の実数部分 */
	FILE *fin;		 /* 固有値の虚数部分 */

	if(argc != 2) {
		fprintf(stderr, "\n[使用法] : eigen <file>\n");
		exit(1);
	}

	/* 次元数を確認 */
	get_size(argv[1], &col, &row);
	if(row != col){
		fprintf(stderr, "\n[エラー] : 指定された行列が正方行列ではありません\n");
		exit(2);
	}

	/* ファイルの有無を確認 */
	if((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(3);
	}

	/* 配列を確保 */
	mat = new_double_matrix(row, col);
	dr = new_double_vector(row);
	di = new_double_vector(row);

	/* データを読み込む */
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fin, "%lf", &mat[i][j]);

	/* 固有値の計算 */
	hes(mat, row);
	hqr(mat, dr, di, row);

	/* 結果を出力 */
	/* drが実数成分、diが虚数成分 */
	for(i = 0; i < row; i++)
		fprintf(stdout, "%.6f + %.6f i \n", dr[i], di[i]);

	/* 配列を解放 */
	free_double_matrix(mat);
	free_double_vector(dr);
	free_double_vector(di);

	exit(0);
}
