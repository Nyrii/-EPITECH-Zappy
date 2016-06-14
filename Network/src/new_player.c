/*
** new_player.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Tue Jun 14 18:25:06 2016 Nyrandone Noboud-Inpeng
*/

#include <netinet/in.h>
#include <sys/types.h>
#include "server.h"

t_player		*new_player(t_server *srv, t_client *cl)
{
  t_player		*new;

  if ((new = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  new->sock = cl->sock;
  new->x = rand() % srv->data.world_x;
  new->y = rand() % srv->data.world_y;
  new->level = 1;
  new->orientation = rand() % 4 * 90;
  new->timer = 0.0;
  new->id = list_get_size(srv->all_players) + 1;
  new->inventory[FOOD] = 0;
  new->inventory[LINEMATE] = 0;
  new->inventory[DERAUMERE] = 0;
  new->inventory[SIBUR] = 0;
  new->inventory[MENDIANE] = 0;
  new->inventory[PHIRAS] = 0;
  new->inventory[THYSTAME] = 0;
  new->inventory[NONE] = -1;
  if (new->id == 1)
    {
      new->x = 0;
      new->y = 1;
      new->orientation = TOP;
    }
  else
    {
      new->x = 1;
      new->y = 4;
      new->orientation = LEFT;
    }
  printf("Position x : %d, position y : %d, orientation = %d\n", new->x, new->y, new->orientation);
  return (new);
}

t_client        	*new_client(t_server *srv)
{
  t_client		*cl;
  unsigned int		ss;
  struct sockaddr_in	sin;

  if ((cl = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  ss = sizeof(sin);
  cl->timer = 0;
  if ((cl->sock = accept(srv->sock, (struct sockaddr *) &sin, &ss)) == -1)
    {
      error("Error socket can't accept connexion");
      return (NULL);
    }
  if (cl->sock > srv->max)
    srv->max = cl->sock;
  return (cl);
}
