/*
** simple_list.c for  in /home/empoci_k/rendu_tek2/piscine_cpp_d02a/ex00
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Thu Jan  7 15:14:51 2016 Kévin Empociello
** Last update Sat Jun 25 15:21:50 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

t_player		*get_player_by_id(t_server *srv, int const id)
{
  unsigned int		i;
  t_player		*p;

  i = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL &&
	  p->id == id)
	return (p);
      i++;
    }
  return (NULL);
}

int			get_max_player_id(t_server *srv)
{
  unsigned int		i;
  t_player		*p;
  int			max;

  i = 0;
  max = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL &&
	  p->id > max)
	max = p->id;
      i++;
    }
  return (max);
}

t_player	*get_player_by_sock(t_data *data, int sock)
{
  t_team	*t;
  t_player	*p;
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  while (i < list_get_size(data->teams))
    {
      if ((t = list_get_elem_at_position(data->teams, i)) != NULL)
	{
	  j = 0;
	  while (j < list_get_size(t->players))
	    {
	      if ((p = list_get_elem_at_position(t->players, j)) != NULL &&
		  p->sock == sock)
		return (p);
	      j++;
	    }
	}
      i++;
    }
  return (NULL);
}

t_list		get_players_at_pos(t_data *data, int y, int x)
{
  t_team	*t;
  t_player	*p;
  t_list	tmp;
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
		list_add_elem_at_back(&tmp, p);
	      j++;
	    }
	}
      i++;
    }
  return (tmp);
}
