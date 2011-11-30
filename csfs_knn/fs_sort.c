#include "float_fs.h"

int
*fs_sort(int num, int *list)
{
	int i, j;
	int min, index = 0, tmp;

	/* 小さい順に並び換え、並び換えたリストを返す */
	for(i = 0; i < num - 1; i++){

		min = INT_MAX;
		for(j = i; j < num ; j++)
			if(list[j] < min){
				min = list[j];
				index = j;
			}
		
		tmp = list[i];
		list[i] = min;
		list[index] = tmp;
	}

	return list;
}

