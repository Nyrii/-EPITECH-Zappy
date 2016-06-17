/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_zappy/serv/src
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 11:35:34 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 17 18:39:36 2016 Nyrandone Noboud-Inpeng
*/

#include <time.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include "server.h"

void		free_before_leaving()
{
  t_server	*server;

  server = save_server(NULL, 0);
  if (server)
    {
      if (close_all_clients(server) == -1)
	exit(-1);
      free_all(server, 0);
    }
  exit(0);
}

int		run_zappy(t_server *srv)
{
  init_code(srv->cmd_tab_ia, srv->cmd_tab_graphic);
  init_ptrfunc(srv->cmd_ptr_ia, srv->cmd_ptr_graphic);
  if ((srv->sock = init_server(SOMAXCONN, srv->data.port)) == -1)
    return (-1);
  srv->max = srv->sock;
  srv->queue_clients = NULL;
  srv->graphic_clients = NULL;
  srv->all_players = NULL;
  if (generate_map(&srv->data, 0, 0, 0) == -1)
    return (-1);
  if (loop_server(srv) == -1)
    {
      close_all_clients(srv);
      return (free_all(srv, -1));
    }
  if (close_all_clients(srv) == -1)
    return (-1);
  free_all(srv, 0);
  save_server(NULL, 1);
  return (run_zappy(NULL));
}

int		main(int argc, char **argv)
{
  t_server	server;

  srand(time(NULL));
  signal(SIGINT, free_before_leaving);
  if (get_opt(argc, argv, &server) != -1)
    {
      if (run_zappy(&server) == -1)
	return (-1);
    }
  return (0);
}
