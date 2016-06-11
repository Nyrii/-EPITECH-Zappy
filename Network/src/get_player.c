/*
** simple_list.c for  in /home/empoci_k/rendu_tek2/piscine_cpp_d02a/ex00
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Thu Jan  7 15:14:51 2016 Kévin Empociello
** Last update Sat Jun 11 15:56:21 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

t_list		*get_players_at_pos(t_data *data, int y, int x)
{
  t_team	*t;
  t_player	*p;
  t_list	*tmp;
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  tmp = NULL;
  while (i < list_get_size(data->teams))
    {
      if ((t = list_get_elem_at_position(data->teams, i)) != NULL)
	{
	  j = 0;
	  while (j < list_get_size(t->players))
	    {
	      if ((p = list_get_elem_at_position(t->players, j)) != NULL &&
		  p->x == x && p->y == y)
		list_add_elem_at_back(tmp, p);
	      j++;
	    }
	}
      i++;
    }
  return (tmp);
}
