#include "k_nn_disc.h"

void
calc_dist(Spec *spc, Data *dat, KNN *knn, int x)
{
	int i, j;
	double tmp_dist;

	/* テストサンプルと訓練サンプルとの距離を計算する */
	for(i = 0; i < spc->tr_total; i++){
		tmp_dist = 0.0;

		for(j = 0; j < spc->feature; j++)
			tmp_dist += 
				(dat->x_tr[i][j] - dat->x_te[x][j]) *
				(dat->x_tr[i][j] - dat->x_te[x][j]);

		knn->dist_queue[i] = tmp_dist;
		knn->index[i] = i;
	}
}
