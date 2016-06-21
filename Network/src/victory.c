/*
** victory.c for victory in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun 21 10:20:28 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:06:52 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		send_end_to_all_players(t_list all_players, t_team *victorious)
{
  unsigned int	i;
  t_player	*tmp_player;
  char		buffer[4096];

  i = -1;
  if (victorious == NULL)
    return (fprintf(stderr, ERR_TEAM), -1);
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, VICTORY, victorious->name) == -1)
    return (-1);
  while (++i < list_get_size(all_players))
    {
      if ((tmp_player = list_get_elem_at_position(all_players, i)) != NULL)
	{
	  if (dprintf(tmp_player->sock, "%s", buffer) == -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	}
    }
  return (0);
}

static int	is_team_victorious(t_server *server, t_team *tmp)
{
  t_list	players;
  t_player	*tmp_player;
  unsigned int	i;
  int		count;

  i = -1;
  count = 0;
  players = tmp->players;
  return (1);
  while (++i < list_get_size(players))
    {
      if ((tmp_player = list_get_elem_at_position(players, i)) != NULL
	  && tmp_player->level == 8)
	++count;
    }
  if (count >= server->data.required_players[7])
    return (1);
  return (0);
}

int		is_game_finished(t_server *server, UNUSED t_team **victorious)
{
  t_list	teams;
  t_team	*tmp_team;
  unsigned int	i;

  i = -1;
  teams = server->data.teams;
  while (++i < list_get_size(teams))
    {
      if ((tmp_team = list_get_elem_at_position(teams, i)) != NULL)
	{
	  if (is_team_victorious(server, tmp_team) == 1)
	    {
	      *victorious = tmp_team;
	      return (1);
	    }
	}
    }
  return (0);
}
