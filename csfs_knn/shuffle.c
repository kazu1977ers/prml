#include "float_fs.h"

void 
shuffle(Data *dat, unsigned int seed)
{
	int     i, j, k;
	int     temp_label;
	double *temp_data;

	temp_data = new_double_vector(dat->dim);
	srand(seed);

	for(i = dat->total - 1; i >= 0; i--){

		/* 入れ換え先を決定する */
		k = rand() % dat->total;
		
		for(j = 0; j < dat->dim; j++){
			temp_data[j] = dat->sample[i][j];
			dat->sample[i][j] = dat->sample[k][j];
			dat->sample[k][j] = temp_data[j];
		}

		temp_label = dat->label[i];
		dat->label[i] = dat->label[k];
		dat->label[k] = temp_label;
	}

	free_double_vector(temp_data);
}
