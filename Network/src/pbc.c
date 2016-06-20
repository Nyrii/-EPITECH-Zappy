/*
** pbc.c for pbc in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:34:58 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 19:54:24 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pbc(t_server *server, t_player *player)
{
  char		*answer;
  char		buffer[25];
  int		i;
  int		n;

  i = 0;
  n = 0;
  if ((answer = malloc(25 + strlen(server->params))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  if (memset(buffer, 0, 25) == NULL
      || snprintf(buffer, 25, PBC, player->id) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  while (buffer[n])
    answer[i++] = buffer[n++];
  n = 0;
  while (server->params[n])
    answer[i++] = server->params[n++];
  answer[i++] = '\n';
  answer[i] = '\0';
  if (send_all_graphics(server, answer) == -1)
    return (-1);
  free(answer);
  return (0);
}
