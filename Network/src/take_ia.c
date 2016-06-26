/*
** take_ia.c for take_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:48:52 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 10:47:42 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	take_item(t_server *s, t_player *player, int index)
{
  char		*answ;
  char		buf[4096];

  answ = NULL;
  if (s->data.map[player->y] && s->data.map[player->y][player->x]
      && s->data.map[player->y][player->x][index] > 0)
    {
      printf("index = %d\n", index);
      s->data.map[player->y][player->x][index] -= 1;
      player->inventory[index] += 1;
      if ((answ = bct(s->data.map, player->y, player->x)) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      if (pgt(s, player, index) == -1 || pin_ia(s, player) == -1
	  || send_all_graphics(s, strdup(buf)) == -1)
	return (-1);
      free(answ);
      return (store_answer_p(player, strdup(OK), 0));
    }
  else if (store_answer_p(player, strdup(KO), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}

int		take_ia(t_server *server, t_player *player)
{
  int		i;

  i = -1;
  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if (server->params == NULL)
    {
      if (store_answer_p(player, strdup(KO), 0) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  while (++i < NONE)
    {
      if (strcmp(server->params, server->data.strings_resources[i]) == 0)
	return (take_item(server, player, i));
    }
  if (store_answer_p(player, strdup(KO), 0) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
