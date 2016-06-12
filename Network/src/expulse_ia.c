/*
** expulse_ia.c for expulse_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:31 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 16:54:14 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "replies.h"
#include "errors.h"
#include "server.h"

static int	pex(t_server *server, t_player *player)
{
  char		buffer[20];

  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, "pex %d", player->id) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}

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
  *y = *y >= server->data.world_y ? 0 : *y < 0 ? server->data.world_y - 1 : *x;
}

int		expulse_ia(t_server *server, t_player *player)
{
  t_list	tmp;
  t_player	*p;
  unsigned int	i;
  int		x;
  int		y;
  unsigned int	number;

  i = -1;
  tmp = get_players_at_pos(&server->data, player->y, player->x);
  number = list_get_size(tmp);
  if (number <= 1)
    return (dprintf(player->sock, KO));
  else if (dprintf(player->sock, OK) == -1 || pex(server, player) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  get_future_position(server, player, &y, &x);
  while (i++ < list_get_size(tmp))
    {
      if ((p = list_get_elem_at_position(tmp, i)) != NULL &&
	  ppo_ia(server, p) != -1)
	{
	  if (p != player)
	    {
	      p->x = x;
	      p->y = y;
	    }
	}
    }
  /*while (tmp != NULL)
    {
      if (ppo_ia(server, (t_player *)((*tmp)->value)) == -1)
	return (-1);
      if (((t_player *)((*tmp)->value))->sock != player->sock)
	{
	  ((t_player *)((*tmp)->value))->x = x;
  	  ((t_player *)((*tmp)->value))->y = y;
	}
      *tmp = (*tmp)->next;
    }*/

  return (0);
}
