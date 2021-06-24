#ifndef __ARRAY__H
#define __ARRAY__H

#include <stdio.h>
#include <string.h>

enum stat {
	OK = 0,
	ERR_ALLOC = 1,
	ERR_INVALID_CAPACITY = 2,
	ERR_INVALID_RANGE = 3,
	ERR_MAX_CAPACITY = 4,
	ERR_KEY_NOT_FOUND = 6,
	ERR_VALUE_NOT_FOUND = 7,
	ERR_OUT_OF_RANGE = 8,
	ITER_END = 9
};

#define MAX_ELEMENTS ((size_t) - 2)

typedef struct {
	void**  elements;
	size_t	size;
	size_t	capacity;
	float		exp_factor;	/*扩容因子*/
} array;

typedef struct {
	float		exp_factor;
	size_t	capacity;
}  array_conf;

typedef struct {
	array*	ar;
	size_t	index;
	size_t	last_removed;
} array_iter;

enum stat		array_new(array** out);
enum stat		array_new_conf(array** out, array_conf* conf);
void				array_conf_init(array_conf* conf);

void				array_destroy(array** ar);
void				array_destroy_cb(array** ar);

enum stat		array_add(array* ar, void* elem);
enum stat		array_add_at(array* ar, void* elem, size_t index);

enum stat 	array_remove(array* ar, void* elem, void** out); //没卵用
enum stat 	array_remove_at(array* ar, size_t index, void** out);
enum stat 	array_remove_last(array* ar, void** out);
void				array_remove_all(array* ar);
void				array_remove_all_cb(array* ar);

enum stat		array_index_of(array* ar, void* element, size_t* index);  //没卵用
enum stat 	array_get_at(array* ar, size_t index, void** out);
enum stat 	array_get_last(array* ar, void** out);

enum stat		array_subarray(array* ar, size_t b, size_t e, array** out);
enum stat		array_subarray_cb(array* ar, size_t b, size_t e, array** out);

size_t			array_size(array* ar);
size_t		 	array_capacity(array* ar);

size_t			cc_array_contains(array* ar, void* elem);

void				array_iter_init(array_iter* iter, array* ar);
enum stat 	array_iter_next(array_iter* iter, void** out);
enum stat 	array_iter_remove(array_iter* iter, void** out);
enum stat 	array_iter_add(array_iter* iter, void* elem);
enum stat 	array_iter_index(array_iter* iter);
#endif // !__ARRAY__H
