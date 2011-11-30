#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

#define  NAME_LEN  31

void quicksort(double *item, int *index, int first, int last);

int main(int argc, char **argv)
{
  int     i;
  int     dim, line;
  int    *index;
  double *item, sum = 0.0;
  char    ofname[NAME_LEN];
  FILE   *fp;

  if(argc != 2){
    fprintf(stderr, "\n[使用法] : rank_fi <file>\n");
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

  /* itemの値に関して小さい順に並び換える */
  quicksort(item, index, 0, line-1);

  /* 並び換えた結果を出力 */
  sprintf(ofname, "%s.sort", argv[1]);
  if((fp = fopen(ofname, "w")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", ofname);
    exit(1);
  }
  for(i = line - 1; i >= 0; i--)
    fprintf(fp, "%3d\t%.12g\n", index[i], item[i]);
	
  fclose(fp);

  /* 値を先頭から順番に足した結果を出力 */
  sprintf(ofname, "%s.sum", argv[1]);
  if((fp = fopen(ofname, "w")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", ofname);
    exit(1);
  }
  for(i = line - 1; i >= 0; i--){
    sum += item[i];
    fprintf(fp, "%3d\t%.12g\n", index[i], sum);
  }

  fclose(fp);

  /* 終了処理 */
  free_int_vector(index);
  free_double_vector(item);

  exit(0);
}

void quicksort(double *item, int *index, int first, int last)
{
	int i, j, u;
	double x, t;
  
	x = item[(first + last) / 2];
	i = first;  
  j = last;

	while (1) {

		while (item[i] < x) 
      i++;
		while (x < item[j]) 
      j--;

		if (i >= j) 
      break;

		t = item[i];  item[i] = item[j];  item[j] = t;
    u = index[i]; index[i] = index[j]; index[j] = u;
		i++;  j--;

	}

	if (first  < i - 1) 
    quicksort(item, index, first , i - 1);
	if (j + 1 < last) 
    quicksort(item, index, j + 1, last);
}
