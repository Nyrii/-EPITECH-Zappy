/*
** timer.c for  in /home/empoci_k/rendu_tek2/PSU_2015_myirc/server_src
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Tue May 31 03:36:45 2016 Kévin Empociello
** Last update Thu Jun  9 01:11:53 2016 Kevin Empociello
*/

#include "server.h"

static double	calculate_elapse(struct timeb *before, struct timeb *after)
{
  double	res;

  res = (after->time*1000 + after->millitm) -
      (before->time*1000 + before->millitm);
  res /= 1000;
  return (res);
}

static int	waiting_list(t_server *srv)
{
  struct timeb	now;
  unsigned int	i;
  t_client	*cl;

  i = 0;
  ftime(&now);
  while (i < list_get_size(srv->queue_clients))
    {
      if ((cl = list_get_elem_at_position(srv->queue_clients, i)) != NULL)
	{
	  if (calculate_elapse(&cl->timer.val, &now) >= 10.0)
	    {
	      close(cl->sock);
	      list_del_elem_at_position(&srv->queue_clients, i);
	      return (0);
	    }
	}
      i++;
    }
  return (0);
}

int	check_timer(t_server *srv)
{
  waiting_list(srv);
  return (0);
}
