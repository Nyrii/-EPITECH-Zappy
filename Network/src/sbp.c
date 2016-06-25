/*
** sbp.c for sbp in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 17:50:46 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 15:03:39 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		sbp(t_client *graphic)
{
  char		buffer[10];

  if (!graphic)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 10) == NULL
      || snprintf(buffer, 10, SBP) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (store_answer_c(graphic, buffer, 0) == -1)
    return (-1);
  return (0);
}
