#include "opt_utils.h"

char *get_char_arg(int argc, char **argv, char *opt_str)
{
	int i;
	char *arg;

	arg = new_char_vector(DEFAULT_LENGTH);
  for(i = 0; i < DEFAULT_LENGTH; i++)
    arg[i] = '\0';

	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
			strcpy(arg, argv[++i]);
      if(arg == NULL){
        fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
        exit(1);
      }
			break;
		}
	}

	return arg;
}

char **get_char_list(int argc, char **argv, char *opt_str, int arg_num)
{
	int i, j;
	char **arg;

	arg = new_char_matrix(arg_num, DEFAULT_LENGTH);
  for(i = 0; i < arg_num; i++)
    for(j = 0; j < DEFAULT_LENGTH; j++)
      arg[i][j] = '\0';

	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
			for(j = 0; j < arg_num; j++){
				strcpy(arg[j], argv[i+j+1]);
        if(arg[j] == NULL){
          fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
          exit(1);
        }
      }
			break;
		}
	}
	
	return arg;
}

int
get_int_arg(int argc, char **argv, char *opt_str)
{
	int i;
	int arg = 0;
	
	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
      if(argv[++i] == NULL){
        fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
        exit(1);
      }
      arg = atoi(argv[i]);
			break;
		}
	}

	return arg;
}

int *get_int_list(int argc, char **argv, char *opt_str, int arg_num)
{
	int i, j;
	int *arg;
	
	arg = new_int_vector(arg_num);
  for(i = 0; i < arg_num; i++)
    arg[i] = 0;
	
	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
			for(j = 0; j < arg_num; j++){
        if(argv[i+j+1] == NULL){
          fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
          exit(1);
        }
				arg[j] = atoi(argv[i+j+1]);
      }
			break;
		}
	}
	
	return arg;
}

int *get_int_arg_list(int argc, char **argv, char *opt_str, int *arg_num)
{
  int i, j;
  int *arg = NULL;

  for(i = 0; i < argc; i++){
    if(strcmp(opt_str, argv[i]) == 0){
      if(argv[++i] == NULL){
        fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした");
				exit(1);
      }
      *arg_num = atoi(argv[i]);
      arg = new_int_vector(*arg_num);

      for(j = 0; j < *arg_num; j++){
        if(argv[i+j+1] == NULL){
          fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
          exit(1);
        }
        arg[j] = atoi(argv[i+j+1]);
      }

      break;
    }
  }

  return arg;
}

double get_double_arg(int argc, char **argv, char *opt_str)
{
	int i;
	double arg = 0.0;

	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
      if(argv[++i] == NULL){
        fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
        exit(1);
      }
			arg = atof(argv[i]);
			break;
		}
	}

	return arg;
}

double *get_double_list(int argc, char **argv, char *opt_str, int arg_num)
{
	int i, j;
	double *arg;

	arg = new_double_vector(arg_num);
  for(i = 0; i < arg_num; i++)
    arg[i] = 0.0;
	
	for(i = 0; i < argc; i++){
		if(strcmp(opt_str, argv[i]) == 0){
			for(j = 0; j < arg_num; j++){
        if(argv[i+j+1] == NULL){
          fprintf(stderr, "\n[エラー] : 引数を読み取ることができませんでした\n");
          exit(1);
        }
				arg[j] = atof(argv[i+j+1]);
      }
			break;
		}
	}

	return arg;
}

int
is_opt(int argc, char **argv, char *opt_str)
{
	int i;
	
	for(i = 0; i < argc; i++){
		if(strcmp(argv[i], opt_str) == 0)
			return 1;
	}
	
	return 0;
}

int
num_opt(int argc, char **argv, char *opt_str)
{
	int i;
	int flag = 0;
	int count = 0;

	for(i = 0; i < argc; i++){
		if(flag){
			if(argv[i][0] == '-')
				break;
			else
				count++;
		}

		if(strcmp(argv[i], opt_str) == 0)
			flag = 1;
	}

	return count;
}
