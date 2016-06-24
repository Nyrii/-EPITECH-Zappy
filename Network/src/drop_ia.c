/*
** drop_ia.c for drop_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:49:24 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 23 23:05:34 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static int	drop_item(t_server *server, t_player *p, int index)
{
  char		*answ;
  char		buf[4096];

  answ = NULL;
  if (server->data.map[p->y] && server->data.map[p->y][p->x]
      && p->inventory[index] > 0)
    {
      server->data.map[p->y][p->x][index] += 1;
      p->inventory[index] -= 1;
      if ((answ = bct(server->data.map, p->y, p->x)) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      if (pdr(server, p, index) == -1 || pin_ia(server, p) == -1
	  || send_all_graphics(server, buf) == -1)
	return (-1);
      free(answ);
      if (store_answer_p(p, OK, 0) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
    }
  else if (store_answer_p(p, KO, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}

int		drop_ia(t_server *server, t_player *player)
{
  int		i;

  i = -1;
  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (server->params == NULL)
    {
      if (store_answer_p(player, KO, 0) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
      return (0);
    }
  while (++i < NONE)
    {
      if (strcmp(server->params, server->data.strings_resources[i]) == 0)
	return (drop_item(server, player, i));
    }
  if (store_answer_p(player, KO, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}
