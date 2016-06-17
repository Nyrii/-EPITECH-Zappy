/*
** loop.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:04:41 2016 Kevin Empociello
** Last update Fri Jun 17 18:18:06 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int	loop_server(t_server *srv)
{
  int	ret_value;

  while (1)
    {
      save_server(srv);
      printf("Loop server\n");
      FD_ZERO(&srv->rdfs);
      FD_SET(srv->sock, &srv->rdfs);
      set_all_clients(srv);
      if (select(srv->max + 1, &srv->rdfs, NULL, NULL, NULL) == -1)
        return (error("Select failed\n"));
      if ((ret_value = check_sockets_loop(srv)) == -1 || ret_value == 2)
	return (ret_value);
    }
  return (0);
}
