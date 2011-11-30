#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "pattern.h"

#define  NAME_LEN   30

int main(int argc, char **argv)
{
  int          i, j;
  int          line, dim, max_byte;
  char         **buffer, *temp;
  unsigned int seed = (unsigned)time(NULL) / 2 + getpid();
  FILE         *fp = NULL;

  /* 引数の確認 */
  if(argc < 2){
    fprintf(stderr, "\n[使用法] : shuffle <file> (-s (num))\n");
    exit(1);
  }

  if(is_opt(argc, argv, "-s")){
    seed = (unsigned)get_int_arg(argc, argv, "-s");
  }
  srand(seed);

  /* 1行当たりのバイト数の最大値とデータの行の総数を調べる */
  get_max_byte(argv[1], &max_byte);
  get_size(argv[1], &dim, &line);
  
  /* データを確保するための配列を準備する */
  buffer = new_char_matrix(line, sizeof(char)*(max_byte + 2));
  temp   = new_char_vector(sizeof(char)*(max_byte + 2));

  for(i = 0; i < line; i++)
    for(j = 0; j <= sizeof(char)*max_byte + 1; j++)
      buffer[i][j] = '\0';

  /* ファイルからデータを読み込む */
  if((fp = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
    exit(1);
  }

  for(i = 0; i < line; i++){
    for(j = 0; j <= max_byte*sizeof(char); j++){
      fscanf(fp, "%c", &buffer[i][j]);
      if(buffer[i][j] == '\n')
        break;
    }
  }

  fclose(fp);

  /* データを並び換える */
  for(i = line - 1; i >= 0; i--){
		j = rand() % line;
    strcpy(temp, buffer[i]);
    strcpy(buffer[i], buffer[j]);
    strcpy(buffer[j], temp);
  }

  /* 標準出力に結果を吐く */
  for(i = 0; i < line; i++){
    for(j = 0; j <= max_byte*sizeof(char); j++){
      fprintf(stdout, "%c", buffer[i][j]);
      if(buffer[i][j] == '\n')
        break;
    }
  }

  /* 作業用の配列を解放 */
  free_char_matrix(buffer);
  free_char_vector(temp);

  exit(0);
}
