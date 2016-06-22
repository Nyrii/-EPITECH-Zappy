/*
** broadcast_ia.c for broadcast_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:55 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:05:13 2016 Nyrandone Noboud-Inpeng
*/

#include <math.h>
#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static int	get_best_distance_from_tile(t_player *target, t_player *player,
					    int *calculs)
{
  float		distance;
  int		x;
  double	angle;
  double	rad;

  distance = -1;
  x = 0;
  while (calculs[x] != -1)
    {
      if (distance == -1
	  || distance > sqrt(pow(calculs[x] - player->y, 2)
			     + pow(calculs[x + 1] - player->x, 2)))
	{
	  distance = sqrt(pow(calculs[x] - player->y, 2)
			  + pow(calculs[x + 1] - player->x, 2));
	  angle = get_angle(player, calculs[x], calculs[x + 1], &rad);
	}
      x += 2;
    }
  return (get_best_tile_by_angle(angle, rad, target));
}

static int	determine_best_way(t_server *server, t_player *player,
				   t_player *target)
{
  int		calculs[19];
  int		tile;

  init_calculs(server->data, calculs, target);
  tile = get_best_distance_from_tile(target, player, calculs);
  if (tile == -1)
    return (0);
  return (tile);
}

static int	send_broadcast(t_server *server, t_player *player, t_list tmp,
			       unsigned int i)
{
  t_player	*tmp_player;
  int		tile;
  char		*answ;
  int		null;

  null = 1;
  while (++i < list_get_size(tmp))
    {
      if ((tmp_player = list_get_elem_at_position(tmp, i)) != NULL
	  && tmp_player->sock != player->sock)
	{
	  tile = determine_best_way(server, player, tmp_player);
	  if (null == 1 && (answ = malloc(strlen(server->params) + 50)) == NULL)
	    return (fprintf(stderr, ERR_MALLOC), -1);
	  if (null == 1 && !memset(answ, 0, strlen(server->params) + 50)
	      && snprintf(answ, strlen(server->params) + 50, BROADCAST, tile,
			  server->params) == -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	  if (store_answer_p(tmp_player, answ, 0) == -1)
	    return (-1);
	  null = 0;
	}
    }
  return (pbc(server, player));
}

int		broadcast_ia(t_server *server, t_player *player)
{
  t_list	tmp;

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (server->params == NULL)
    return (store_answer_p(player, KO, 0));
  else if (store_answer_p(player, OK, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  tmp = server->all_players;
  return (send_broadcast(server, player, tmp, -1));
}
