/*
** drop_ia.c for drop_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:49:24 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 17:05:14 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static int	pdr(t_server *server, t_player *player, int index)
{
  char		buffer[40];

  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, PDR, player->id, index) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}

static int	drop_item(t_server *server, t_player *player, int index)
{
  int		x;
  int		y;
  char		*answ;
  char		buf[4096];

  x = player->x;
  y = player->y;
  answ = NULL;
  if (server->data.map[y] && server->data.map[y][x]
      && player->inventory[index] > 0)
    {
      server->data.map[y][x][index] += 1;
      player->inventory[index] -= 1;
      if ((answ = bct(server->data.map, y, x)) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      if (pdr(server, player, index) == -1 || pin_ia(server, player) == -1
	  || send_all_graphics(server, buf) == -1)
	return (-1);
      free(answ);
    }
  else if (dprintf(player->sock, KO) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}

int		drop_ia(t_server *server, t_player *player)
{
  int		i;

  i = -1;
  if (server->params == NULL)
    {
      if (dprintf(player->sock, KO) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  while (++i < NONE)
    {
      if (strcmp(server->params, server->data.strings_resources[i]) == 0)
	return (drop_item(server, player, i));
    }
  if (dprintf(player->sock, KO) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
