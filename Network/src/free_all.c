/*
** free_all.c for free all in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:26:36 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 23 15:38:49 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		free_all(t_server *server, int const ret_value)
{
  if (!server)
    return (ret_value);
  free_list(server->data.eggs, ret_value);
  free_teams(server->data.teams, ret_value);
  free_list(server->queue_clients, ret_value);
  free_list(server->graphic_clients, ret_value);
  free_list(server->all_players, ret_value);
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
  free_list(server->queue_clients, 0);
  free_list(server->graphic_clients, 0);
  free_list(server->all_players, 0);
  return (0);
}
