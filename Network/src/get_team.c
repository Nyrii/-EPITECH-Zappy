/*
** simple_list.c for  in /home/empoci_k/rendu_tek2/piscine_cpp_d02a/ex00
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Thu Jan  7 15:14:51 2016 Kévin Empociello
** Last update Sat Jun 11 19:32:36 2016 Kevin Empociello
*/

#include <string.h>
#include "server.h"

t_team		*get_team_by_name(t_server *srv, const char *name)
{
  unsigned int	i;
  t_team	*t;

  i = 0;
  while (i < list_get_size(srv->data.teams))
    {
      if ((t = list_get_elem_at_position(srv->data.teams, i)) != NULL
	  && strcmp(t->name, name) == 0)
	return (t);
      i++;
    }
  return (NULL);
}

t_team		*get_team_by_player(t_server *srv, t_player *pl)
{
  unsigned int	i;
  unsigned int	j;
  t_team	*t;
  t_player	*p;

  i = 0;
  while (i < list_get_size(srv->data.teams))
    {
      if ((t = list_get_elem_at_position(srv->data.teams, i)) != NULL)
	{
	  j = 0;
	  while (j < list_get_size(t->players))
	    if ((p = list_get_elem_at_position(t->players, j)) != NULL &&
		p == pl)
		return (t);
	}
      i++;
    }
  return (NULL);
}
