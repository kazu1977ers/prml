#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "pattern.h"

#define  NAME_LEN  31

void quicksort(int *index, int first, int last);

int main(int argc, char **argv)
{
  int     i;
  int     dim, line;
  int     dflag = 0;
  double  extract;
  int    *index, *fi;
  double *item, max;
  FILE   *fp;

  if(argc != 4){
    fprintf(stderr, "\n[使用法] : detect_fi <file> [-d (num) / -r (ratio)]\n");
    exit(1);
  }
  
  /* 取り出す要素数の方法を引数から確認 */
  if(is_opt(argc, argv, "-d")){
    dflag = 1;
    extract = get_double_arg(argc, argv, "-d");
  }
  else if(is_opt(argc, argv, "-r"))
    extract = get_double_arg(argc, argv, "-r");
  else{
    fprintf(stderr, "\n[エラー] : 不明な引数が含まれています\n");
    exit(1);
  }

  /* データの大きさを調べる */
  get_size(argv[1], &dim, &line);
  
  /* 準備 */
  index = new_int_vector(line);
  item  = new_double_vector(line);

  /* データを読み込む */
  if((fp = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
    exit(1);
  }
  for(i = 0; i < line; i++)
    fscanf(fp, "%d %lf", &index[i], &item[i]);

  fclose(fp);

  /* 要素数を決定し、結果を出力 */
  if(dflag){

    dim = (int)extract;
		fi = new_int_vector(dim);

    for(i = 0; i < dim; i++)
			fi[i] = index[i];

    if(dim > 1)
      quicksort(fi, 0, dim - 1);
    
    if((fp = fopen("Subset.dat", "w")) == NULL){
      fprintf(stderr, "\n[エラー] : ファイル Subset.dat が開けません\n");
      exit(1);
    }
    for(i = 0; i < dim; i++){
      fprintf(fp, "%d", fi[i]);
      if(i < dim - 1)
        fprintf(fp, " ");
    }
    fprintf(fp, "\n");
    fclose(fp);
		
  }
  else{
		/* 評価関数の最大値を判定する */
		max = item[line - 1];

		extract = max * (1.0 - extract / 100.0);
    for(i = 0; i < line; i++){
      if(item[i] - extract > 0.0){
        dim = i;
        break;
      }
    }
		dim++;  /* 特徴の番号を合わせる. C言語では0番から始まるけど、特徴は1
							 番からカウントするのでfor文を抜けた後のdimは特徴数が1だけ
							 小さい。 */

		fi = new_int_vector(dim);
    for(i = 0; i < dim; i++)
			fi[i] = index[i];
		
    if(dim > 1)
      quicksort(fi, 0, dim - 1);

    if((fp = fopen("Subset.dat", "w")) == NULL){
      fprintf(stderr, "\n[エラー] : ファイル Subset.dat が開けません\n");
      exit(1);
    }
    for(i = 0; i < dim; i++){
      fprintf(fp, "%d", fi[i]);
      if(i < dim - 1)
        fprintf(fp, " ");
    }
    fprintf(fp, "\n");
    fclose(fp);
    
  }
  
  /* 終了処理 */
  free_int_vector(index);
  free_double_vector(item);
	free_int_vector(fi);
  
  exit(0);
}

void quicksort(int *index, int first, int last)
{
	int i, j;
	int x, t;
  
	x = index[(first + last) / 2];
	i = first;  
  j = last;

	while (1) {

		while (index[i] < x) 
      i++;
		while (x < index[j]) 
      j--;

		if (i >= j) 
      break;

		t = index[i];  index[i] = index[j];  index[j] = t;
		i++;  j--;

	}

	if (first  < i - 1) 
    quicksort(index, first , i - 1);
	if (j + 1 < last) 
    quicksort(index, j + 1, last);
}
