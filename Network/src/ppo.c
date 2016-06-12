/*
** ppo.c for ppo in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:02:42 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 15:10:10 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"

int		ppo_ia(t_server *server, t_player *player)
{
  t_list	tmp;
  char		buffer[80];
  int		orientation;

  orientation = player->orientation == TOP ? 1 :
      player->orientation == RIGHT ? 2 : player->orientation == BOTTOM ? 3 : 4;
  if (memset(buffer, 0, 60) == NULL
      || snprintf(buffer, 60, "ppo %d %d %d %d\r\n",
		  player->id, player->x, player->y, orientation) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  tmp = server->graphic_clients;
  while (tmp != NULL)
    {
      // envoyer la réponse à tous les clients graphiques
      tmp = tmp->next;
    }
  return (0);
}

int		ppo(t_server *server, t_client *graphic)
{
  (void)server;
  (void)graphic;
  return (0);
}
