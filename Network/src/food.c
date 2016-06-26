/*
** food.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Sun Jun 26 05:30:49 2016 Kevin Empociello
** Last update Sun Jun 26 14:36:16 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		food_gen(t_server *srv)
{
  struct timeb	now;

  if (list_get_size(srv->all_players) == 0)
    return (0);
  ftime(&now);
  if (calculate_elapse(&srv->timer.val, &now) >= (1350 / srv->data.delay) &&
      list_get_size(srv->all_players) > 0)
    {
      if (generate_new_resources(srv) == -1)
	return (-1);
      ftime(&srv->timer.val);
    }
  return (0);
}
