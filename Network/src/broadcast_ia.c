/*
** broadcast_ia.c for broadcast_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:55 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 14:58:29 2016 Nyrandone Noboud-Inpeng
*/

#include <math.h>
#include "server.h"

static void	determine_best_way(int *src, int *dest,
				   int *pos)
{
  int		i;
  int		n;
  int		distance;

  distance = -1;
  i = 0;
  while (src[i] != -1)
    {
      n = 0;
      while (dest[n] != -1)
	{
	  if (distance == -1 || distance > sqrt(pow(src[i + 1] - dest[n + 1], 2)
						+ pow(src[i] - dest[n], 2)))
	    {
	      distance = sqrt(pow(src[i + 1] - dest[n + 1], 2)
			      + pow(src[i] - dest[n], 2));
	      pos[0] = dest[n];
	      pos[1] = dest[n + 1];
	    }
	  n += 2;
	}
      i += 2;
    }
}

static int	determine_direction(int *dest, int *pos)
{
  int		i;

  i = 0;
  while (dest[i] != -1)
    {
      if (dest[i] == pos[0])
	return (i / 2 + 1);
      i += 2;
    }
  return (0);
}

int		broadcast_ia(t_server *server, t_player *player)
{
  int		perimeter_src[17];
  int		perimeter_dest[17];
  int		pos[2];
  t_list	tmp;
  int		direction;

  tmp = server->all_players;
  call_init_parameter(server->data, player, perimeter_src);
  while (tmp != NULL)
    {
      call_init_parameter(server->data, (t_player *)(tmp->value),
			  perimeter_dest);
      determine_best_way(perimeter_src, perimeter_dest, pos);
      direction = determine_direction(perimeter_dest, pos);
      (void)direction;
      // répondre au client
      tmp = tmp->next;
    }
  return (0);
}
