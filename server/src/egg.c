/*
** egg.c for  in /home/empoci_k/rendu_tek2/PSU_2015_myirc/server_src
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Tue May 31 03:36:45 2016 Kévin Empociello
** Last update Wed Jun 22 17:50:56 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

static int	check_egg(t_server *srv, t_egg *egg)
{
  t_team	*t;
  struct timeb	now;

  ftime(&now);
  if (egg->is_born == 1)
    return (0);
  if (calculate_elapse(&egg->timer.val, &now) >= 600 / srv->data.delay)
    {
      if (eht(srv, egg) == -1)
	return (-1);
      if ((t = get_team_by_name(srv, egg->team_name)) == NULL)
	return (-1);
      t->max_players++;
      egg->is_born = 1;
    }
  return (0);
}

int		egg_list(t_server *srv)
{
  t_egg		*eg;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->data.eggs))
    {
      if ((eg = list_get_elem_at_position(srv->data.eggs, i)) != NULL)
	if (check_egg(srv, eg) == -1)
	  return (-1);
      i++;
    }
  return (0);
}
