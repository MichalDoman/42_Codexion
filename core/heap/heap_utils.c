#include "heap.h"

int	heap_compare(t_heap_item *a, t_heap_item *b, int flag)
{
	if (a->value == b->value)
		return (a->coder_id < b->coder_id);
	if (flag == 1)
		return (a->value > b->value);
	return (a->value < b->value);
}

void	heap_swap(t_heap_item *a, t_heap_item *b)
{
	t_heap_item	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_branch_adjust(t_heap *heap, int flag)
{
	int current_i;
	int left_i;
	int	right_i;
	int best_i;

	current_i = 0;
	while(1)
	{
		left_i = current_i * 2 + 1;
		right_i = current_i * 2 + 2;
		best_i = current_i;
		if(left_i < heap->size
		&& heap_compare(&heap->items[left_i], &heap->items[best_i], flag))
			best_i = left_i;
		if(right_i < heap->size
		&& heap_compare(&heap->items[right_i], &heap->items[best_i], flag))
			best_i = right_i;
		if (best_i == current_i)
			break ;
		heap_swap(&heap->items[current_i], &heap->items[best_i]);
		current_i = best_i;
	}
}
