#include "k_nn_disc.h"

int 
main(int argc, char **argv)
{
	int       i, oflag = 0, out_class;
	Spec      spc;
	File      fil;
	Data      dat;
	KNN       knn;

	/* 引数の確認 */
	oflag = read_opt(argc, argv, &spc, &fil, &knn);
	
	/* 配列の確保 */
	alloc_param(&spc, &dat, &knn);

	/* パラメータの初期化 */
	init_param(&spc, &dat, &knn);

	/* データの読み込み */
	read_data(&spc, &fil, &dat);

	/* テストサンプルの識別 */
	fprintf(stderr, "Classification rule is %d-nearest neighbour.\n",
					knn.knum);
	
	for(i = 0; i < spc.te_total; i++){
		
		/* 距離を計算する */
		calc_dist(&spc, &dat, &knn, i);
		
		/* 距離の小さい順に並び換え */
		quick_sort(knn.dist_queue, knn.index, 0, spc.tr_total - 1);
		
		/* 多数決によりテストサンプルのクラスを判定 */
		out_class = disc(&spc, &dat, &knn);
		if(oflag == 1)
			fprintf(stderr, "OUT %d\n", out_class);
		else if(oflag == 2){
			if(out_class == dat.label_te[i])
				fprintf(stderr, "TF  %d\n", TRUE);
			else
				fprintf(stderr, "TF  %d\n", FALSE);
		}
		
		/* 識別結果をカウントする */
		knn.count[dat.label_te[i]][out_class]++;
	}

	/* 識別結果の出力 */
	output(&spc, &knn);

	/* 配列の解放 */
	free_param(&spc, &dat, &knn);

	exit(0);
}
