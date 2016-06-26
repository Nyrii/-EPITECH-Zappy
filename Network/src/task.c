/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sun Jun 26 16:14:58 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		free_tasks(t_task *t, int ret_value)
{
  t->cmd ? free(t->cmd) : 0;
  t->params ? free(t->params) : 0;
  t->real ? free(t->real) : 0;
  t->cmd = NULL;
  t->params = NULL;
  t->real = NULL;
  free(t);
  return (ret_value);
}

int		player_spe_action(t_server *srv, t_player *p, t_task *t)
{
  int		ret_value;

  if (strcmp(t->cmd, "fork") == 0)
    {
      if (store_answer_p(p, strdup(OK), 0) == -1)
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

int		player_tasks(t_server *srv, t_player *p, int index)
{
  struct timeb	now;
  t_task	*t;
  t_task	*t_nxt;
  int		ret;

  ftime(&now);
  if (list_get_size(p->queue_tasks) >= 1 &&
      (t = list_get_elem_at_position(p->queue_tasks, 0)) != NULL)
    {
      strcmp("quit", t->cmd) == 0 ? (index = 12) : 0;
      if (index == 12 || ((index = get_time_by_func(srv, t->cmd)) != -1 &&
			  calculate_elapse(&t->timer.val, &now) >= srv->data.timers[index]))
	{
          if (strcmp(t->cmd, "fork") == 0 || strcmp(t->cmd, "incantation") == 0)
	    ret = player_spe_action(srv, p, t);
	  else
	    ret = srv->cmd_ptr_ia[index](srv, p);
	  list_del_elem_at_position(&p->queue_tasks, 0);
          if (list_get_size(p->queue_tasks) > 0)
            if ((t_nxt = list_get_elem_at_position(p->queue_tasks, 0)) != NULL)
	      ftime(&t_nxt->timer.val);
	  return (free_tasks(t, ret));
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
	  if ((ret = player_tasks(srv, p, -1)) == -1 || ret == 2)
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
  if ((t->cmd = strdup(srv->cmd)) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
  t->params = NULL;
  if (srv->params != NULL && (t->params = strdup(srv->params)) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
  t->real = NULL;
  if (list_get_size(p->queue_tasks) == 0)
    ftime(&t->timer.val);
  return (t);
}
