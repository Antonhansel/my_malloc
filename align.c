/*
** align.c for malloc in /home/apollo/rendu/old/unix/my_malloc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 18 13:14:04 2014 ribeaud antonin
** Last update Fri Apr 18 13:14:34 2014 ribeaud antonin
*/

#include	"malloc.h"

size_t		align(size_t al)
{
  return ((((al - 1) / 4) * 4) + 4);
}
