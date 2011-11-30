#include "k_nn_disc.h"

void
init_param(Spec *spc, Data *dat, KNN *knn)
{
	int i, j;
	int count = 0;

	/* 訓練サンプルのクラスラベルを初期化 */
	/* データは先頭から順に、クラス1、クラス2 ... と並んでいる */
	for(i = 0; i < spc->class; i++){
		for(j = 0; j < spc->tr_sample[i]; j++){
			dat->label_tr[count] = i;
			count++;
		}
	}

	/* テストサンプルのクラスラベルを初期化 */
	/* データの配置は訓練データと同様 */
	count = 0;
	for(i = 0; i < spc->class; i++){
		for(j = 0; j < spc->te_sample[i]; j++){
			dat->label_te[count] = i;
			count++;
		}
	}

	/* 識別結果を保存する配列を初期化 */
	for(i = 0; i< spc->class; i++)
		for(j = 0; j < spc->class; j++)
			knn->count[i][j] = 0;
}
