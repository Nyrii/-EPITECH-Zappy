/*
** disconnect.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Thu Jun 23 13:17:22 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

static int	disconnect_players(t_server *srv)
{
  unsigned int	i;
  t_player	*p;

  i = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL &&
	  p->off == 1)
	{
	  if (close(p->sock) == -1)
	    return (fprintf(stderr, ERR_CLOSE), -1);
	  if (list_del_elem_at_position(&srv->all_players, i) == FALSE)
	    return (-1);
	  return (0);
	}
      i++;
    }
  return (0);
}

static int	disconnect_graphics(t_server *srv)
{
  unsigned int	i;
  t_client	*cl;

  i = 0;
  while (i < list_get_size(srv->graphic_clients))
    {
      if ((cl = list_get_elem_at_position(srv->graphic_clients, i)) != NULL &&
	  cl->off == 1)
	{
	  if (close(cl->sock) == -1)
	    return (fprintf(stderr, ERR_CLOSE), -1);
	  if (list_del_elem_at_position(&srv->graphic_clients, i) == FALSE)
	    return (-1);
	  return (0);
	}
      i++;
    }
  return (0);
}

static int	disconnect_queue_clients(t_server *srv)
{
  unsigned int	i;
  t_client	*cl;

  i = 0;
  while (i < list_get_size(srv->queue_clients))
    {
      if ((cl = list_get_elem_at_position(srv->queue_clients, i)) != NULL &&
	  cl->off == 1)
	{
	  if (close(cl->sock) == -1)
	    return (fprintf(stderr, ERR_CLOSE), -1);
	  if (list_del_elem_at_position(&srv->queue_clients, i) == FALSE)
	    return (-1);
	  return (0);
	}
      i++;
    }
  return (0);
}

int		check_disconnect(t_server *srv)
{
  if (disconnect_queue_clients(srv) == -1 || disconnect_graphics(srv) == -1 ||
      disconnect_players(srv) == -1)
    return (-1);
  return (0);
}
