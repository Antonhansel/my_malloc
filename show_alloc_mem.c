/*
** show_alloc_mem.c for rendu in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:13:46 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:35 2014 ribeaud antonin
*/

#include	"malloc.h"

void		show_alloc_mem(void)
{
  t_malloc	tmp;

  tmp = getset_list(NULL, 0);
  printf("break : %p\n", sbrk(0));
  if (tmp == NULL)
    printf("No memory allocated\n");
  else
    {
      while (tmp != NULL)
	{
	  if (tmp->is_free == 0)
	    printf("malloc : %p - %p : %zu octets\n", &tmp->data, &tmp->data
		   + tmp->size, tmp->size);
	  tmp = tmp->next;
	}
    }
}
