#include "float_fs.h"

void sfs(Data *dat, FInfo *fs, double *ans_value, int fold, int *target,
				 int *eval_time, int knum)
{
	int i, j;
	double crite_value;
	
	/* 初期化 */
	*ans_value = -DBL_MAX;
	*target = -1;
	fs->cur.num = fs->sel.num + 1;

	/* SFS開始 */
	for(i = 0; i < fs->rej.num; i++){

		/* i番目の特徴を一つ追加したリストを作る */
		for(j = 0; j < fs->sel.num; j++)
			fs->cur.fi[j] = fs->sel.fi[j];
		fs->cur.fi[fs->sel.num] = fs->rej.fi[i];

		/* k近隣で識別を行う */
		crite_value = k_nn_disc(dat, fs, fold, knum);		

		/* 識別率を更新する */
		if(*ans_value < crite_value){
			*ans_value = crite_value;
			*target = fs->rej.fi[i];
		}

	} /* for文の終り */

	*eval_time += fs->rej.num;
}
