/*
** incantation_ia.c for incantation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:11 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 15:23:57 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	manage_level_player(t_server *server,
				    t_player *player, int *pos,
				    int const level)
{
  unsigned int	i;
  int		ret_value;
  t_list	tmp;
  t_player	*tmp_player;

  i = -1;
  if ((ret_value = pie(server, player)) == 0)
    {
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
      while (server->data.map[pos[0]][pos[1]][++i] != -1)
	server->data.map[pos[0]][pos[1]][i]
      -= server->data.resources[level][i];
    }
  else if (ret_value == -1)
    return (-1);
  return (0);
}

int		incantation_ia(t_server *server, t_player *player)
{
  int		pos[2];

  pos[0] = player->y;
  pos[1] = player->x;
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    {
      if (send_message_to_all_players(&server->data, player,
                                      ELEVATION_IN_PROGRESS, -1) == -1
	  || pic(server, player) == -1
	  || manage_level_player(server, player, pos, player->level) == -1)
	return (-1);
      if (player->level == 8)
	{
	  if (send_message_to_all_players(&server->data, player, CURRENT_LEVEL,
					  player->level) == -1
	      || seg(server, player) == -1)
	    return (-1);
	  return (2);
	}
      if (send_message_to_all_players(&server->data, player,
				      CURRENT_LEVEL, player->level) == -1
	  || plv_ia(server, player) == -1)
	return (-1);
      return (0);
    }
  if (dprintf(player->sock, KO) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
