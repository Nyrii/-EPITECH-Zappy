/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_zappy/serv/src
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 11:35:34 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 21:32:05 2016 Nyrandone Noboud-Inpeng
*/

#include <time.h>
#include <sys/socket.h>
#include "server.h"

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
  loop_server(srv);
  return (0);
}

int		main(int argc, char **argv)
{
  t_server	server;

  srand(time(NULL));
  if (get_opt(argc, argv, &server.data) != -1)
    {
      if (run_zappy(&server) == -1)
	return (-1);
    }
  //free_tab(server.data.teams, 0);
  return (0);
}
