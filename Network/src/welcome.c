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

int		handle_new_graphic(t_server *srv, t_client *cl)
{
  msz(srv, cl);
  sgt(srv, cl);
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
