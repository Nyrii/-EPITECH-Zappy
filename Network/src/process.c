/*
** process.c for process in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 16:00:48 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 13:24:23 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"

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

int		manage_auth(t_server *srv, t_client *cl, const char *command)
{
  t_player	*p;
  t_team	*t;

  if (strcmp(command, "GRAPHIC") == 0)
    {
      if (list_add_elem_at_back(&srv->graphic_clients, cl) == FALSE ||
	  handle_new_graphic(srv, cl) == -1)
	return (-1);
    }
  else if ((t = get_team_by_name(srv, command)) != NULL &&
	   list_get_size(t->players) < (unsigned int) t->max_players)
    {
      // check si y a encore de la place
      if ((p = new_player(srv, t, cl)) == NULL ||
	  list_add_elem_at_back(&t->players, p) == FALSE ||
	  list_add_elem_at_back(&srv->all_players, p) == FALSE)
	return (-1);
      else
	if (handle_new_player(srv, t, p) == -1)
	    return (-1);
    }
  else
    {
      dprintf(cl->sock, KO);
      close(cl->sock);
    }
  remove_client_from_queue(srv, cl);
  return (0);
}
