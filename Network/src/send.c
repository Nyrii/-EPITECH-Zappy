/*
** send.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sun Jun 19 13:39:45 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

int		send_all_players(t_server *srv, t_player *p, const char *msg)
{
  t_player	*tmp;
  unsigned int	i;

  i = 0;
  if (srv == NULL || msg == NULL)
    return (-1);
  while (i < list_get_size(srv->all_players))
    {
      if ((tmp = list_get_elem_at_position(srv->all_players, i)) != NULL)
	{
	  if (p == NULL && dprintf(tmp->sock, "%s", msg) == -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	  else if (tmp != p && dprintf(tmp->sock, "%s", msg) != -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	}
      i++;
    }
  return (0);
}

int		send_all_graphics(t_server *srv, const char *msg)
{
  t_client	*tmp;
  unsigned int	i;

  i = 0;
  if (srv == NULL || msg == NULL)
    return (-1);
  while (i < list_get_size(srv->graphic_clients))
    {
      if ((tmp = list_get_elem_at_position(srv->graphic_clients, i)) != NULL)
	{
	  if (dprintf(tmp->sock, "%s", msg) == -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	}
      i++;
    }
  return (0);
}
