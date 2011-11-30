#include "float_fs.h"

void 
eval_best(FInfo *fs)
{
	int i;
	
	/* 識別率が向上した、または同じ識別率で特徴が少ない場合には更新 */
	if(
		 (fs->C[fs->sel.num-1] > fs->best_rate) || 
		 ((fs->best.num > fs->sel.num) && (fs->C[fs->sel.num-1] == fs->best_rate))
		 ){
		
		fs->best.num = fs->sel.num;
		fs->best_rate = fs->C[fs->sel.num - 1];
		
		for(i = 0; i < fs->best.num; i++)
			fs->best.fi[i] = fs->sel.fi[i];
	}

}
