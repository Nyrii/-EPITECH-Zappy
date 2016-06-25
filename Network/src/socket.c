/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sat Jun 25 15:02:14 2016 Nyrandone Noboud-Inpeng
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"
#include "errors.h"

static int	handle_client(t_server *srv, void *tmp, int type)
{
  if (tmp == NULL)
    return (-1);
  if (type == 0 || type == 1)
    return (process_auth_and_graphics(srv, tmp, type));
  else if (type == 2)
    return (process_ia(srv, tmp));
  return (0);
}

static int		check_lists(int sock, t_server *srv)
{
  t_player		*p;
  t_client		*c;
  unsigned int		i;

  i = -1;
  p = NULL;
  c = NULL;
  while (++i < list_get_size(srv->queue_clients))
    if ((c = list_get_elem_at_position(srv->queue_clients, i)) != NULL)
      if (c->sock == sock)
	return (handle_client(srv, c, 0));
  i = -1;
  while (++i < list_get_size(srv->graphic_clients))
    if ((c = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
      if (c->sock == sock)
	return (handle_client(srv, c, 1));
  i = -1;
  while (++i < list_get_size(srv->all_players))
    if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
      if (p->sock == sock)
	return (handle_client(srv, p, 2));
  return (0);
}

static int		check_socket(int sock, t_server *srv, int index)
{
  int			ret_value;

  if (FD_ISSET(sock, &srv->rdfs))
    {
      if (sock == srv->socks[index])
	{
	  if (handle_new_client(srv, index) == -1)
	    return (-1);
	}
      else
	if ((ret_value = check_lists(sock, srv)) == -1 || ret_value == 2)
	  return (ret_value);
      return (1);
    }
  return (0);
}

int		check_sockets_loop(t_server *srv, int index)
{
  int		i;
  int		ret_value;

  i = 0;
  while (i <= srv->max)
    {
      if ((ret_value = check_socket(i, srv, index)) != 0)
	return (ret_value);
      i++;
    }
  return (0);
}

void			set_all_clients(t_server *srv, unsigned int i)
{
  t_player		*p;
  t_client		*c;

  c = NULL;
  while (++i < list_get_size(srv->queue_clients))
    if ((c = list_get_elem_at_position(srv->queue_clients, i)) != NULL)
      {
	FD_SET(c->sock, &srv->rdfs);
        c->buff != NULL ? FD_SET(c->sock, &srv->wfd) : 0;
      }
  i = -1;
  while (++i < list_get_size(srv->graphic_clients))
    if ((c = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
      {
	FD_SET(c->sock, &srv->rdfs);
        c->buff != NULL ? FD_SET(c->sock, &srv->wfd) : 0;
      }
  i = -1;
  while (++i < list_get_size(srv->all_players))
    if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
      {
        FD_SET(p->sock, &srv->rdfs);
        p->buff != NULL ? FD_SET(p->sock, &srv->wfd) : 0;
      }
}
