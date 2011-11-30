#include "float_fs.h"

int
get_min_index(double *dist, int *index, int num)
{
	int    i, ans = -1;
	double min = DBL_MAX;

	/* 距離が最小の要素を見つけ、それに対応するサンプルの番号を調べる */
	for(i = 0; i < num; i++){
		if(min > dist[i]){
			min = dist[i];
			ans = index[i];
		}
	}

	/* サンプルの番号が初期値の-1のままであればエラーなので終了 */
	if(ans < 0){
		fprintf(stderr, "\n[エラー] : 距離の最小値が見つかりません\n");
		exit(1);
	}

	return ans;
}

