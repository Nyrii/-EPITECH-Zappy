/*
** welcome.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Sat Jun 11 19:03:36 2016 Kevin Empociello
** Last update Wed Jun 22 18:28:15 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int		handle_new_player(t_server *srv, t_team *t, t_player *p)
{
  char		buffer[4096];

  if (srv == NULL || p == NULL)
    return (-1);
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, WELCOME_NB_PLAYERS,
		  t->max_players - list_get_size(t->players)) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (store_answer_p(p, buffer, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, WELCOME_SIZE_MAP,
		  srv->data.world_x, srv->data.world_y) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (store_answer_p(p, buffer, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  if (pnw(srv, p) == -1)
    return (-1);
  return (0);
}

int		handle_new_graphic(t_server *srv, t_client *cl)
{
  if (msz(srv, cl) == -1 || sgt(srv, cl) == -1 || mct(srv, cl) == -1 ||
      tna(srv, cl) == -1)
    return (-1);
  return (0);
}

int		handle_new_client(t_server *srv, int const index)
{
  t_client	*c;

  if ((c = new_client(srv, index)) == NULL)
    return (-1);
  FD_SET(c->sock, &srv->rdfs);
  if (list_add_elem_at_back(&srv->queue_clients, c) == FALSE)
    return (-1);
  if (store_answer_c(c, WELCOME, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}
