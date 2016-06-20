/*
** enw.c for enw in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:28:23 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 15:28:40 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

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
