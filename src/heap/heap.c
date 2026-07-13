/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 10:03:31 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/13 10:53:06 by mdomansk         ###   ########.fr       */
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

int	heap_point_root(t_heap *heap, t_heap_item *ptr)
{
	if (!heap || !ptr || heap->size == 0)
		return (0);
	*ptr = heap->items[0];
	return (1);
}

int	heap_push(t_heap *heap, t_heap_item *item)
{
	int	i;

	if (!heap || !item || (heap->size >= heap->max_size))
		return (0);
	i = heap->size;
	heap->items[i] = *item;
	heap->size++;
	heap_adjust_up(heap, i);
	return (1);
}

int	heap_remove(t_heap *heap)
{
	if (!heap || heap->size == 0)
		return (0);
	heap->size--;
	if (heap->size == 0)
		return (0);
	heap->items[0] = heap->items[heap->size];
	heap_adjust_down(heap, 0);
	return (1);
}

int	heap_remove_by_id(t_heap *heap, int id)
{
	int i;
	int	parent_id;

	if (heap->size == 0)
		return (0);
	i = 0;
	while (i < heap->size)
	{
		if (heap->items[i].id == id)
		{
			heap->size--;
			if (heap->size == 0)
				return (0);
			heap->items[i] = heap->items[heap->size];
			parent_id = (i - 1) / 2;
			if (heap_compare(heap, i, parent_id))
				heap_adjust_up(heap, i);
			else
				heap_adjust_down(heap, i);
			break ;
		}
	}
	return (1);
}
