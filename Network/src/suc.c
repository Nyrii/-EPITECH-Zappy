/*
** suc.c for suc in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 12:52:39 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:15:38 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		suc(t_client *graphic)
{
  char		buffer[10];

  if (!graphic)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 10) == NULL
      || snprintf(buffer, 10, SUC) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (dprintf(graphic->sock, "%s", buffer) == -1)
    {
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (0);
}
