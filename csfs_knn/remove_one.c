#include "float_fs.h"

void remove_one(FInfo *fs, int target, double ans_value)
{
	int i;
	int count = 0;
	
	/* 元の特徴集合から target の特徴を抜いた特徴集合を作る */
	for(i = 0; i < fs->sel.num; i++){
		if(fs->sel.fi[i] != target){
			fs->sel.fi[count] = fs->sel.fi[i];
			count++;
		}
		else
			fs->rej.fi[fs->rej.num] = target;
	}
	
	fs->sel.num--;
	fs->rej.num++;
	fs->C[fs->sel.num - 1] = ans_value;

	/* 要素を小さい順に並び換える */
	fs->sel.fi = fs_sort(fs->sel.num, fs->sel.fi);
	fs->rej.fi = fs_sort(fs->rej.num, fs->rej.fi);
}
