/*
** statics.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:13:40 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:35 2014 ribeaud antonin
*/

#include			"malloc.h"

void				change_mutex(int status)
{
  static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_unlock(&mutex);
  if (status == 1)
    pthread_mutex_lock(&mutex);
  if (status == 0)
    pthread_mutex_unlock(&mutex);
}

void				*getset_list(t_malloc par, int getset)
{
  static void			*list = NULL;

  if (getset == 1)
    list = par;
  else if (getset == 0)
    return (list);
  else
    list = NULL;
  return (NULL);
}

