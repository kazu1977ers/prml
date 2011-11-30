#include "ary_utils.h"

/* char型の配列管理 */
char *alloc_char_vector(int n)
{
	char *v = NULL;
	
	v = malloc(sizeof(char) * n);
	if(v == NULL)	//確保に失敗したときは NULL を返す
		return NULL;
	
	return v;
}

char *new_char_vector(int n)
{
	char *v = NULL;
	
	v = alloc_char_vector(n);
	
	return v;
}

void free_char_vector(char *v)
{
	free(v);
}

char **alloc_char_matrix(int nrow, int ncol)
{
	int i;
	char **a = NULL;
	
	a = malloc((nrow + 1) * sizeof(void *));
	if(a == NULL) // 確保に失敗したときは NULL を返す
		return NULL;
	
	for(i = 0; i < nrow; i++){
		a[i] = malloc(sizeof(char) * ncol);
		if(a[i] == NULL){ // 確保に失敗したときは解放した後で NULL を返す
			while(--i >= 0) 
				free(a[i]);
			free(a);
			return NULL;  
		}
	}
	
	a[nrow] = NULL;
	return a;
}

char **new_char_matrix(int nrow, int ncol)
{
	char **a = NULL;
	
	a = alloc_char_matrix(nrow, ncol);
	
	return a;
}

void free_char_matrix(char **a)
{
	char **b;

	b = a;
	while (*b != NULL) 
		free(*b++);
	free(a);
}

/* int型の配列管理 */
int *alloc_int_vector(int n)
{
	int *v = NULL;
	
	v = malloc(sizeof(int) * n);
	if(v == NULL)	//確保に失敗したときは NULL を返す
		return NULL;
	
	return v;
}

int *new_int_vector(int n)
{
	int *v = NULL;
	
	v = alloc_int_vector(n);
	
	return v;
}

void free_int_vector(int *v)
{
	free(v);
}

int **alloc_int_matrix(int nrow, int ncol)
{
	int i;
	int **a = NULL;
	
	a = malloc((nrow + 1) * sizeof(void *));
	if(a == NULL) // 確保に失敗したときは NULL を返す
		return NULL;
	
	for(i = 0; i < nrow; i++){
		a[i] = malloc(sizeof(int) * ncol);
		if(a[i] == NULL){ // 確保に失敗したときは解放した後で NULL を返す
			while(--i >= 0) 
				free(a[i]);
			free(a);
			return NULL;  
		}
	}
	
	a[nrow] = NULL;
	return a;
}

int **new_int_matrix(int nrow, int ncol)
{
	int **a = NULL;
	
	a = alloc_int_matrix(nrow, ncol);
	
	return a;
}

void free_int_matrix(int **a)
{
	int **b;

	b = a;
	while (*b != NULL) 
		free(*b++);
	free(a);
}

/* float型の配列管理 */
float *alloc_float_vector(int n)
{
	float *v = NULL;
	
	v = malloc(sizeof(float) * n);
	if(v == NULL)	//確保に失敗したときは NULL を返す
		return NULL;
	
	return v;
}

float *new_float_vector(int n)
{
	float *v = NULL;
	
	v = alloc_float_vector(n);
	
	return v;
}

void free_float_vector(float *v)
{
	free(v);
}

float **alloc_float_matrix(int nrow, int ncol)
{
	int i;
	float **a = NULL;
	
	a = malloc((nrow + 1) * sizeof(void *));
	if(a == NULL) // 確保に失敗したときは NULL を返す
		return NULL;
	
	for(i = 0; i < nrow; i++){
		a[i] = malloc(sizeof(float) * ncol);
		if(a[i] == NULL){ // 確保に失敗したときは解放した後で NULL を返す
			while(--i >= 0) 
				free(a[i]);
			free(a);
			return NULL;  
		}
	}
	
	a[nrow] = NULL;
	return a;
}

float **new_float_matrix(int nrow, int ncol)
{
	float **a = NULL;
	
	a = alloc_float_matrix(nrow, ncol);
	
	return a;
}

void free_float_matrix(float **a)
{
	float **b;

	b = a;
	while (*b != NULL) 
		free(*b++);
	free(a);
}

/* double型の配列管理 */
double *alloc_double_vector(int n)
{
	double *v = NULL;
	
	v = malloc(sizeof(double) * n);
	if(v == NULL)	//確保に失敗したときは NULL を返す
		return NULL;
	
	return v;
}

double *new_double_vector(int n)
{
	double *v = NULL;
	
	v = alloc_double_vector(n);
	
	return v;
}

void free_double_vector(double *v)
{
	free(v);
}

double **alloc_double_matrix(int nrow, int ncol)
{
	int i;
	double **a = NULL;
	
	a = malloc((nrow + 1) * sizeof(void *));
	if(a == NULL) // 確保に失敗したときは NULL を返す
		return NULL;
	
	for(i = 0; i < nrow; i++){
		a[i] = malloc(sizeof(double) * ncol);
		if(a[i] == NULL){ // 確保に失敗したときは解放した後で NULL を返す
			while(--i >= 0) 
				free(a[i]);
			free(a);
			return NULL;  
		}
	}
	
	a[nrow] = NULL;
	return a;
}

double **new_double_matrix(int nrow, int ncol)
{
	double **a = NULL;
	
	a = alloc_double_matrix(nrow, ncol);
	
	return a;
}

void free_double_matrix(double **a)
{
	double **b;

	b = a;
	while (*b != NULL) 
		free(*b++);
	free(a);
}
