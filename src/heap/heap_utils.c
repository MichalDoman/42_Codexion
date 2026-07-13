/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:27 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/13 10:53:36 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

int	heap_compare(t_heap *heap, int id_1, int id_2)
{
	t_heap_item	*a;
	t_heap_item *b;

	a = &(heap->items[id_1]);
	b = &(heap->items[id_2]);
	if (a->value == b->value)
		return (a->id < b->id);
	if (heap->flag == 1)
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

void	heap_adjust_up(t_heap *heap, int current_id)
{
	int parent_id;

	while(current_id > 0)
	{
		parent_id = (current_id - 1) / 2;
		if (parent_id == current_id)
			break ;
		if (heap_compare(heap, parent_id, current_id))
			break ;
		heap_swap(&heap->items[current_id], &heap->items[parent_id]);
		current_id = parent_id;
	}
}

void	heap_adjust_down(t_heap *heap, int current_id)
{
	int	left_id;
	int	right_id;
	int	best_id;

	while (1)
	{
		left_id = current_id * 2 + 1;
		right_id = current_id * 2 + 2;
		best_id = current_id;
		if (left_id < heap->size && heap_compare(heap, left_id, best_id))
			best_id = left_id;
		if (right_id < heap->size && heap_compare(heap, right_id, best_id))
			best_id = right_id;
		if (best_id == current_id)
			break ;
		heap_swap(&heap->items[current_id], &heap->items[best_id]);
		current_id = best_id;
	}
}

void	heap_free(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->items);
	free(heap);
}
