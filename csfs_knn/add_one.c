#include "float_fs.h"

void
add_one(FInfo *fs, int target, double ans_value)
{
	int count = 0;
	int i;

	/* targetの特徴を一つ追加する */
	fs->sel.fi[fs->sel.num] = target;
	fs->sel.num++;
	fs->C[fs->sel.num - 1] = ans_value;
	
	/* ゴミ特徴の要素を一つ減らす */
	count = 0;
	for(i = 0; i < fs->rej.num; i++){
		if(fs->rej.fi[i] != target){
			fs->rej.fi[count] = fs->rej.fi[i];
			count++;
		}
	}
	fs->rej.num--;

	/* 要素を小さい順に並び換える */
	fs->sel.fi = fs_sort(fs->sel.num, fs->sel.fi);
	fs->rej.fi = fs_sort(fs->rej.num, fs->rej.fi);
}
