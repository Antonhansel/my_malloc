/*
** free.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:14:11 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:34 2014 ribeaud antonin
*/

#include	"malloc.h"

t_malloc	fusion(t_malloc tmp)
{
  if (tmp->next && tmp->next->is_free)
    {
      tmp->size += SIZE + tmp->next->size;
      tmp->next = tmp->next->next;
      if (tmp->next)
	tmp->next->prev = tmp;
    }
  return (tmp);
}

int		valid_addr(void *ptr)
{
  t_malloc	malloc;
  void		*nptr;

  nptr = ptr - SIZE;
  malloc = (t_malloc)nptr;
  if (getset_list(NULL, 0) != NULL)
    {
      if (ptr >= getset_list(NULL, 0) && ptr < sbrk(0))
	return (ptr == malloc->ptr);
    }
  return (0);
}

void		free(void *ptr)
{
  t_malloc	tmp;
  void		*nptr;

  change_mutex(1);
  if (valid_addr(ptr) == 1)
    {
      nptr = ptr - SIZE;
      tmp = (t_malloc)nptr;
      tmp->is_free = 1;
      if (tmp->prev != NULL && tmp->prev->is_free == 1)
	tmp = fusion (tmp->prev);
      if (tmp->next)
	fusion(tmp);
      else
	{
	  if (tmp->prev)
	    tmp->prev->next = NULL;
          else
	    getset_list(NULL, -1);
	  brk(tmp);
        }
    }
  change_mutex(0);
}
