/*
** ebo.c for ebo in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 12:10:44 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:49:47 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		ebo(t_server *server, t_egg *egg)
{
  char		buffer[20];

  if (!server || !egg)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, EBO, egg->id) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, strdup(buffer)));
}
