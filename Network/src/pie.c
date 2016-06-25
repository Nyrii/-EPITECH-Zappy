/*
** pie.c for pie in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:24:01 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:51:27 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pie(t_server *server, t_player *player,
		    int const has_elevation_happened)
{
  char		buffer[40];

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (has_elevation_happened)
    {
      if (memset(buffer, 0, 40) == NULL
	  || snprintf(buffer, 40, PIE,
		      player->x, player->y, 1) == -1)
	return (fprintf(stderr, ERR_MEMSET), -1);
      return (send_all_graphics(server, strdup(buffer)));
    }
  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, PIE,
		  player->x, player->y, 0) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  if (send_all_graphics(server, strdup(buffer)) == -1)
    return (-1);
  return (-2);
}
