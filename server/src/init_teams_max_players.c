/*
** init_teams_max_players.c for init_teams_max_players in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun 16 14:27:56 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 14:58:58 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
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
	{
	  if (strlen(tmp_team->name) > 512)
	    {
	      fprintf(stderr, ERR_TEAM_NAME);
	      return (-1);
	    }
	  tmp_team->max_players = max_players;
	}
      i++;
    }
  if (i <= 1)
    {
      fprintf(stderr, ERR_NBTEAMS);
      return (-1);
    }
  return (0);
}
