/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 10:04:10 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 11:34:04 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include <stdlib.h>

typedef struct s_heap_item
{
	int	coder_id;
	int	value;
}	t_heap_item;

typedef struct s_heap
{
	t_heap_item	*items;
	int			max_size;
	int			size;
}	t_heap;

// core/heap/heap.c
t_heap	*heap_init(int max_size);
void	heap_push(t_heap *heap, t_heap_item *a);
int		heap_remove(t_heap *heap, t_heap_item *item);
void	heap_free(t_heap *heap);

// core/heap/heap_utils.c
int		heap_compare(t_heap_item *a, t_heap_item *b);
void	heap_swap(t_heap_item *a, t_heap_item *b);

#endif
