/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Fri Jun 17 18:18:58 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

int		player_tasks(t_server *srv, t_player *p)
{
  struct timeb	now;
  int		index;
  t_task	*t;

  index = -1;
  ftime(&now);
  if (list_get_size(p->queue_tasks) >= 1 &&
      (t = list_get_elem_at_position(p->queue_tasks, 0)) != NULL)
    {
      if ((index = get_time_by_func(srv, t->cmd)) != -1 &&
	  calculate_elapse(&t->timer.val, &now) >= srv->data.timers[index])
	{
	  list_del_elem_at_position(&p->queue_tasks, 0);
	  if (list_get_size(p->queue_tasks) > 0)
	    if ((t = list_get_elem_at_position(p->queue_tasks, 0)) != NULL)
		ftime(&t->timer.val);
	  return (srv->cmd_ptr_ia[index](srv, p));
	}
    }
  return (0);
}

int		task_list(t_server *srv)
{
  unsigned int	i;
  int		ret;
  t_player	*p;

  i = 0;
  ret = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
	{
	  if ((ret = player_life(srv, p)) == -1)
		return (ret);
	  if ((ret = player_tasks(srv, p)) == -1 || ret == 2)
	    return (ret);
	}
      i++;
    }
  return (0);
}

t_task		*new_task(t_server *srv, t_player *p)
{
  t_task	*t;

  if ((t = malloc(sizeof(t_task))) == NULL)
    return (NULL);
  t->cmd = strdup(srv->cmd);
  t->params = NULL;
  if (srv->params != NULL)
    t->params = strdup(srv->params);
  t->real = NULL;
  if (list_get_size(p->queue_tasks) == 0)
    ftime(&t->timer.val);
  return (t);
}
