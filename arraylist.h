#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef unsigned short bool;

typedef enum storage_type {
    DYNAMIC, /* if elements are added past capacity reallocate */
    FIXED /* cannot add elements after capacity is maxed out */
} Storage_type;

typedef struct array_list {
  Storage_type storage_type;  
  size_t elt_size;
  size_t capacity;
  char* data;
  char* top;
} List;

List* list_create(size_t, size_t);
bool list_append(List* const, void*);
bool list_destroy(List** const);
bool list_init(List* const, size_t, size_t);
bool list_clear(List* const);
