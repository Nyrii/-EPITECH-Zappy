/*
** pin.c for pin in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:08:33 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 14:14:49 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static char 	*fill_pin(char *answer, t_player *player, int *i)
{
  int		inc;
  int		k;
  char		buffer[36];

  inc = 0;
  k = 0;
  if (memset(buffer, 0, 36) == NULL
      || snprintf(buffer, 36, PIN,
		  player->id, player->y, player->x) == -1)
    return (fprintf(stderr, ERR_MEMSET), NULL);
  while (buffer[inc])
    answer[(*i)++] = buffer[inc++];
  while (k < NONE)
    {
      answer[(*i)++] = ' ';
      inc = 0;
      if (memset(buffer, 0, 36) == NULL
	  || snprintf(buffer, 36, "%d", player->inventory[k]) == -1)
	return (NULL);
      ++k;
      while (buffer[inc])
	answer[(*i)++] = buffer[inc++];
    }
  return (answer);
}

int		pin_ia(t_server *server, t_player *player)
{
  char		*answer;
  int		i;

  i = 0;
  if ((answer = malloc(190 * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  if ((answer = fill_pin(answer, player, &i)) == NULL)
    return (-1);
  answer[i++] = '\r';
  answer[i++] = '\n';
  answer[i] = '\0';
  return (send_all_graphics(server, answer));
}

int		pin(t_server *server, t_client *graphic)
{
  (void)server;
  (void)graphic;
  return (0);
}
