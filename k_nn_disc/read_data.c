#include "k_nn_disc.h"

void
read_data(Spec *spc, File *fil, Data *dat)
{
	int i, j;
	FILE *fp;

	/* 訓練サンプルの読み込み */
	if((fp = fopen(fil->trname, "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", fil->trname);
		exit(3);
	}
	for(i = 0; i < spc->tr_total; i++)
		for(j = 0; j < spc->feature; j++)
			fscanf(fp, "%lf", &dat->x_tr[i][j]);
	
	fclose(fp);
	
	/* テストサンプルの読み込み */
	if((fp = fopen(fil->tename, "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", fil->tename);
		exit(3);
	}
	for(i = 0; i < spc->te_total; i++)
		for(j = 0; j < spc->feature; j++)
			fscanf(fp, "%lf", &dat->x_te[i][j]);
	
	fclose(fp);
}
