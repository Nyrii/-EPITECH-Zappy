/*
** store_socks.c for store_socks in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun 21 17:33:11 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 15:00:18 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

static int	len(int *socks)
{
  int		len;
  int		i;

  len = 0;
  i = 0;
  if (socks == NULL)
    return (len);
  while (socks[i] != -1)
    {
      ++i;
      ++len;
    }
  return (len);
}

int		store_socks(int **socks, int const new_sock)
{
  int		is_null;
  int		i;

  i = -1;
  is_null = (*socks) == NULL ? 1 : 0;
  if (((*socks) == NULL && ((*socks) = malloc(3 * sizeof(int))) == NULL)
      || (is_null == 0
	  && ((*socks) = realloc((*socks),
				 (len((*socks)) + 2) * sizeof(int))) == NULL))
    return (fprintf(stderr, ERR_MALLOC), -1);
  if (is_null)
    {
      (*socks)[0] = new_sock;
      (*socks)[1] = -1;
      return (0);
    }
  while ((*socks)[++i] != -1);
  (*socks)[i++] = new_sock;
  (*socks)[i] = -1;
  return (0);
}
