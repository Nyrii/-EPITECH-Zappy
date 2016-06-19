/*
** drop_ia.c for drop_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:49:24 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 13:58:57 2016 Nyrandone Noboud-Inpeng
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
      || snprintf(buffer, 40, PGT, player->id, index) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}

static int	drop_item(t_server *server, t_player *player, int index)
{
  int		x;
  int		y;
  char		*bct_answer;

  x = player->x;
  y = player->y;
  bct_answer = NULL;
  if (server->data.map[y] && server->data.map[y][x]
      && player->inventory[index] > 0)
    {
      server->data.map[y][x][index] += 1;
      player->inventory[index] -= 1;
      if ((bct_answer = bct(server->data.map, y, x)) == NULL)
	return (-1);
      if (pdr(server, player, index) == -1 || pin_ia(server, player) == -1
	  || send_all_graphics(server, bct_answer) == -1)
	return (-1);
      free(bct_answer);
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
