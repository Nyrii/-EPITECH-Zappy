/*
** life.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sat Jun 25 20:56:54 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		player_life(t_server *srv, t_player *p)
{
  struct timeb	now;
  double	tmp;
  int		resource;

  ftime(&now);
  if (p->inventory[FOOD] <= 0)
    {
      resource = 0;
      while (srv->data.map && srv->data.map[p->y] && srv->data.map[p->y][p->x]
	     && ++resource < NONE)
	srv->data.map[p->y][p->x][resource] += p->inventory[resource];
      if (store_answer_p(p, strdup(DEAD), 0) == -1 || pdi(srv, p) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
      p->off = 1;
      return (0);
    }
  tmp = calculate_elapse(&p->timer.val, &now);
  if (tmp >= 126.0 * (1.0 / srv->data.delay))
    {
      p->inventory[FOOD]--;
      if (p->inventory[FOOD] < 0)
	p->inventory[FOOD] = 0;
      ftime(&p->timer.val);
    }
  return (0);
}
