#include "k_nn_disc.h"

void 
alloc_param(Spec *spc, Data *dat, KNN *knn)
{
	/* データを保存する配列 */
	dat->x_tr = new_double_matrix(spc->tr_total, spc->feature);
	dat->x_te = new_double_matrix(spc->te_total, spc->feature);

	/* クラスラベルを保存する配列 */
	dat->label_tr = new_int_vector(spc->tr_total);
	dat->label_te = new_int_vector(spc->te_total);

	/* 距離を保存する配列 */
	knn->dist_queue = new_double_vector(spc->tr_total);
	knn->index = new_int_vector(spc->tr_total);
	
	/* 識別結果を保存する配列 */
	knn->count = new_int_matrix(spc->class, spc->class);
}
