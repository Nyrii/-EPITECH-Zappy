/*
** loop.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:04:41 2016 Kevin Empociello
** Last update Tue Jun 21 17:50:06 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int			loop_server(t_server *srv)
{
  struct timeval 	tv;
  int			ret_value;
  int			i;

  printf("Loop server\n");
  while (1)
    {
      i = -1;
      while (srv->socks[++i] != -1)
	{
	  tv.tv_sec = 0;
	  tv.tv_usec = 100;
	  save_server(srv, 1);
	  FD_ZERO(&srv->rdfs);
	  FD_SET(srv->socks[i], &srv->rdfs);
	  set_all_clients(srv);
	  if (select(srv->max + 1, &srv->rdfs, NULL, NULL, &tv) == -1)
	    return (error("Select failed\n"));
	  if ((ret_value = check_sockets_loop(srv, i)) == -1 || ret_value == 2)
	    return (ret_value);
	  check_timer(srv);
	}
    }
  return (0);
}
