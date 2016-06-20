/*
** incantation_ia.c for incantation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:11 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 19:17:34 2016 Nyrandone Noboud-Inpeng
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
  while (++i < list_get_size(tmp))
    {
      if ((tmp_player = list_get_elem_at_position(tmp, i)) != NULL
	  && tmp_player->level == level)
	tmp_player->level += 1;
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
  if (pie(server, player, 0) == -1)
    return (-1);
  return (-2);
}

int		incantation_manager(t_server *server,
				    t_player *player, int *pos)
{
  int		ret_value;

  if ((ret_value = manage_level_player(server, player,
				       pos, player->level)) == -1
      || ret_value == -2)
    return (ret_value);
  if (send_update_tile(server, player) == -1 || pie(server, player, 1) == -1)
    return (-1);
  if (player->level == 8)
    {
      if (send_message_to_all_players(server, player, CURRENT_LEVEL,
				      player->level) == -1
	  || seg(server, player) == -1)
	return (-1);
      return (2);
    }
  if (send_message_to_all_players(server, player,
				  CURRENT_LEVEL, player->level) == -1
      || plv_ia(server, player) == -1)
    return (-1);
  return (0);
}

int		incantation_ia(t_server *server, t_player *player)
{
  int		pos[2];
  int		ret_value;

  pos[0] = player->y;
  pos[1] = player->x;
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    {
      if (send_message_to_all_players(server, player,
				      ELEVATION_IN_PROGRESS, -1) == -1
	  || pic(server, player) == -1)
	return (-1);
      if ((ret_value = incantation_manager(server, player, pos)) == -1
	  || ret_value == 0 || ret_value == 2)
	return (ret_value);
    }
  if (dprintf(player->sock, KO) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
