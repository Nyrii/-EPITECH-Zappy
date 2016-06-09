/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Thu Jun  9 11:08:19 2016 Nyrandone Noboud-Inpeng
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"

// function temporaire
static void read_client(t_server *srv, t_player *cl)
{
  char		buffer[512];
  int		n;

  (void)srv;
  n = 0;
  memset(buffer, 0, 512);
  if (cl && (n = recv(cl->sock, buffer, 512, 0)) > 0)
    {
      printf("[%s]\n", buffer);
    }
}

static int		check_socket(int sock, t_server *srv)
{
  t_player		*p;
  unsigned int		i;

  i = -1;
  if (FD_ISSET(sock, &srv->rdfs))
    {
      if (sock == srv->sock)
	{
	  printf("New player\n");
	  p = new_player(srv);
	  FD_SET(p->sock, &srv->rdfs);
	  list_add_elem_at_back(&srv->players, p);
	}
      else
	while (++i < list_get_size(srv->players))
	  if ((p = list_get_elem_at_position(srv->players, i)) != NULL)
	    if (p->sock == sock)
	      {
		read_client(srv, p);
		return (1);
	      }
      //return (client_talking(srv, list_get_elem_at_position(srv->clients, i)));
      return (1);
    }
  return (0);
}

void		check_sockets_loop(t_server *srv)
{
  int		i;

  i = 0;
  while (i <= srv->max)
    {
      if (check_socket(i, srv) == 1)
	return ;
      i++;
    }
}

void		set_all_clients(t_server *srv)
{
  t_player		*p;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->players))
    {
      if ((p = list_get_elem_at_position(srv->players, i)) != NULL)
	       FD_SET(p->sock, &srv->rdfs);
      i++;
    }
}
