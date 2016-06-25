/*
** free_all.c for free all in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:26:36 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:06:33 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

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
	free_player_buffers(tmp->value);
      free(tmp->value);
      tmp->value = NULL;
      free(tmp);
      tmp = NULL;
    }
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
  free_clients(server->all_players, 0, 0);
  return (0);
}
