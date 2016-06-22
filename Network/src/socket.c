/*
** socket.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Wed Jun 22 17:44:05 2016 Nyrandone Noboud-Inpeng
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"
#include "errors.h"

// temporary
void	dump_lists(t_server *srv)
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
  int		ret;
  t_bmanager	*tmp_cmd;

  if (tmp == NULL)
    return (-1);
  if (type == 0 || type == 1)
    {
      tmp_cmd = ((t_client *)tmp)->buffs.cmds;
      while (tmp_cmd)
	{
	  if ((srv->cmd = parse_cmd(srv, epur_bf(tmp_cmd->struc))) == NULL)
	    return (-1);
	  if (type == 1)
	    ret = manage_commands_graphic(srv, (t_client *)tmp, srv->cmd);
	  else if (type == 0)
	    ret = manage_auth(srv, (t_client *)tmp, srv->cmd);
	  if (ret == -1 || ret == 2)
            return (ret);
	  tmp_cmd = tmp_cmd->next;
	}
    }
  else if (type == 2)
    {
      tmp_cmd = ((t_player *)tmp)->buffs.cmds;
      while (tmp_cmd)
	{
	  if ((srv->cmd = parse_cmd(srv, epur_bf(tmp_cmd->struc))) == NULL)
	    return (-1);
	  ret = manage_commands_ia(srv, (t_player *)tmp, srv->cmd);
	  if (ret == -1 || ret == 2)
	    return (ret);
	  tmp_cmd = tmp_cmd->next;
	}
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

static int		check_socket(int sock, t_server *srv, int index)
{
  int			ret_value;

  if (FD_ISSET(sock, &srv->rdfs))
    {
      if (sock == srv->socks[index])
	{
	  handle_new_client(srv, index);
	}
      else
	if ((ret_value = check_lists(sock, srv)) == -1 || ret_value == 2)
	  return (ret_value);
      //dump_lists(srv);
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
      if ((ret_value = check_socket(i, srv, index)) == -1 || ret_value == 1)
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
        c->buffs.out.start != c->buffs.out.end ? FD_SET(c->sock, &srv->wfd) : 0;
      }
  i = -1;
  while (++i < list_get_size(srv->graphic_clients))
    if ((c = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
      {
	FD_SET(c->sock, &srv->rdfs);
        c->buffs.out.start != c->buffs.out.end ? FD_SET(c->sock, &srv->wfd) : 0;
      }
  i = -1;
  while (++i < list_get_size(srv->all_players))
    if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
      {
        FD_SET(p->sock, &srv->rdfs);
        p->buffs.out.start != p->buffs.out.end ? FD_SET(p->sock, &srv->wfd) : 0;
      }
}
