/*
** malloc.h for mallox in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:14:29 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:34 2014 ribeaud antonin
*/

#ifndef	_MALLOC_H_
#define	_MALLOC_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_malloc
{
  size_t		size;
  struct s_malloc	*next;
  struct s_malloc	*prev;
  int			is_free;
  void			*ptr;
  char			data[1];
}			*t_malloc;

#define			SIZE sizeof(void*) * 5

void			split_block(t_malloc, size_t);
t_malloc		extend_block(t_malloc, size_t);
void			copy_block(t_malloc, t_malloc);
t_malloc		find_block(t_malloc*, size_t);
t_malloc		get_block(void *);
void			free(void *);
void			*realloc(void *, size_t);
void			*malloc(size_t);
t_malloc		fusion(t_malloc);
size_t			align(size_t);
void			*simple_realloc(void*, t_malloc , size_t);
int			legit_malloc(t_malloc, size_t);
int			cant_split(t_malloc, size_t);
void			*getset_list(t_malloc , int);
void			show_alloc_mem(void);
t_malloc		continue_malloc(size_t, t_malloc);
void			*getbrk();
size_t			getfreespace();
void			change_mutex(int);
int			valid_addr(void*);
t_malloc		set_malloc(size_t *);

#endif			/*!MALLOC_H_!*/
