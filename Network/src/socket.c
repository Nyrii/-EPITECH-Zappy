/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Mon Jun 13 12:17:46 2016 Nyrandone Noboud-Inpeng
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"

// temporary
static void	dump_lists(t_server *srv)
{
  t_team	*t;
  unsigned int	i;

  i = 0;
  printf("Clients in queue : %d\n", list_get_size(srv->queue_clients));
  printf("Graphic clients : %d\n", list_get_size(srv->graphic_clients));
  printf("Total players : %d\n", list_get_size(srv->all_players));
  while (i < list_get_size(srv->data.teams))
    {
      if ((t = list_get_elem_at_position(srv->data.teams, i)) != NULL)
	printf("Players team n°%d : %d\n", i, list_get_size(t->players));
      i++;
    }
}

static int	handle_client(t_server *srv, void *tmp, int type)
{
  int		tmp_sock;
  char		buffer[512];
  int		n;

  n = 0;
  if (tmp == NULL)
    return (-1);
  if (type == 0 || type == 1)
    tmp_sock = ((t_client *)tmp)->sock;
  else if (type == 2)
    tmp_sock = ((t_player *)tmp)->sock;
  memset(buffer, 0, 512);
  if ((n = recv(tmp_sock, buffer, 512, 0)) > 0)
    {
      if ((srv->cmd = parse_cmd(srv, epur_bf(buffer))) == NULL)
	return (-1);
      if (type == 1)
	manage_commands_graphic(srv, (t_client *)tmp, srv->cmd);
      else if (type == 2)
	manage_commands_ia(srv, (t_player *)tmp, srv->cmd);
      else
	manage_auth(srv, (t_client *)tmp, srv->cmd);
      printf("[%s]\n", srv->cmd);
    }
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
	return (handle_client(srv, c, 0), 1);
  i = -1;
  while (++i < list_get_size(srv->graphic_clients))
    if ((c = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
      if (c->sock == sock)
	return (handle_client(srv, c, 1), 1);
  i = -1;
  while (++i < list_get_size(srv->all_players))
    if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
      if (p->sock == sock)
	return (handle_client(srv, p, 2), 1);
  return (0);
}

static int		check_socket(int sock, t_server *srv)
{
  if (FD_ISSET(sock, &srv->rdfs))
    {
      if (sock == srv->sock)
	{
	  printf("New client\n");
	  handle_new_client(srv);
	}
      else
	check_lists(sock, srv);
      dump_lists(srv);
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

void			set_all_clients(t_server *srv)
{
  t_player		*p;
  t_client		*c;
  unsigned int		i;

  c = NULL;
  i = -1;
  while (++i < list_get_size(srv->queue_clients))
    if ((c = list_get_elem_at_position(srv->queue_clients, i)) != NULL)
      FD_SET(c->sock, &srv->rdfs);
  i = -1;
  while (++i < list_get_size(srv->graphic_clients))
    if ((c = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
      FD_SET(c->sock, &srv->rdfs);
  i = -1;
  while (++i < list_get_size(srv->all_players))
    if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
      FD_SET(p->sock, &srv->rdfs);
}
