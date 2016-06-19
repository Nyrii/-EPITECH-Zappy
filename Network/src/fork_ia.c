/*
** fork_ia.c for fork_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:29 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 16:11:40 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		enw(t_server *server, t_egg *egg)
{
  char		buffer[80];

  if (memset(buffer, 0, 80) == NULL
      || snprintf(buffer, 80, ENW,
		  egg->id, egg->player_id, egg->x, egg->y) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}

static int	pfk(t_server *server, t_player *player)
{
  char		buffer[30];

  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, PFK, player->id) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}

int		fork_ia(t_server *server, t_player *player)
{
  t_egg		*egg;

  if ((egg = new_egg(server, player)) == NULL)
    return (-1);
  egg->player_id = player->id;
  if (list_add_elem_at_back(&server->data.eggs, egg) == FALSE)
    {
      fprintf(stderr, ERR_MALLOC);
      return (-1);
    }
  // Timer;
  if (dprintf(player->sock, OK) == -1)
    {
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (pfk(server, player));
}
