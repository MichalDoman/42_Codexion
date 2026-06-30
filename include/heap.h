#ifndef HEAP_H
# define HEAP_H

typedef struct s_heap_item
{
	int	coder_id;
	int	priority;
}	t_heap_item;

typedef struct s_heap
{
	t_heap_item	*items;

}	t_heap;

#endif
