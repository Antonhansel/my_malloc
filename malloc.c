/*
** malloc.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:13:52 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:35 2014 ribeaud antonin
*/

#include		"malloc.h"

void			*malloc(size_t size)
{
  t_malloc		tmp;
  t_malloc		prev;

  change_mutex(1);
  prev = set_malloc(&size);
  if (prev == NULL)
    {
      tmp = extend_block(NULL, size);
      if (tmp == NULL)
	{
	  change_mutex(0);
	  return (NULL);
	}
      getset_list(tmp, 1);
    }
  else
    {
      tmp = continue_malloc(size, prev);
      change_mutex(0);
      if (tmp == NULL)
	return (NULL);
    }
  change_mutex(0);
  return (tmp->data);
}

t_malloc		set_malloc(size_t *size)
{
  *size = align(*size);
  return (getset_list(NULL, 0));
}

t_malloc		continue_malloc(size_t size, t_malloc prev)
{
  t_malloc		prev2;
  t_malloc		tmp;

  prev2 = prev;
  tmp = find_block(&prev2, size);
  if (tmp != NULL)
    {
      if ((tmp->size - size) >= SIZE + 4)
        split_block(tmp, size);
      tmp->is_free = 0;
    }
  else
    tmp = extend_block(prev2, size);
  return (tmp);
}
