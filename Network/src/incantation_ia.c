/*
** incantation_ia.c for incantation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:11 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 03:10:01 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	elevation_ok(t_server *server, t_player *player,
			     int const level)
{
  unsigned int	i;
  t_list	tmp;
  t_player	*tmp_player;

  i = -1;
  if ((tmp = get_players_at_pos(&server->data,
				player->y, player->x)) == NULL)
    return (-1);
  if (pie(server, player, 1) == -1)
    return (-1);
  while (++i < list_get_size(tmp))
    {
      if ((tmp_player = list_get_elem_at_position(tmp, i)) != NULL
	  && tmp_player->level == level)
	{
	  tmp_player->level += 1;
	  if (plv_ia(server, tmp_player) == -1)
	    return (-1);
	}
    }
  i = -1;
  while (server->data.map[player->y][player->x][++i] != -1)
    server->data.map[player->y][player->x][i]
      -= server->data.resources[level][i];
  return (0);
}

static int	manage_level_player(t_server *server,
				    t_player *player, int *pos,
				    int const level)
{
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    return (elevation_ok(server, player, level));
  else if (store_answer_p(player, strdup(KO), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  if (pie(server, player, 0) == -1)
    return (-1);
  return (-2);
}

int		incantation_manager(t_server *server,
				    t_player *player, int *pos)
{
  int		ret_value;
  t_team	*victorious;

  victorious = NULL;
  if ((ret_value = manage_level_player(server, player,
				       pos, player->level)) == -1
      || ret_value == -2)
    return (ret_value);
  if (send_update_tile(server, player) == -1)
    return (-1);
  if (send_message_to_all_players(server, player, CURRENT_LEVEL,
				  player->level) == -1)
    return (-1);
  if (is_game_finished(server, &victorious) == 1)
    {
      if (send_end_to_all_players(server->all_players, victorious) == -1
	  || seg(server, victorious) == -1)
	return (-1);
      return (2);
    }
  return (0);
}

int		incantation_ia(t_server *server, t_player *player)
{
  int		*pos;

  if ((pos = malloc(2 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  pos[0] = player->y;
  pos[1] = player->x;
  player->incant.pos = NULL;
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    {
      if (send_message_to_all_players(server, player, ELEVATION_IN_PROGRESS,
				      player->level) == -1
	  || pic(server, player) == -1)
	return (-1);
      player->incant.pos = pos;
      return (1);
    }
  if (store_answer_p(player, strdup(KO), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}
