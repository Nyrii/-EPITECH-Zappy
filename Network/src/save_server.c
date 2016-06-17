/*
** save_server.c for save_server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:30:09 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 17 16:32:15 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

t_server		*save_server(t_server *new_server)
{
  static t_server	*server = NULL;

  if (new_server != NULL)
    server = new_server;
  return (server);
}
