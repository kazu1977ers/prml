#include "k_nn_disc.h"

int
read_opt(int argc, char **argv, Spec *spc, File *fil, KNN *knn)
{
	int tr_feat, te_feat;
	int tr_num, te_num;

	/* 引数が足りない時は使用法を出力して終了 */
	if(argc < 11){
		fprintf(stderr, "\n[使用法] : k_nn_disc <trfile> <tefile> [-c (num)] [-tr (n1)...(nC)] [-te (n1)...(nC)] (-k (num)) (-o / -tf)\n");
		exit(1);
	}

	/* ファイル名を取得 */
	strcpy(fil->trname, argv[1]);
	strcpy(fil->tename, argv[2]);

	/* 準備 */
	knn->knum = DEFAULT_KNUM;
	get_size(fil->trname, &tr_feat, &tr_num);
	get_size(fil->tename, &te_feat, &te_num);
	if(tr_feat != te_feat){
		fprintf(stderr, "\n[エラー] : 訓練データとテストデータの次元数が一致しません\n");
		exit(1);
	}
	spc->feature = tr_feat;
	spc->tr_total = tr_num;
	spc->te_total = te_num;

	/* 1回目 : クラス数だけを取り出し、他の引数の保存に必要な配列を確保 */
	spc->class = get_int_arg(argc, argv, "-c");

	/* 2回目 : 残りの引数を全て調べる */
	spc->tr_sample = get_int_list(argc, argv, "-tr", spc->class);
	spc->te_sample = get_int_list(argc, argv, "-te", spc->class);

	if(is_opt(argc, argv, "-k"))
		knn->knum = get_int_arg(argc, argv, "-k");
	
	if(knn->knum <= 0){
		fprintf(stderr, "\n[エラー] : kの値は1以上の整数に設定して下さい\n");
		exit(1);
	}

	if(is_opt(argc, argv, "-o"))
		return 1;
	else if(is_opt(argc, argv, "-tf"))
		return 2;
	else
		return 0;
}
