/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 10:03:31 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 11:38:39 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heap.h"

static int	heap_compare(t_heap_item *a, t_heap_item *b)
{
	if (a->value > b->value)
		return 1;
	return 0;
}

static void	heap_swap(t_heap_item *a, t_heap_item *b)
{
	t_heap_item	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_heap	*heap_init(int max_size)
{
	t_heap		*heap;

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
	return (heap);
}

void	heap_push(t_heap *heap, t_heap_item *item)
{
	int	i;
	int	parent_id;

	if (!heap || (heap->size >= heap->max_size))
		return ;
	if (heap->size == 0)
	{
		heap->items[0] = *item;
		heap->size++;
		return ;
	}
	i = heap->size;
	heap->items[i] = *item;
	heap->size++;
	while (i > 0)
	{
		parent_id = (i - 1) / 2;
		if (!heap_compare(heap->items[i], heap->items[parent_id]))
			return ;
		heap_swap(heap->items[i], heap->items[parent_id]);
		i = parent_id;
	}
}

void	heap_free(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->items);
	free(heap);
}