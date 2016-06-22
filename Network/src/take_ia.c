/*
** take_ia.c for take_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:48:52 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 19:04:20 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	take_food(t_server *server, t_player *player)
{
  int		x;
  int		y;
  char		*answ;
  char		buf[4096];

  x = player->x;
  y = player->y;
  answ = NULL;
  if (server->data.map[y] && server->data.map[y][x]
      && server->data.map[y][x][0] > 0)
    {
      server->data.map[y][x][0] -= 1;
      player->inventory[0] += 1;
      if ((answ = bct(server->data.map, y, x)) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      if (send_all_graphics(server, buf) == -1)
	return (-1);
      free(answ);
    }
  else if (store_answer_p(player, KO, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}

static int	take_stone(t_server *server, t_player *player, int index)
{
  int		x;
  int		y;
  char		*answ;
  char		buf[4096];

  x = player->x;
  y = player->y;
  answ = NULL;
  if (server->data.map[y] && server->data.map[y][x]
      && server->data.map[y][x][index] > 0)
    {
      server->data.map[y][x][index] -= 1;
      player->inventory[index] += 1;
      if ((answ = bct(server->data.map, y, x)) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      if (pgt(server, player, index) == -1 || pin_ia(server, player) == -1
	  || send_all_graphics(server, buf) == -1)
	return (-1);
      free(answ);
    }
  else if (store_answer_p(player, KO, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (store_answer_p(player, OK, 0));
}

int		take_ia(t_server *server, t_player *player)
{
  int		i;

  i = -1;
  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if (server->params == NULL)
    {
      if (store_answer_p(player, KO, 0) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  if (strcmp(server->params, "nourriture") == 0)
    return (take_food(server, player));
  while (++i < NONE)
    {
      if (strcmp(server->params, server->data.strings_resources[i]) == 0)
	return (take_stone(server, player, i));
    }
  if (store_answer_p(player, KO, 0) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
