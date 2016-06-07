/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_zappy/serv/src
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 11:35:34 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 16:25:36 2016 nekfeu
*/

#include "server.h"

void		run_zappy(t_server *srv)
{
  init_code(srv->cmd_tab);
  init_ptrfunc(srv->cmd_ptr);
}

int		main(int argc, char **argv)
{
  t_server	server;

  if (get_opt(argc, argv, &server.data) != -1)
    run_zappy(&server);
  //free_tab(server.data.teams, 0);
  return (0);
}
