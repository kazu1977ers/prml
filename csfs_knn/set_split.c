#include "float_fs.h"

int
*set_split(int fold, int total)
{
	int i, *temp;
	
	temp = new_int_vector(fold);
	
	for(i = 0; i < fold; i++)
		temp[i] = total / fold;
	
	for(i = 0; i < total - ((total / fold) * fold); i++)
		temp[i]++;

	return temp;
}
