/*
** sst.c for sst in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 18:11:22 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 18:17:51 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

int		sst(t_server *server, t_client *graphic)
{
  char		*parameter;
  int		new_delay;

  if (!server->params || !(parameter = strtok(server->params, " \t"))
      || (new_delay = atoi(parameter)) <= 0)
    return (sbp(graphic));
  server->data.delay = new_delay;
  return (sgt(server, graphic));
}
