#include "float_fs.h"

void
check(Data *dat, FInfo *fs, int *target, double *ans_value, int fold,
			int *eval_time, int method,	int knum)
{
	int i, j;
	int count = 0;
	double crite_value;
	
	if(method == SBFS){
		
		/* 削除した特徴を一つ追加し、最も識別に寄与する特徴を判定する */
		*ans_value = -DBL_MAX;
		for(i = 0; i < fs->rej.num; i++){
			
			/* 新しい特徴集合のリストを作る */
			count = 0;
			for(j = 0; j < fs->sel.num; j++){
				fs->cur.fi[count] = fs->sel.fi[j];
				count++;
			}
			
			fs->cur.fi[count] = fs->rej.fi[i];
			fs->cur.num = fs->sel.num + 1;
			
			/* 作成した特徴集合を用いて識別する */
			crite_value = k_nn_disc(dat, fs, fold, knum);
			
			/* 記録を更新する */
			if(*ans_value < crite_value){
				*ans_value = crite_value;
				*target = fs->rej.fi[i];
			}
			
		}
		
		*eval_time += fs->rej.num;
	}
	else{

		/* 選択した特徴から一つ削除し、最も識別に寄与しない特徴を判定する */
		*ans_value = -DBL_MAX;
		for(i = 0; i < fs->sel.num; i++){

			/* 新しい特徴集合のリストを作る */
			count = 0;
			for(j = 0; j < fs->sel.num; j++){
				if(i != j){
					fs->cur.fi[count] = fs->sel.fi[j];
					count++;
				}
			}
			fs->cur.num = fs->sel.num - 1;
			
			/* 作成した特徴集合を用いて識別する */
			crite_value = k_nn_disc(dat, fs, fold, knum);

			/* 記録を更新する */
			if(*ans_value < crite_value){
				*ans_value = crite_value;
				*target = fs->sel.fi[i];
			}
			
		}
		
		*eval_time += fs->sel.num;
	}
}
