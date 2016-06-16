/*
** init_teams_max_players.c for init_teams_max_players in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun 16 14:27:56 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 16 14:37:09 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

int		init_teams_max_players(t_list teams, int const max_players)
{
  unsigned int	i;
  t_team	*tmp_team;

  i = 0;
  while (i < list_get_size(teams))
    {
      if ((tmp_team = list_get_elem_at_position(teams, i)) != NULL)
	tmp_team->max_players = max_players;
      i++;
    }
  if (i <= 1)
    {
      fprintf(stderr, ERR_NBTEAMS);
      return (-1);
    }
  return (0);
}
