/*
** welcome.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Sat Jun 11 19:03:36 2016 Kevin Empociello
** Last update Sat Jun 11 19:24:12 2016 Kevin Empociello
*/

#include "server.h"

// catch return of dprintf <= 0 .. ?
void		handle_new_client(t_server *srv)
{
  t_client	*c;

  c = new_client(srv);
  FD_SET(c->sock, &srv->rdfs);
  list_add_elem_at_back(&srv->queue_clients, c);
  dprintf(c->sock, "BIENVENUE\r\n");
}
