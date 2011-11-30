#include "k_nn_disc.h"

int
disc(Spec *spc, Data *dat, KNN *knn)
{
	int i;
	int max_class = 0, max_count;
	int min_dist_class;
	int *class_count;

	/* 準備 */
	class_count = new_int_vector(spc->class);
	for(i = 0; i < spc->class; i++)
		class_count[i] = 0;
	
	/* 距離の小さい順にk個だけクラスラベルをカウントする */
	for(i = 0; i < knn->knum; i++)
		class_count[dat->label_tr[knn->index[i]]]++;
	
	/* 一番近いサンプルのクラスラベルを保存 */
	min_dist_class = dat->label_tr[knn->index[0]];

	/* カウントが最大のクラスラベルを出力。カウントが最大になるクラスが複
		 数出てきた場合の処理も含む */
	max_count = -1;
	for(i = 0; i < spc->class; i++){
		if((max_count < class_count[i]) ||
			 (max_count == class_count[i] && i == min_dist_class)){
			max_count = class_count[i];
			max_class = i;
		}
	}

	/* 配列を解放 */
	free_int_vector(class_count);

	return max_class;
}
