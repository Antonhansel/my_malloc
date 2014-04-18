/*
** block.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:13:56 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:35 2014 ribeaud antonin
*/

#include		"malloc.h"

t_malloc		find_block(t_malloc *prev, size_t size)
{
  t_malloc		tmp;

  tmp = getset_list(NULL, 0);
  while (tmp && !(tmp->is_free && tmp->size >= size))
    {
      *prev = tmp;
      tmp = tmp->next;
    }
  return (tmp);
}

void			split_block(t_malloc prev, size_t size)
{
  t_malloc		tmp;

  tmp = (t_malloc)(prev->data + size);
  tmp->size = prev->size - size - SIZE;
  tmp->next = prev->next;
  tmp->prev = prev;
  tmp->is_free = 1;
  tmp->ptr = tmp->data;
  prev->size = size;
  prev->next = tmp;
  if (tmp->next)
    tmp->next->prev = tmp;
}

t_malloc		extend_block(t_malloc prev, size_t size)
{
  t_malloc		tmp;

  if ((SIZE + size) <= getfreespace() && sbrk(0) > getbrk())
    tmp = sbrk(0) - getfreespace();
  else
    {
      tmp = sbrk(0);
      if ((void*)-1 == sbrk(getpagesize()))
	return (NULL);
    }
  tmp = sbrk(0);
  if ((void*)-1 == sbrk(SIZE + size))
    return (NULL);
  tmp->size = size;
  tmp->next = NULL;
  tmp->prev = prev;
  tmp->ptr = tmp->data;
  if (prev)
    prev->next = tmp;
  tmp->is_free = 0;
  return (tmp);
}

size_t			getfreespace()
{
  t_malloc		tmp;
  size_t		tsize;
  size_t		pagesize;

  pagesize = (int)getpagesize();
  tmp = getset_list(NULL, 0);
  if (tmp == NULL)
    return (0);
  tsize = 0;
  while (tmp != NULL)
    {
      tsize += tmp->size + SIZE;
      tmp = tmp->next;
    }
  while (tsize > pagesize)
    tsize -= pagesize;
  return (pagesize - tsize);
}

void			*getbrk()
{
  t_malloc		tmp;
  t_malloc		prev;

  tmp = getset_list(NULL, 0);
  while (tmp != NULL)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  return (prev + prev->size + SIZE);
}
