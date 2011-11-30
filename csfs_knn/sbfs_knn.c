#include "float_fs.h"

int main(int argc, char **argv)
{
	int          tmode, ans_fi, target, fold, knum;
	unsigned int seed;
	int          tflag = 0, eval_time = 0, skip_flag = 0;
	double       ans_value;
	Data         dat;
	FInfo        fs;

	/* 引数の読み込み */
	read_opt(argc, argv, &dat, &fs, SBFS, &tmode, &knum, &fold, &seed);
	
	/* 各分割におけるデータの個数を初期化 */
	dat.split_num = set_split(fold, dat.total);
	
	/* 配列の初期化 */
	alloc_prm(&dat, &fs);
	
	/* データの読み込み */
	read_data(&dat);

	/* 実験の初期化 */
	shuffle(&dat, seed);
	skip_flag = init_step(&dat, &fs, &eval_time, INITIAL, fold, knum, SBFS);
	
	if(!skip_flag){
		/* SBFS開始 */
		do{
			/* 
				 Backward Step: 
				 SBSで評価関数の値を最も少なく減少させる特徴を一つ削除する。
				 削除したらFoward Stepへ。 
			*/
			sbs(&dat, &fs, &ans_value, fold, &target, &eval_time, knum);
			ans_fi = target;
			
			/* 最も不要な特徴を除いた特徴集合を作成 */
			remove_one(&fs, target, ans_value);
			
			print_fs(&fs, eval_time, BACKWARD);
			
			/* tmodeモードの時は、最も評価関数の値が大きい特徴集合を保存する */
			if(tmode)
				eval_best(&fs);
			
			/* rej.num <= 2の時は以下の処理を飛ばす。但し、特徴数が1になった場
				 合には終了する */
			if(fs.rej.num <= 2){
				if(fs.sel.num == 1)
					break;
				else
					continue;
			}

			/* 
				 Forward Step: 
				 捨てられた特徴を追加し評価関数の値が増加すれば更に追加する。更新さ
				 れない場合にはBackward Stepへ。
			*/
			while(1){
				
				/* 選択されている特徴集合に捨てられた特徴を一つ追加する */
				check(&dat, &fs, &target, &ans_value, fold, &eval_time, SBFS, knum);
				
				/* 捨てた特徴を追加しても評価関数の値が増えない場合にはstep1へ */
				if(ans_value <= fs.C[fs.sel.num]){
					
					/* 指定された特徴数に達した場合には終了 */
					if(fs.sel.num == fs.ext_num){
						print_fs(&fs, eval_time, FINAL);
						tflag = 1;
					}
					break;
				}
				else{
					/* 追加した特徴集合を保存する */
					add_one(&fs, target, ans_value);
					
					print_fs(&fs, eval_time, FORWARD);

					/* tmodeモードの時は、最も評価関数の値が大きい特徴集合を保存する */
					if(tmode)
						eval_best(&fs);
					
					/* rej.num <= 2の時はforwardの処理を飛ばす */
					if(fs.rej.num <= 2)
						break;
				}
				
			}; /* forward step のループ */
			
		}while(!tflag); /* 全体のループ */
	}
	
	/* 選択した特徴集合を出力する */
	output(&fs, tmode, eval_time);
	
	/* 確保した配列を解放する */
	free_prm(&dat, &fs);
	
	exit(0);
}
