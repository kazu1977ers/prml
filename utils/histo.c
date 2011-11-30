/* 
	 ヒストグラムを求める
	 Time-stamp: <00:24:47 2004/11/13>
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "pattern.h"

int 
main(int argc, char **argv)
{
	int    i;
	int    dim, size;
	int    *count, index, num_level;
	double min, max, step;
	double *data;
	FILE   *fp;

	if(argc < 4){
		fprintf(stderr, "\n[使用法] : histo <file> [-step (num)]\n");
		exit(1);
	}

	/* 引数を読み込む */
	if(is_opt(argc, argv, "-step"))
		step = get_double_arg(argc, argv, "-step");
	else{
		fprintf(stderr, "\n[エラー] : 階級の幅を必ず指定して下さい\n");
		exit(1);
	}

	/* データの個数を調べる */
	get_size(argv[1], &dim, &size);
	size = dim * size;
	data = new_double_vector(size);
	
	/* ファイルを開く */
	if((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
		exit(1);
	}

	/* データの最大値と最小値を見つける */
	min = DBL_MAX;
	max = -DBL_MAX;
	for(i = 0; i< size; i++){
		
		fscanf(fp, "%lf", &data[i]);
		
		if(min > data[i])
			min = data[i];
		else if(max < data[i])
			max = data[i];
	}

	/* 準備 */
	num_level = (int)roundoff((max - min) / step, 0.1);
	count = new_int_vector(num_level);
	
	for(i = 0; i < num_level; i++)
		count[i] = 0;
	
	/* データを読み込みつつカウントをする */
	for(i = 0; i < size; i++){

		/* 何番目の階級に属するか計算する */
		index = floor((data[i] - min) / step);

		/* カウントを増やす */
		count[index]++;
	}

	/* 結果を出力 */
	for(i = 0; i < num_level; i++)
		fprintf(stdout, "%+8.3f --> %+8.3f   [ %+8.3f ]\t%5d\n", 
						min + step * i, min + step * (i+1), 
						(2 * min + step * i + step * (i+1)) / 2,
						count[i]);
	
	/* 配列を解放 */
	free_int_vector(count);
	free_double_vector(data);

	exit(0);
}
