/*
	逆行列を計算する
	Time-stamp: <12:30:02 2003/11/5>
*/
#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int
main(int argc, char **argv)
{
	int i, j;
	int row, col;
	double det;
	double **covariance, **inverse;
	FILE *fin;

	if(argc != 2) {
		fprintf(stderr, "\n[使用法] : inverse <file>\n");
		exit(1);
	}

	/* 次元数を確認 */
	get_size(argv[1], &col, &row);
	
	if(row != col){
		fprintf(stderr, "\n[エラー] : 指定された行列は正方行列ではありません\n");
		exit(2);
	}

	/* ファイルの有無を確認 */
	if((fin = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(3);
	}

	/* 配列を確保 */
	covariance = new_double_matrix(row, col);
	inverse = new_double_matrix(row, col);
	
	/* データを読み込む */
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fin, "%lf", &covariance[i][j]);

	/* LU分解を経由して逆行列の計算 */
	inverse = matinv(row, covariance, &det);

	/* 結果を出力 */
  fprintf(stdout, "det = %#+.6g\n\n", det);
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++){
			fprintf(stdout, "%#+.6g", inverse[i][j]);
			if(j != col-1)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}

	/* 配列を解放 */
	free_double_matrix(covariance);
	free_double_matrix(inverse);

	exit(0);
}
