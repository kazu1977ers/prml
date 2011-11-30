#include "k_nn_disc.h"

void
free_param(Spec *spc, Data *dat, KNN *knn)
{
	/* 配列の解放 */
	free_int_vector(spc->tr_sample);
	free_int_vector(spc->te_sample);

	free_double_matrix(dat->x_tr);
	free_double_matrix(dat->x_te);
	free_int_vector(dat->label_tr);
	free_int_vector(dat->label_te);

	free_double_vector(knn->dist_queue);
	free_int_vector(knn->index);

	free_int_matrix(knn->count);
}
