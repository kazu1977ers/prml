#include "float_fs.h"

double
k_nn_disc(Data *dat, FInfo *fs, int fold, int knum)
{
	int     i, j, out_class;
	int     shift = 0;
	int     **count;
	DInfo   train, test;
	KInfo   knn;

	/* 識別結果を保存する配列 */
	count = new_int_matrix(dat->class, dat->class);
	for(i = 0; i < dat->class; i++)
		for(j = 0; j < dat->class; j++)
			count[i][j] = 0;
	
	/* k-nearest neighborで cross validation法により識別する */
	for(i = 0; i < fold; i++){
		
		/* 訓練データとテストデータに分ける */
		data_split(dat, shift, shift + dat->split_num[i], &train,
							 &test, &knn, fs);
		
		for(j = 0; j < test.size; j++){
			
			/* 距離を計算する */
			calc_dist(&train, &test, &knn, fs, j);
			
			/* 距離でソートし、小さい順にk個のラベルを調べる*/
			if(knum > 1){
				/* 距離の小さい順に並び換え */
				dist_sort(knn.dist, knn.index, 0, train.size-1);
				
				/* 多数決によりテストサンプルのクラスを判定 */
				out_class = find_class(dat->class, knum, &train, &knn);
			}
			else{
				/* 最小の値に対応する配列のindexを得て、それに対応するクラスラベル
					 を調べる */
				out_class = 
					train.label[get_min_index(knn.dist, knn.index, train.size)];
			}
			
			/* 識別結果をカウントする */
			count[test.label[j]][out_class]++;
		}

		/* 作業用の配列を解放 */
		free_double_vector(knn.dist);
		free_int_vector(knn.index);
		free_int_vector(train.label);
		free_int_vector(test.label);
		free_double_matrix(train.x);
		free_double_matrix(test.x);

		/* 次の分割セットを示す範囲の更新 */
		shift += dat->split_num[i];
	}

	/* 識別結果の集計し識別率を返す */
	shift = 0;
	for(i = 0; i < dat->class; i++)
		shift += count[i][i];

	/* 集計結果の配列を解放 */
	free_int_matrix(count);

	return (100.0 * (double)shift / (double)dat->total);
}
