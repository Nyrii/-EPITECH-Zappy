/*
** get_egg.c for get_egg in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 14:26:55 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:37:37 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

int			get_max_egg_id(t_server *srv)
{
  unsigned int		i;
  t_egg			*egg;
  int			max;

  i = 0;
  max = 0;
  if (!srv)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  while (i < list_get_size(srv->data.eggs))
    {
      if ((egg = list_get_elem_at_position(srv->data.eggs, i)) != NULL &&
	  egg->id > max)
	max = egg->id;
      i++;
    }
  return (max);
}
