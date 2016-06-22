/*
** inventory_ia.c for inventory in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:48:17 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:11:49 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

static int	get_answer(t_server *server, t_player *player,
			   char **answer, int i)
{
  int		tmp;
  int		n;
  char		buffer[13];

  tmp = 0;
  (*answer)[i] = '\0';
  while (tmp < NONE)
    {
      n = 0;
      if (i == 0)
        (*answer)[i++] = '{';
      while (server->data.strings_resources[tmp][n])
	(*answer)[i++] = server->data.strings_resources[tmp][n++];
      if (memset(buffer, 0, 13) == NULL
	  || snprintf(buffer, 13, " %d", player->inventory[tmp]) == -1)
	return (fprintf(stderr, ERR_MEMSET), -1);
      n = 0;
      while (buffer[n])
	(*answer)[i++] = buffer[n++];
      tmp + 1 != NONE ? (*answer)[i++] = ',' : 0;
      tmp + 1 != NONE ? (*answer)[i++] = ' ' : 0;
      ++tmp;
    }
  return (i);
}

int		inventory_ia(t_server *server, t_player *player)
{
  char		*answer;
  int		i;
  char		buffer[4096];

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if ((answer = malloc((21 * 7 + 20) * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  if ((i = get_answer(server, player, &answer, 0)) == -1)
    return (-1);
  answer[i++] = '}';
  answer[i] = '\0';
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, MSG, answer) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  if (store_answer_p(player, buffer, 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (0);
}
