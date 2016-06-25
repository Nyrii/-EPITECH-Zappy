/*
** broadcast_ia.c for broadcast_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:55 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 14:02:12 2016 Nyrandone Noboud-Inpeng
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

  distance = -1.0;
  x = 0;
  angle = 0.0;
  while (x < 17)
    {
      if (distance == -1.0
	  || distance > sqrt(pow(calculs[x] - player->y, 2)
			     + pow(calculs[x + 1] - player->x, 2)))
	{
	  distance = sqrt(pow(calculs[x] - player->y, 2)
			  + pow(calculs[x + 1] - player->x, 2));
	  angle = get_angle(player, calculs[x], calculs[x + 1]);
	}
      x += 2;
    }
  return (get_best_tile_by_angle(angle, target));
}

static int	determine_best_way(t_server *server, t_player *player,
				   t_player *target)
{
  int		calculs[19];
  int		tile;

  init_calculs(server->data, calculs, target);
  if (player->x == target->x && player->y == target->y)
    return (0);
  else
    tile = get_best_distance_from_tile(target, player, calculs);
  if (tile == -1)
    return (0);
  return (tile);
}

static int	concat_answer(t_server *server, char **answer,
			      int tile, int null)
{
  char		buffer[1024];
  int		i;

  if (null == 0)
    return (0);
  if (memset(buffer, 0, 1024) == NULL
      || snprintf(buffer, 1024, BROADCAST, tile, server->params) == -1)
    return (-1);
  i = 0;
  while (buffer[i])
    {
      (*answer)[i] = buffer[i];
      ++i;
    }
  (*answer)[i] = '\0';
  return (0);
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
	  if (null == 1
	      && (answ = malloc(strlen(server->params) + 150)) == NULL)
	    return (fprintf(stderr, ERR_MALLOC), -1);
	  if (concat_answer(server, &answ, tile, null) == -1)
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
  if (server->params == NULL || strlen(server->params) > 512)
    return (store_answer_p(player, KO, 0));
  else if (store_answer_p(player, OK, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  tmp = server->all_players;
  return (send_broadcast(server, player, tmp, -1));
}
