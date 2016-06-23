/*
** process.c for process in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 16:00:48 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:20:39 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		manage_commands_ia(t_server *server,
				   t_player *player, const char *command)
{
  int		i;

  i = 0;
  while (server->cmd_tab_ia[i] != NULL)
    {
      if (strcmp(server->cmd_tab_ia[i], command) == 0)
	{
	  if (list_add_elem_at_back(&player->queue_tasks,
				    new_task(server, player)) == FALSE)
	    return (-1);
	  return (0);
	}
      ++i;
    }
  if (store_answer_p(player, KO, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
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
  return (suc(graphic));
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
      remove_client_from_queue(srv, cl);
    }
  else if ((t = get_team_by_name(srv, command)) != NULL &&
	   list_get_size(t->players) < (unsigned int) t->max_players)
    {
      // check si y a encore de la place
      if ((p = new_player(srv, t, cl)) == NULL ||
	  list_add_elem_at_back(&t->players, p) == FALSE ||
	  list_add_elem_at_back(&srv->all_players, p) == FALSE ||
	 generate_food(&srv->data) == -1)
	return (-1);
      else
	if (handle_new_player(srv, t, p) == -1)
	    return (-1);
	  remove_client_from_queue(srv, cl);
    }
  else
    {
	  printf("je store KO\n");
      if (store_answer_c(cl, KO, 0) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
	  cl->off = 1;
    }
  return (0);
}
