/*
** loop.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:04:41 2016 Kevin Empociello
** Last update Wed Jun 22 17:47:18 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

static int		process(t_server *srv, int const index)
{
  int			ret_value;

  if (check_and_read_clients(&srv->rdfs, srv->queue_clients) == -1 ||
      check_and_read_clients(&srv->rdfs, srv->graphic_clients) == -1 ||
      check_and_read_players(&srv->rdfs, srv->all_players) == -1 ||
      ((ret_value = check_sockets_loop(srv, index)) == -1) ||
      check_and_write_clients(&srv->wfd, srv->queue_clients) == -1 ||
      check_and_write_clients(&srv->wfd, srv->graphic_clients) == -1 ||
      check_and_write_players(&srv->wfd, srv->all_players) == -1)
    return (-1);
  if (ret_value == 2)
    return (ret_value);
  return (0);
}

int			loop_server(t_server *srv)
{
  struct timeval 	tv;
  int			ret_value;
  int			i;

  while (1)
    {
      i = -1;
      while (srv->socks[++i] != -1)
	{
	  tv.tv_sec = 0;
	  tv.tv_usec = 200;
	  save_server(srv, 1);
	  FD_ZERO(&srv->rdfs);
	  FD_ZERO(&srv->wfd);
	  FD_SET(srv->socks[i], &srv->rdfs);
          FD_SET(srv->socks[i], &srv->wfd);
	  set_all_clients(srv, -1);
	  if (select(srv->max + 1, &srv->rdfs, &srv->wfd, NULL, &tv) == -1)
	    return (error("Select failed\n"));
	  if ((ret_value = process(srv, i)) != 0)
	    return (ret_value);
	  if (check_timer(srv) == -1 || check_disconnect(srv) == -1)
	    return (-1);
	}
    }
  return (0);
}
