/*
** plv.c for plv in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:03:28 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 14:01:39 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		plv(t_server *server, t_client *graphic)
{
  char		*parameter;
  int		id;
  t_player	*player;
  char		buffer[4096];

  (void)graphic;
  if (!server->params || !(parameter = strtok(server->params, " \t")))
    return (fprintf(stderr, ERR_WRONG_ARGS), 0); // Réponse client graphique #KO;
  id = atoi(parameter);
  if ((player = get_player_by_id(server, id)) == NULL)
    return (fprintf(stderr, ERR_PLAYER), 0); // Réponse client graphique KO;
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, PLV,
		  player->id, player->level) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  // Répondre au client graphique avec le buffer
  return (0);
}
