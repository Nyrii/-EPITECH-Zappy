/*
** free_all.c for free all in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:26:36 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 18:04:11 2016 Nyrandone Noboud-Inpeng
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
  return (free_map(server->data.map, ret_value));
}
