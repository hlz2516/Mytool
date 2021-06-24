#include "array.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY						8
#define DEFAULT_EXPANSION_FACTOR		2.0
#define DEFAULT_SHRINK_FACTOR				0.5

enum stat		expand_capacity(array* ar);

void	array_conf_init(array_conf* conf)
{
	conf->capacity = DEFAULT_CAPACITY;
	conf->exp_factor = DEFAULT_EXPANSION_FACTOR;
}

enum stat array_new_conf(array** out, array_conf* conf)
{
	float ex,shr;
	if (conf->exp_factor <= 1.00)
		ex = 1.00;
	else
		ex = conf->exp_factor;

	if (!conf->capacity || ex >= MAX_ELEMENTS / conf->capacity)
		return ERR_INVALID_CAPACITY;

	array* ar;
	ar = (array*)malloc(sizeof(array));
	if (!ar)	return ERR_ALLOC;
	memset(ar, 0, sizeof(array));

	void** buf;
	buf = (void**)malloc(conf->capacity*sizeof(void*));
	if (!buf)
	{
		free(ar);
		return ERR_ALLOC;
	}
	memset(buf, 0, conf->capacity * sizeof(void*));

	ar->capacity = conf->capacity;
	ar->size = 0;
	ar->exp_factor = ex;
	ar->elements = buf;
	*out = ar;
	return OK;
}

enum stat	array_new(array** out)
{
	array_conf conf;
	array_conf_init(&conf);
	return array_new_conf(out, &conf);
}
/*
	如果你的每个元素均在栈上分配，调用此方法
*/
void	array_destroy(array** ar)
{
	if (!*ar) return;
	free((*ar)->elements);
	(*ar)->elements = NULL;
	free(*ar);
	*ar = NULL;
}
/*
	如果你的每个元素均在堆上分配，调用此方法
*/
void	array_destroy_cb(array** ar)
{
	if (!*ar) return;
	size_t		i;
	for (i = 0; i < (*ar)->size; i++)
		free((*ar)->elements[i]);
	array_destroy(ar);
	printf("array has free!\n");
}

enum stat	 expand_capacity(array* ar)
{
	if (ar->capacity >= MAX_ELEMENTS - 1)
		return ERR_MAX_CAPACITY;
	float new_capacity = ar->capacity * (ar->exp_factor);
	void** buf = (void**)calloc((unsigned int)new_capacity,sizeof(void*));
	if (!buf)	return ERR_ALLOC;
	memcpy(buf, ar->elements, ar->size * sizeof(void*));
	free(ar->elements);
	ar->elements = buf;
	return OK;
}
/*
	默认在array末尾位置添加一个元素
*/
enum stat	 array_add(array* ar, void* elem)
{
	if (ar->size >= ar->capacity - 1)
	{
		enum stat stats = expand_capacity(ar);
		if (stats != OK)
			return stats;
	}

	ar->elements[ar->size++] = elem;
	return OK;
}

enum stat	 array_add_at(array* ar, void* elem, size_t index)
{
	if (index == ar->size)
		return array_add(ar, elem);
	if ((ar->size == 0 && index != 0) || index > ar->size)
		return ERR_OUT_OF_RANGE;
	if (ar->size >= ar->capacity)
	{
		enum stat stats = expand_capacity(ar);
		if (stats != OK)	return stats;
	}
	size_t shift = (ar->size - index) * sizeof(void*);
	memmove(&(ar->elements[index + 1]),
		&(ar->elements[index]),
		shift);
	ar->elements[index] = elem;
	ar->size++;
	return OK;
}

enum stat	 array_index_of(array* ar, void* element, size_t* index)
{
	size_t i;
	for (i = 0; i < ar->size; i++)
	{
		if (ar->elements[i] == element)
		{
			*index = i;
			return OK;
		}
	}
	return ERR_INVALID_RANGE;
}
/*
	若删除的元素是堆上分配，记得利用传出的out参数手动释放元素，类似的删除方法同理
*/
enum stat array_remove(array* ar, void* elem, void** out)
{
	size_t index;
	enum stat stats = array_index_of(ar, elem, &index);
	if (stats == ERR_INVALID_RANGE)
		return ERR_VALUE_NOT_FOUND;

	if (index == ar->size - 1)
	{
		size_t block_size = (ar->size - index - 1) * sizeof(void*);
		memmove(&(ar->elements[index]),
			&(ar->elements[index + 1]),
			block_size);
	}
	ar->size--;
	if (out)
		*out = elem;
	return OK;
}

enum stat array_remove_at(array* ar, size_t index, void** out)
{
	if (index >= ar->size)
		return ERR_OUT_OF_RANGE;

