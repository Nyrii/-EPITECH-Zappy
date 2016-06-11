/*
** process.c for process in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 16:00:48 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 10 17:30:08 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

int		manage_commands_ia(t_server *server,
				   t_player *player, const char *command)
{
  int		i;

  i = 0;
  while (server->cmd_tab_ia[i] != NULL)
    {
      if (strcmp(server->cmd_tab_ia[i], command) == 0)
	return (server->cmd_ptr_ia[i](server, player));
      ++i;
    }
  return (0);
}

int		manage_commands_graphic(t_server *server,
				   t_client *graphic, const char *command)
{
  int		i;

  i = 0;
  while (server->cmd_tab_graphic[i] != NULL)
    {
      if (strcmp(server->cmd_tab_graphic[i], command) == 0)
	return (server->cmd_ptr_graphic[i](server, graphic));
      ++i;
    }
  return (0);
}
