/*
** pfk.c for pfk in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:27:13 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:11:21 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pfk(t_server *server, t_player *player)
{
  char		buffer[30];

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, PFK, player->id) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}
