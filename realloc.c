/*
** realloc.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:14:17 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:34 2014 ribeaud antonin
*/

#include	"malloc.h"

void		*realloc(void *ptr, size_t size)
{
  t_malloc	tmp;
  void		*nptr;

  change_mutex(1);
  size = align(size);
  if (!ptr)
    return (malloc(size));
  if (valid_addr(ptr))
    {
      nptr = ptr - SIZE;
      tmp = (t_malloc)nptr;
      if (tmp->size >= size)
	{
	  if (tmp->size - size >= SIZE + 4)
	    split_block(tmp, size);
	}
      else if (cant_split(tmp, size) == 1)
	  return (simple_realloc(ptr, tmp, size));
      return (ptr);
    }
  change_mutex(0);
  return (NULL);
}

int		cant_split(t_malloc tmp, size_t size)
{
  if (legit_malloc(tmp, size) == 1)
    {
      fusion(tmp);
      if (tmp->size - size >= SIZE + 4)
	split_block(tmp, size);
      return (0);
    }
  else
    return (1);
}

int		legit_malloc(t_malloc tmp, size_t size)
{
  if (tmp->next && tmp->next->is_free &&
      (tmp->size + SIZE + tmp->next->size) >= size)
    return (1);
  else
    return (0);
}

void		*simple_realloc(void *ptr, t_malloc tmp, size_t size)
{
  void		*n_ptr;
  void		*nptr;
  t_malloc	new;

  n_ptr = malloc(size);
  if (n_ptr == NULL)
    return (NULL);
  nptr = n_ptr - SIZE;
  new = (t_malloc)nptr;
  copy_block(tmp, new);
  free(ptr);
  change_mutex(0);
  return (n_ptr);
}

void		copy_block(t_malloc src, t_malloc dst)
{
  int		*srcdata;
  int		*destdata;
  size_t	i;

  srcdata = src->ptr;
  destdata = dst->ptr;
  i = 0;
  while (i * 4 < src->size && i * 4 < dst->size)
    {
      destdata [i] = srcdata [i];
      i++;
    }
}
