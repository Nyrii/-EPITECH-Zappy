/*
** life.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Fri Jun 17 18:18:58 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

// 1 unité de vie  = 126 * 1/t
int		player_life(t_server *srv, t_player *p)
{
  struct timeb	now;

  ftime(&now);
  if (p->inventory[FOOD] <= 0)
    {
      dprintf(p->sock, "mort\n");
      close(p->sock);
      remove_player_from_srv(srv, get_team_by_player(srv, p), p);
      return (-1);
    }
  double tmp = calculate_elapse(&p->timer.val, &now);
  if (tmp >= 126.0 * (1.0 / srv->data.delay))
    {
      p->inventory[FOOD]--;
      if (p->inventory[FOOD] < 0)
	p->inventory[FOOD] = 0;
      ftime(&p->timer.val);
    }
  return (0);
}
