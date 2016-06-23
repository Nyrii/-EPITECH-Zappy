/*
** life.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Wed Jun 22 19:21:01 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"
#include "replies.h"

// 1 unité de vie  = 126 * 1/t
int		player_life(t_server *srv, t_player *p)
{
  struct timeb	now;
  double	tmp;

  ftime(&now);
  if (p->inventory[FOOD] <= 0)
    {
      if (store_answer_p(p, DEAD, 0) == -1 || pdi(srv, p) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
      p->off = 1;
      if (close(p->sock) == -1)
	return (fprintf(stderr, ERR_CLOSE), -1);
      remove_player_from_srv(srv, get_team_by_player(srv, p), p);
      return (-1);
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
