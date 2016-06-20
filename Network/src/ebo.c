/*
** ebo.c for ebo in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 12:10:44 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 12:11:12 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		ebo(t_server *server, t_egg *egg)
{
  char		buffer[20];

  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, EBO, egg->id) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}
