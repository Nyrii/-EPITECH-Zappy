/*
** timer.c for  in /home/empoci_k/rendu_tek2/PSU_2015_myirc/server_src
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Tue May 31 03:36:45 2016 Kévin Empociello
** Last update Sun Jun 26 10:37:53 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

double		*init_timer_tasks(t_server *srv)
{
  double	*times;

  if ((times = malloc(12 * sizeof(double))) == NULL)
    return (NULL);
  times[0] = 7.0 / (srv->data.delay * 1.0);
  times[1] = 7.0 / (srv->data.delay * 1.0);
  times[2] = 7.0 / (srv->data.delay * 1.0);
  times[3] = 7.0 / (srv->data.delay * 1.0);
  times[4] = 1.0 / (srv->data.delay * 1.0);
  times[5] = 7.0 / (srv->data.delay * 1.0);
  times[6] = 7.0 / (srv->data.delay * 1.0);
  times[7] = 7.0 / (srv->data.delay * 1.0);
  times[8] = 7.0 / (srv->data.delay * 1.0);
  times[9] = 300.0 / (srv->data.delay * 1.0);
  times[10] = 42.0 / (srv->data.delay * 1.0);
  times[11] = 0.0;
  return (times);
}

int		get_time_by_func(t_server *srv, char *cmd)
{
  int		i;

  i = 0;
  while (srv->cmd_tab_ia[i] != NULL)
    {
      if (strcmp(srv->cmd_tab_ia[i], cmd) == 0)
	return (i);
      i++;
    }
  return (-1);
}

double		calculate_elapse(struct timeb *before, struct timeb *after)
{
  double	res;

  res = (after->time * 1000 + after->millitm) -
    (before->time * 1000 + before->millitm);
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
	      if (close(cl->sock) == -1)
		return (-1);
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
  int	ret;

  ret = 0;
  if (waiting_list(srv) == -1)
    return (-1);
  if ((ret = task_list(srv)) == -1 || ret == 2)
    {
      if (ret == 2
	  && check_and_write_players(&srv->wfd, srv->all_players, -1) == -1)
	return (-1);
      return (ret);
    }
  srv->cmd ? free(srv->cmd) : 0;
  srv->params ? free(srv->params) : 0;
  srv->cmd = NULL;
  srv->params = NULL;
  if (egg_list(srv) == -1)
    return (-1);
  if (check_and_write_players(&srv->wfd, srv->all_players, -1) == -1)
    return (-1);
  if (food_gen(srv) == -1)
    return (-1);
  return (0);
}
