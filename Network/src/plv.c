/*
** plv.c for plv in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:03:28 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:17:39 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		plv_ia(t_server *server, t_player *player)
{
  char		buffer[40];

  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, PLV,
		  player->id, player->level) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}

int		plv(t_server *server, t_client *graphic)
{
  char		*parameter;
  int		id;
  t_player	*player;
  char		buffer[40];

  if (!server || !graphic || !server->params
      || !(parameter = strtok(server->params, " \t")))
    return (sbp(graphic));
  id = atoi(parameter);
  if ((player = get_player_by_id(server, id)) == NULL)
    return (sbp(graphic));
  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, PLV,
		  player->id, player->level) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  if (store_answer_c(graphic, buffer, 0) == -1)
    {
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (0);
}
