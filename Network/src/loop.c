/*
** loop.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:04:41 2016 Kevin Empociello
** Last update Thu Jun  9 01:09:35 2016 Kevin Empociello
*/

#include "server.h"

int	loop_server(t_server *srv)
{
  while (1)
    {
      printf("Loop server\n");
      FD_ZERO(&srv->rdfs);
      FD_SET(srv->sock, &srv->rdfs);
      set_all_clients(srv);
      if (select(srv->max + 1, &srv->rdfs, NULL, NULL, NULL) == -1)
        return (error("Select failed\n"));
      check_sockets_loop(srv);
    }
  return (0);
}
