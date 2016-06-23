/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_zappy/serv/src
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 11:35:34 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 23 15:15:48 2016 Nyrandone Noboud-Inpeng
*/

#include <time.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
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

static int	activate_all_ports(t_server *server)
{
  int		i;
  int		sock;

  i = -1;
  server->max = -1;
  server->socks = NULL;
  while (server->data.ports[++i] != -1)
    {
      if ((sock = init_server(SOMAXCONN, server->data.ports[i])) == -1)
	return (-1);
      if (store_socks(&server->socks, sock) == -1)
	return (-1);
      if (server->max < sock)
	server->max = sock;
    }
  if (server->max == -1)
    return (-1);
  return (0);
}

int		run_zappy(t_server *template)
{
  t_server	*server;

  server = template;
  server->queue_clients = NULL;
  server->graphic_clients = NULL;
  server->all_players = NULL;
  if (loop_server(server) == -1)
    {
      close_all_clients(server);
      return (free_all(server, -1));
    }
  if (close_all_clients(server) == -1)
    return (-1);
  free_before_reset(server);
  save_server(template, 1);
  return (run_zappy(template));
}

int		main(int argc, char **argv)
{
  t_server	server;

  srand(time(NULL));
  signal(SIGINT, free_before_leaving);
  if (get_opt(argc, argv, &server) != -1 &&
      (server.data.timers = init_timer_tasks(&server)) != NULL)
    {
      init_code(server.cmd_tab_ia, server.cmd_tab_graphic);
      init_ptrfunc(server.cmd_ptr_ia, server.cmd_ptr_graphic);
      if (activate_all_ports(&server) == -1)
	return (-1);
      if (generate_map(&server.data, 0, 0, 0) == -2)
	return (-1);
      save_server(&server, 1);
      if (run_zappy(&server) == -1)
	return (-1);
    }
  return (0);
}
