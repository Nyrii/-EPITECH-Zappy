/*
** welcome.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Sat Jun 11 19:03:36 2016 Kevin Empociello
** Last update Sat Jun 11 19:24:12 2016 Kevin Empociello
*/

#include "errors.h"
#include "server.h"

int		handle_new_player(t_server *srv, t_team *t, t_player *p)
{
  if (srv == NULL || p == NULL)
    return (-1);
  if (dprintf(p->sock, "%d\r\n",
	      t->max_players - list_get_size(t->players)) == -1 ||
      dprintf(p->sock, "%d %d\r\n", srv->data.world_x, srv->data.world_y) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}

int		handle_new_graphic(t_server *srv, t_client *cl)
{
  if (msz(srv, cl) == -1 || sgt(srv, cl) == -1 || mct(srv, cl) == -1 ||
      tna(srv, cl) == -1)
    return (-1);
  return (0);
}

// catch return of dprintf <= 0 .. ?
int		handle_new_client(t_server *srv)
{
  t_client	*c;

  c = new_client(srv);
  FD_SET(c->sock, &srv->rdfs);
  list_add_elem_at_back(&srv->queue_clients, c);
  if (dprintf(c->sock, "BIENVENUE\r\n") == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
