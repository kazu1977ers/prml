#include "float_fs.h"

void
alloc_prm(Data *dat, FInfo *fs)
{
	/* クラスラベル */
	dat->label = new_int_vector(dat->total);

	/* 訓練データ */
	dat->sample = new_double_matrix(dat->total, dat->dim);

	/* 現在使用している特徴集合 */
	fs->cur.fi = new_int_vector(dat->dim);

	/* 選択されていない特徴集合 */
	fs->rej.fi = new_int_vector(dat->dim);

	/* 選択している特徴集合 */
	fs->sel.fi = new_int_vector(dat->dim);

	/* traceモード用。最も良い特徴集合 */
	fs->best.fi = new_int_vector(dat->dim);

	/* 各特徴数における評価関数の値 */
	fs->C = new_double_vector(dat->dim);
}
