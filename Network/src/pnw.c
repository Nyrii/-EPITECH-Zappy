/*
** pnw.c for pnw in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 17:10:28 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:13:40 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		pnw(t_server *server, t_player *player)
{
  char		buffer[4096];
  int		orientation;
  t_team	*player_team;

  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  orientation = player->orientation == TOP ? 1 :
      player->orientation == RIGHT ? 2 : player->orientation == BOTTOM ? 3 : 4;
  if ((player_team = get_team_by_player(server, player)) == NULL)
    {
      fprintf(stderr, ERR_TEAM);
      return (-1);
    }
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, PNW, player->id, player->x, player->y,
		  orientation, player->level, player_team->name) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}
