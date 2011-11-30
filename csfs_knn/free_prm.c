#include "float_fs.h"

void
free_prm(Data *dat, FInfo *fs)
{
	/* 訓練サンプル数 */
	free_int_vector(dat->trnum);
	
	/* クラスラベル */
	free_int_vector(dat->label);
	
	/* 各分割におけるデータの個数を初期化 */
	free_int_vector(dat->split_num);
	
	/* 訓練データ */
	free_double_matrix(dat->sample);
	
	/* 現在使用している特徴集合 */
	free_int_vector(fs->cur.fi);
	
	/* 選択されていない特徴集合 */
	free_int_vector(fs->rej.fi);
	
	/* 選択している特徴集合 */
	free_int_vector(fs->sel.fi);
	
	/* traceモード用。最も良い特徴集合 */
	free_int_vector(fs->best.fi);
	
	/* 各特徴数における評価関数の値 */
	free_double_vector(fs->C);
}
