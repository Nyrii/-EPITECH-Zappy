/*
** life.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sun Jun 26 17:30:58 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		player_life(t_server *srv, t_player *p)
{
  struct timeb	now;
  double	tmp;

  ftime(&now);
  if (p->inventory[FOOD] <= 0)
    {
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
