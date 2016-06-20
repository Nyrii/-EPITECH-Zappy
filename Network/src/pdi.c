/*
** pdi.c for pdi in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 19:02:24 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 19:17:56 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pdi(t_server *server, t_player *player)
{
  char		buffer[30];

  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, PDI, player->id) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}
