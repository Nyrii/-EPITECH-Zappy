/*
** process.c for process in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 16:00:48 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 16:13:59 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	manage_ko(t_client *cl)
{
  if (store_answer_c(cl, strdup(KO), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  cl->off = 1;
  return (0);
}

int		manage_commands_spe(t_server *server,
				    t_player *player, const char *command)
{
  if (strcmp(command, "fork") == 0)
    return (fork_ia(server, player));
  else if (strcmp(command, "incantation") == 0)
    {
      if (incantation_ia(server, player) == 1)
	return (0);
      return (1);
    }
  return (0);
}

int		manage_commands_ia(t_server *server,
				   t_player *player, const char *command)
{
  int		i;
  int		ret;

  i = -1;
  if (list_get_size(player->queue_tasks) >= 10)
    return (0);
  while (server->cmd_tab_ia[++i] != NULL)
    {
      if (strcmp(server->cmd_tab_ia[i], command) == 0)
	{
	  if ((ret = manage_commands_spe(server, player, command)) != 0)
	    return (ret);
	  if (list_add_elem_at_back(&player->queue_tasks,
				    new_task(server, player)) == FALSE)
	    return (-1);
	  return (0);
	}
    }
  server->cmd ? free(server->cmd) : 0;
  server->params ? free(server->params) : 0;
  server->cmd = NULL;
  server->params = NULL;
  if (store_answer_p(player, strdup(KO), 0) == -1)
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
      return (remove_client_from_queue(srv, cl));
    }
  else if ((t = get_team_by_name(srv, command)) != NULL &&
	   list_get_size(t->players) < (unsigned int)t->max_players)
    {
      if ((p = new_player(srv, t, cl)) == NULL ||
	  list_add_elem_at_back(&t->players, p) == FALSE ||
	  list_add_elem_at_back(&srv->all_players, p) == FALSE ||
	  generate_food(srv) == -1)
	return (-1);
      else if (handle_new_player(srv, t, p) == -1)
        return (-1);
      return (remove_client_from_queue(srv, cl));
    }
  return (manage_ko(cl));
}
