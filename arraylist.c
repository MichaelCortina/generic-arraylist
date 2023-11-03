#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arraylist.h"

int main(void) {
  int i, *curr;
  List int_list;
  list_init(&int_list, 5, sizeof(int));

  for (i = 0; i <= 10; i += 2)
      list_append(&int_list, &i);

  for (curr = (int*) int_list.data; curr < (int*) int_list.top; curr++) 
    printf("%d ", *curr);
  printf("\n\n");

  printf("%lu %lu\n", int_list.capacity, int_list.elt_size);

  list_clear(&int_list);

  return 0;
}

List* list_create(size_t num_elts, size_t elt_size) {
  List* ret = malloc(sizeof(*ret));
  list_init(ret, num_elts, elt_size);

  return ret;
}

bool list_init(List* const list, size_t num_elts, size_t elt_size) {
    if (list == NULL)
        return FALSE;

    list->storage_type = DYNAMIC;
    list->elt_size = elt_size;
    list->capacity = num_elts;
    list->data = malloc (num_elts * elt_size);
    list->top = list->data;

    return TRUE;
}

bool list_append(List* const list, void* to_add) {
  if (list == NULL) 
    return FALSE;

  /* if capacity has been maxxed out */
  if (list->data + list->capacity * list->elt_size <= list->top) {
    if (list->storage_type == FIXED)
      return FALSE;
    
    /* if storage is dyamic reallocate memory for list
     * after exceeding maximum list capacity
     */
    list->capacity *= 2;
    list->data = realloc(list->data, list->capacity * list->elt_size);
  }

  /* copy element into list, then increment top */
  memcpy(list->top, to_add, list->elt_size);
  list->top = list->top + list->elt_size;

  return TRUE;
}


/* frees all memory inside of a dynamically allocated list,
 * then frees the list itself
 */
bool list_destroy(List** list) {
  if (list == NULL || *list == NULL)
    return FALSE;

  free((*list)->data);
  free(*list);
  *list = NULL;
  return TRUE;
}

bool list_clear(List* const list) {
    if (list == NULL)
        return FALSE;

    free(list->data);
    list->capacity = 0;
    list->top = NULL;
    list->data = NULL;

    return TRUE;
}
