/*
** pbc.c for pbc in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:34:58 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 12:19:28 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pbc(t_server *server, t_player *player)
{
  t_task	*current;
  char		*answer;
  char		buffer[25];
  int		i;

  i = 0;
  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if ((current = list_get_elem_at_position(player->queue_tasks, 0)) == NULL)
    return (-1);
  if ((answer = malloc(25 + strlen(current->params))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  if (memset(buffer, 0, 25) == NULL
      || snprintf(buffer, 25, PBC, player->id) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  answer[i] = '\0';
  if ((answer = strcat(answer, buffer)) == NULL
      || (answer = strcat(answer, current->params)) == NULL)
    return (fprintf(stderr, ERR_STRCAT), -1);
  i = strlen(answer);
  answer[i++] = '\n';
  answer[i] = '\0';
  if (send_all_graphics(server, answer) == -1)
    return (-1);
  return (0);
}
