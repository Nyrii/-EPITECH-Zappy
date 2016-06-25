/*
** free.c for free in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 14:43:13 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 15:19:51 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include "server.h"

int		free_map(int ***map, int const ret_value)
{
  int		x;
  int		y;

  y = 0;
  while (map && map[y] != NULL)
    {
      x = 0;
      while (map[y][x] != NULL)
	free(map[y][x++]);
      free(map[y++]);
    }
  if (map)
    free(map);
  map = NULL;
  return (ret_value);
}

int		free_teams(t_list list, int const ret_value)
{
  unsigned int	i;
  t_list	tmp;
  t_team	*tmp_team;

  i = 0;
  while (list != NULL)
    {
      tmp = list;
      list = list->next;
      if ((tmp_team = list_get_elem_at_position(tmp, i)) != NULL)
	{
	  if (tmp_team->name)
	    free(tmp_team->name);
	  tmp_team->name = NULL;
	  free(tmp_team);
	  tmp_team = NULL;
	}
      free(tmp);
      tmp = NULL;
    }
  list = NULL;
  return (ret_value);
}

int		free_list(t_list list, int const ret_value)
{
  t_list	tmp;

  if (!list)
    return (ret_value);
  while (list != NULL)
    {
      tmp = list;
      list = list->next;
      if (tmp->value)
	free(tmp->value);
      tmp->value = NULL;
      free(tmp);
      tmp = NULL;
    }
  list = NULL;
  return (ret_value);
}

int		free_int_tab(int *tab, int const ret_value)
{
  if (tab)
    free(tab);
  tab = NULL;
  return (ret_value);
}

int		free_double_int_tab(int **tab, int const ret_value)
{
  int		y;

  y = 0;
  while (tab && tab[y] != NULL)
    free(tab[y++]);
  if (tab)
    free(tab);
  tab = NULL;
  return (ret_value);
}
