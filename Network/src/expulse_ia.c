/*
** expulse_ia.c for expulse_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:31 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 15:50:26 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "replies.h"
#include "errors.h"
#include "server.h"

static void	get_future_position(t_server *server, t_player *player,
				    int *y, int *x)
{
  *x = player->x;
  *y = player->y;
  player->orientation == TOP ? (*y -= 1) :
      player->orientation == BOTTOM ? (*y += 1) : 0;
  player->orientation == RIGHT ? (*x += 1) :
      player->orientation == LEFT ? (*x -= 1) : 0;
  *x = *x >= server->data.world_x ? 0 : *x < 0 ? server->data.world_x - 1 : *x;
  *y = *y >= server->data.world_y ? 0 : *y < 0 ? server->data.world_y - 1 : *y;
}

static int	deplacement(t_server *server,
			    t_player *pusher, t_player *victim)
{
  int		i;
  int		target_perimeter[17];

  i = 0;
  call_init_perimeter(server->data, victim, target_perimeter);
  while (target_perimeter[i] != -1)
    {
      if (target_perimeter[i] == pusher->y
	  && target_perimeter[i + 1] == pusher->x)
	{
	  if (dprintf(victim->sock, MOVE, (i / 2) + 1) == -1)
	    {
	      fprintf(stderr, ERR_PRINTF);
	      return (-1);
	    }
	  return (0);
	}
      i += 2;
    }
  return (0);
}

static int	manage_expulse(t_server *server, t_player *player,
			       t_list players, unsigned int const i)
{
  t_player	*p;
  int		x;
  int		y;

  get_future_position(server, player, &y, &x);
  if ((p = list_get_elem_at_position(players, i)) != NULL)
    {
      p->sock != player->sock ? (p->x = x) : 0;
      p->sock != player->sock ? (p->y = y) : 0;
    }
  if (p != NULL && (ppo_ia(server, p) == -1
		    || (p->sock != player->sock
			&& deplacement(server, player, p) == -1)))
    return (-1);
  return (0);
}

int		expulse_ia(t_server *server, t_player *player)
{
  t_list	tmp;
  unsigned int	i;
  unsigned int	number;

  i = -1;
  tmp = get_players_at_pos(&server->data, player->y, player->x);
  number = list_get_size(tmp);
  if (!tmp || number <= 1)
    return (dprintf(player->sock, KO));
  else if (dprintf(player->sock, OK) == -1 || pex(server, player) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  while (++i < list_get_size(tmp))
    {
      if (manage_expulse(server, player, tmp, i) == -1)
	return (-1);
    }
  return (0);
}
