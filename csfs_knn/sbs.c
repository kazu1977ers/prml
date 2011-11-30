#include "float_fs.h"

void sbs(Data *dat, FInfo *fs, double *ans_value, int fold, int *target,
				 int *eval_time, int knum)
{
	int i, j;
	int count;
	double crite_value;
	
	/* 初期化 */
	*ans_value = -DBL_MAX;
	*target = -1;
	fs->cur.num = fs->sel.num - 1;
	
	/* SBS開始 */
	for(i = 0; i < fs->sel.num; i++){
		
		/* i番目の特徴を一つ抜いたリストを作る */
		count = 0;
		for(j = 0; j < fs->sel.num; j++)
			if(i != j){
				fs->cur.fi[count] = fs->sel.fi[j];
				count++;
			}
		
		/* k近隣で識別を行う */
		crite_value = k_nn_disc(dat, fs, fold, knum);

		/* 識別率を更新する */
		if(*ans_value < crite_value){
			*ans_value = crite_value;
			*target = fs->sel.fi[i];
		}
		
	} /* for文の終り */

	*eval_time += fs->sel.num;
}
