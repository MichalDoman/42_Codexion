/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 10:03:31 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:26:53 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

t_heap	*heap_init(int max_size, int flag)
{
	t_heap		*heap;

	if (max_size <= 0)
		return (NULL);
	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->items = malloc(sizeof(t_heap_item) * max_size);
	if (!heap->items)
	{
		free(heap);
		return (NULL);
	}
	heap->max_size = max_size;
	heap->size = 0;
	heap->flag = flag;
	return (heap);
}

void	heap_push(t_heap *heap, t_heap_item *item)
{
	int	i;
	int	parent_id;

	if (!heap || !item || (heap->size >= heap->max_size))
		return ;
	i = heap->size;
	heap->items[i] = *item;
	heap->size++;
	while (i > 0)
	{
		parent_id = (i - 1) / 2;
		if (!heap_compare(
				&(heap->items[i]),
				&(heap->items[parent_id]),
				heap->flag
			)
		)
			return ;
		heap_swap(&(heap->items[i]), &(heap->items[parent_id]));
		i = parent_id;
	}
}

int	heap_remove(t_heap *heap, t_heap_item *item)
{
	if (heap->size == 0)
		return (0);
	*item = heap->items[0];
	heap->size--;
	heap->items[0] = heap->items[heap->size];
	if (heap->size > 0)
		heap_branch_adjust(heap, heap->flag);
	return (1);
}

void	heap_free(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->items);
	free(heap);
}
