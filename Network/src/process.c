/*
** process.c for process in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 16:00:48 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 16:24:23 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

int		manage_commands(t_server *server, const char *command)
{
  int		i;

  i = 0;
  while (server->cmd_tab[i] != NULL)
    {
      if (strcmp(server->cmd_tab[i], command) == 0)
	return (server->cmd_func[i](server));
      ++i;
    }
  return (0);
}
