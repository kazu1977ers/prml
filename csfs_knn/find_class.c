#include "float_fs.h"

int
find_class(int class, int knum, DInfo *train, KInfo *knn)
{
	int i;
	int max_class = 0, max_count;
	int *class_count;
	
	/* 準備 */
	class_count = new_int_vector(class);
	for(i = 0; i < class; i++)
		class_count[i] = 0;
	
	/* 距離の小さい順にk個だけクラスラベルをカウントする */
	for(i = 0; i < knum; i++)
		class_count[train->label[knn->index[i]]]++;
	
	/* カウントが最大のクラスラベルを出力 */
	max_count = 0;
	for(i = 0; i < class; i++){
		if(max_count < class_count[i]){
			max_count = class_count[i];
			max_class = i;
		}
	}

	/* 配列を解放 */
	free_int_vector(class_count);

	return max_class;
}
