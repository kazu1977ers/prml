#include "float_fs.h"

void
calc_dist(DInfo *train, DInfo *test, KInfo *knn, FInfo *fs, int k)
{
	int i, j;
	
	/* k番目の検査サンプルとの距離を計算する */
	for(i = 0; i < train->size; i++){
		knn->dist[i] = 0.0;
		
		/* 本来、距離なら平方根をとるべきだが、距離の小さい順に並び換えるだ
			 けなので2乗のままでも影響しない */
		for(j = 0; j < fs->cur.num; j++)
			knn->dist[i] += 
				(train->x[i][j] - test->x[k][j]) * (train->x[i][j] - test->x[k][j]);
		
		knn->index[i] = i;
	}
}
