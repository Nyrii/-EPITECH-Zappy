/*
** free_all.c for free all in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:26:36 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 21:55:32 2016 Kevin Empociello
*/

#include "server.h"

void		free_nodes_only(t_list list)
{
  t_list	tmp;
  unsigned int	i;

  if (list == NULL)
    return ;
  i = -1;
  while (++i < list_get_size(list))
    {
      tmp = list;
      list = list->next;
      free(tmp);
    }
}

void		free_player_structure(t_player *player)
{
  unsigned int	i;
  t_task	*task;

  i = -1;
  if (player == NULL)
    return ;
  while (++i < list_get_size(player->queue_tasks))
    {
      if ((task = list_get_elem_at_position(player->queue_tasks, i)) != NULL)
	{
	  if (task->cmd)
	    free(task->cmd);
	  if (task->params)
	    free(task->params);
	  if (task->real)
	    free(task->real);
	  task->cmd = NULL;
	  task->params = NULL;
	  task->real = NULL;
	  free(task);
	}
    }
}

int		free_clients(t_list list, int const type, int const ret_value)
{
  unsigned int	i;
  t_list	tmp;

  if (!list)
    return (ret_value);
  i = -1;
  while (++i < list_get_size(list))
    {
      tmp = list;
      list = list->next;
      if (type == 0)
	free_client_buffers(tmp->value);
      else
	{
	  free_player_buffers(tmp->value);
	  free_player_structure(tmp->value);
	}
      free(tmp->value);
      tmp->value = NULL;
      free(tmp);
      tmp = NULL;
    }
  free(list);
  list = NULL;
  return (ret_value);
}

int		free_all(t_server *server, int const ret_value)
{
  if (!server)
    return (ret_value);
  free_list(server->data.eggs, ret_value);
  free_teams(server->data.teams, ret_value);
  free_clients(server->queue_clients, 0, ret_value);
  free_clients(server->graphic_clients, 0, ret_value);
  free_clients(server->all_players, 1, ret_value);
  free_int_tab(server->data.required_players, ret_value);
  free_int_tab(server->data.ports, ret_value);
  free_int_tab(server->socks, ret_value);
  free_double_int_tab(server->data.resources, ret_value);
  free(server->data.timers);
  return (free_map(server->data.map, ret_value));
}

int		free_before_reset(t_server *server)
{
  if (!server)
    return (0);
  if (remove_players_from_team(server) == -1)
    return (-1);
  free_list(server->data.eggs, 0);
  free_clients(server->queue_clients, 0, 0);
  free_clients(server->graphic_clients, 0, 0);
  free_clients(server->all_players, 1, 0);
  return (0);
}
