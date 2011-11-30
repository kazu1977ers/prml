#include "float_fs.h"

void
data_split(Data *dat, int start, int last, DInfo *train, DInfo *test, 
					 KInfo *knn, FInfo *fs)
{
	int i, j;
	int count1 = 0, count2 = 0;

	/* 訓練と検査データの大きさを決定 */
	train->size = dat->total - (last - start);
	test->size  = last - start;
	
	/* 距離を保存する配列 */
	knn->dist = new_double_vector(train->size);
	
	/* データの番号を保存する配列 */
	knn->index = new_int_vector(train->size);
	
	/* 訓練データと検査データの配列を初期化 */
	train->label = new_int_vector(train->size);
	test->label = new_int_vector(test->size);
	
	train->x = new_double_matrix(train->size, fs->cur.num);
	test->x  = new_double_matrix(test->size, fs->cur.num);

	/* 分割開始 */
	for(i = 0; i < dat->total; i++){
		if((i >= start) && (i < last)){
			test->label[count1] = dat->label[i];
			for(j = 0; j < fs->cur.num; j++)
				test->x[count1][j] = dat->sample[i][fs->cur.fi[j]];
			count1++;
		}
		else{
			train->label[count2] = dat->label[i];
			for(j = 0; j < fs->cur.num; j++)
				train->x[count2][j] = dat->sample[i][fs->cur.fi[j]];
			count2++;
		}
	}

}
