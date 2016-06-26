/*
** broadcast_ia.c for broadcast_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:55 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 12:18:34 2016 Nyrandone Noboud-Inpeng
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

static int	send_broadcast(t_server *server, t_player *player, t_list tmp,
			       char *params)
{
  t_player	*tmp_player;
  int		tile;
  char		buffer[4096];
  unsigned int	i;

  i = -1;
  while (++i < list_get_size(tmp))
    {
      if ((tmp_player = list_get_elem_at_position(tmp, i)) != NULL
	  && tmp_player->sock != player->sock)
	{
	  tile = determine_best_way(server, player, tmp_player);
	    if (memset(buffer, 0, 1024) == NULL
		|| snprintf(buffer, 1024, BROADCAST,
			    tile, params) == -1)
	    return (-1);
	  if (store_answer_p(tmp_player, strdup(buffer), 0) == -1)
	    return (-1);
	}
    }
  return (pbc(server, player));
}

int		broadcast_ia(t_server *server, t_player *player)
{
  t_list	tmp;
  t_task	*current;

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if ((current = list_get_elem_at_position(player->queue_tasks, 0)) == NULL)
    return (-1);
  if (current->params == NULL || strlen(current->params) > 512)
    return (store_answer_p(player, strdup(KO), 0));
  else if (store_answer_p(player, strdup(OK), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  tmp = server->all_players;
  return (send_broadcast(server, player, tmp, current->params));
}
