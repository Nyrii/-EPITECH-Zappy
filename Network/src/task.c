/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sat Jun 25 15:31:03 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		player_spe_action(t_server *srv, t_player *p, t_task *t)
{
  int		ret_value;

  if (strcmp(t->cmd, "fork") == 0)
    {
      if (store_answer_p(p, OK, 0) == -1)
	{
	  fprintf(stderr, ERR_BUFFER);
	  return (-1);
	}
      return (enw(srv, p->fork.egg));
    }
  else if (strcmp(t->cmd, "incantation") == 0)
    {
      if (p->incant.pos == NULL)
	return (0);
      if ((ret_value = incantation_manager(srv, p, p->incant.pos)) != -2)
	return (ret_value);
    }
  return (0);
}

int		player_tasks(t_server *srv, t_player *p)
{
  struct timeb	now;
  int		index;
  t_task	*t;
  t_task	*t_nxt;

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
            if ((t_nxt = list_get_elem_at_position(p->queue_tasks, 0)) != NULL)
	      ftime(&t_nxt->timer.val);
          if (strcmp(t->cmd, "fork") == 0 || strcmp(t->cmd, "incantation") == 0)
            return (player_spe_action(srv, p, t));
          else
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
