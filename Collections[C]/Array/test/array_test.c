#include "../Array/array.h"
#include <stdlib.h>

int main()
{
	array* ar;
	array_new(&ar);

	size_t i;
	long* num;
	long* out;
	for (i = 0; i < 10; i++)
	{
		num = (long*)malloc(sizeof(long));
		*num = i * i;
		array_add(ar, num);
	}

	/*
	array_remove_at(ar, 1, &out);
	printf("the removed elem is %ld\n", *out);
	array_remove_last(ar, &out);
	printf("the removed elem is %ld\n", *out);
	*/

	array_get_at(ar, 5, &out);
	printf("the 5th elem is %ld\n", *out);

	array_get_last(ar, &out);
	printf("the last elem is %ld\n", *out);

	array_iter iter;
	array_iter_init(&iter, ar);
	while (array_iter_next(&iter,&out) != ITER_END)
	{
		printf("ar->elements[%u] = [%ld]\n", iter.index, *out);
	}

	array* subar;
	array_subarray_cb(ar, 1, 6, &subar);
	for (i = 0; i < subar->size; i++)
	{
		printf("subarray's elements[%d]=[%ld]\n", i, *(long*)(subar->elements[i]));
	}
	
	array_destroy_cb(&subar);
	array_destroy_cb(&ar);
	return 0;
}