	if (out)
		*out = ar->elements[index];

	if (index != ar->size - 1) {
		size_t block_size = (ar->size - 1 - index) * sizeof(void*);

		memmove(&(ar->elements[index]),
			&(ar->elements[index + 1]),
			block_size);
	}
	ar->size--;

	return OK;
}

enum stat array_remove_last(array* ar, void** out)
{
	return array_remove_at(ar, ar->size - 1, out);
}
/*
	如果你的每个元素均是从栈上分配，调用此方法
*/
void	array_remove_all(array* ar)
{
	ar->size = 0;
}

void array_remove_all_cb(array* ar)
{
	size_t i;
	for (i = 0; i < ar->size; i++)
		free(ar->elements[i]);
	ar->size = 0;
}

enum stat array_get_at(array* ar, size_t index, void** out)
{
	if (index >= ar->size)
		return ERR_OUT_OF_RANGE;

	*out = ar->elements[index];
	return OK;
}

enum stat array_get_last(array* ar, void** out)
{
	if (ar->size == 0)
		return ERR_VALUE_NOT_FOUND;

	return array_get_at(ar, ar->size - 1, out);
}

/*
	从源数组ar中拷贝起始下标为b的元素到结束下标为e的元素，到新的子数组out中
*/
enum stat	 array_subarray(array* ar, size_t b, size_t e, array** out)
{
	if (b > e || e >= ar->size)
		return ERR_INVALID_RANGE;

	array* sub_ar = calloc(1, sizeof(array));

	if (!sub_ar)
		return ERR_ALLOC;

	size_t sub_size = e - b + 1;
	size_t sub_capacity = sub_size * 2;

	/* Try to allocate the buffer */
	if (!(sub_ar->elements = malloc(sub_capacity * sizeof(void*)))) {
		free(sub_ar);
		return ERR_ALLOC;
	}

	sub_ar->capacity = sub_capacity;
	sub_ar->size = sub_size;
	memset(sub_ar->elements, 0, sub_capacity * sizeof(void*));
	memcpy(sub_ar->elements,
		&(ar->elements[b]),
		sub_ar->size * sizeof(void*));

	*out = sub_ar;
	return OK;
}
/*
	与array_subarray相同的功能，但考虑到元素从堆上分配内存所以拷贝elements时采用深拷贝
*/
enum stat	 array_subarray_cb(array* ar, size_t b, size_t e, array** out)
{
	if (b > e || e >= ar->size)
		return ERR_INVALID_RANGE;

	array* sub_ar = calloc(1, sizeof(array));

	if (!sub_ar)
		return ERR_ALLOC;

	size_t sub_size = e - b + 1;
	size_t sub_capacity = sub_size * 2;

	if (!(sub_ar->elements = malloc(sub_capacity * sizeof(void*)))) {
		free(sub_ar);
		return ERR_ALLOC;
	}
	memset(sub_ar->elements, 0, sub_capacity * sizeof(void*));

	size_t i;
	void* elem;
	//深拷贝
	for (i = 0; i < sub_size; i++)
	{
		elem = malloc(sizeof(void*));
		memcpy(elem, ar->elements[b+i], sizeof(void*));
		sub_ar->elements[i] = elem;
	}
	sub_ar->capacity = sub_capacity;
	sub_ar->size = sub_size;

	*out = sub_ar;
	return OK;
}

size_t array_size(array* ar)
{
	return ar->size;
}

size_t array_capacity(array* ar)
{
	return ar->capacity;
}

size_t cc_array_contains(array* ar, void* elem)
{
	size_t i;
	for (i = 0; i < ar->size; i++) {
		if (ar->elements[i] == elem)
			return 1;
	}
	return 0;
}

void	array_iter_init(array_iter* iter, array* ar)
{
	iter->ar = ar;
	iter->index = 0;
	iter->last_removed = 0;
}

enum stat array_iter_next(array_iter* iter, void** out)
{
	if (iter->index >= iter->ar->size)
		return ITER_END;

	*out = iter->ar->elements[iter->index];

	iter->index++;
	iter->last_removed = 0;

	return OK;
}

enum stat array_iter_remove(array_iter* iter, void** out)
{
	enum cc_stat status = ERR_VALUE_NOT_FOUND;

	if (!iter->last_removed) {
		status = array_remove_at(iter->ar, iter->index - 1, out);
		if (status == OK)
			iter->last_removed = 1;
	}
	return status;
}

enum stat array_iter_add(array_iter* iter, void* elem)
{
	return array_add_at(iter->ar, elem, iter->index++);
}

enum stat array_iter_index(array_iter* iter)
{
	return iter->index - 1;
}