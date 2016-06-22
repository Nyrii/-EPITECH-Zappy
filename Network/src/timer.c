/*
** timer.c for  in /home/empoci_k/rendu_tek2/PSU_2015_myirc/server_src
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Tue May 31 03:36:45 2016 Kévin Empociello
** Last update Thu Jun  9 01:11:53 2016 Kevin Empociello
*/

#include <string.h>
#include "server.h"

// avance, droite, gauche, voir : 7
// inventaire : 1
// prend, pose, expulse, broadcast : 7
// incantation : 300
// fork : 42
// slot : 0
// free!
double		*init_timer_tasks(t_server *srv)
{
  double	*times;

  if ((times = malloc(12 * sizeof(double))) == NULL)
    return (NULL);
  times[0] = 7 / srv->data.delay;
  times[1] = 7 / srv->data.delay;
  times[2] = 7 / srv->data.delay;
  times[3] = 7 / srv->data.delay;
  times[4] = 1 / srv->data.delay;
  times[5] = 7 / srv->data.delay;
  times[6] = 7 / srv->data.delay;
  times[7] = 7 / srv->data.delay;
  times[8] = 7 / srv->data.delay;
  times[9] = 300 / srv->data.delay;
  times[10] = 42 / srv->data.delay;
  times[11] = 0;
  return (times);
}

int	get_time_by_func(t_server *srv, char *cmd)
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

double	calculate_elapse(struct timeb *before, struct timeb *after)
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
  int	ret;

  ret = 0;
  printf("Checking timer\n");
  waiting_list(srv);
  printf("Cheking in progress\n");
  ret = task_list(srv);
  printf("Checking done\n");
  return (ret);
}
