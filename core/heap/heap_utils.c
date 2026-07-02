#include "heap.h"

int	heap_compare(t_heap_item *a, t_heap_item *b)
{
	if (a->value != b->value)
		return (a->value > b->value);
	return (a->coder_id < b->coder_id);
}

void	heap_swap(t_heap_item *a, t_heap_item *b)
{
	t_heap_item	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}