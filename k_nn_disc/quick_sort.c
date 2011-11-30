#include "k_nn_disc.h"

/* 距離に応じて要素を入れ換えるクイックソート */
/* C言語アルゴリズム辞典より引用したものを変更 */
void
quick_sort(double dist[], int index[], int first, int last)
{
	int i, j, tmp;
	double x, t;

	x = dist[(first + last) / 2];
	i = first;
	j = last;

	for ( ; ; ) {
		while (dist[i] < x) 
			i++;
		while (x < dist[j]) 
			j--;

		if (i >= j) 
			break;

		/* 要素を入れ換え。ついでに訓練サンプルの番号の情報も入れ換える。 */
		t = dist[i];       /* 距離の入れ換え */
		dist[i] = dist[j];  
		dist[j] = t;

		tmp = index[i];    /* indexの入れ換え */
		index[i] = index[j];
		index[j] = tmp;

		i++;  
		j--;
	}

	if (first < i - 1) 
		quick_sort(dist, index, first , i - 1);

	if (j + 1 < last)
		quick_sort(dist, index, j + 1, last);
}
