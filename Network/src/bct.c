/*
** bct.c for bct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 13:17:30 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 16:48:41 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"

static char 	*fill_bct(char *answer, int ***map,
			  int const *pos, int i)
{
  int		inc;
  int		k;
  char		buffer[24];

  inc = 0;
  k = 0;
  if (memset(buffer, 0, 24) == NULL
      || snprintf(buffer, 24, " %d %d", pos[0], pos[1]) == -1)
    return (fprintf(stderr, ERR_MEMSET), NULL);
  while (buffer[inc])
    answer[i++] = buffer[inc++];
  while (map[pos[0]][pos[1]][k] != -1)
    {
      answer[i++] = ' ';
      inc = 0;
      if (memset(buffer, 0, 24) == NULL
	  || snprintf(buffer, 24, "%d", map[pos[0]][pos[1]][k]) == -1)
	return (NULL);
      ++k;
      while (buffer[inc])
	answer[i++] = buffer[inc++];
    }
  answer[i] = '\0';
  return (answer);
}

char		*bct(int ***map, int const y, int const x)
{
  char		*answer;
  char		*function;
  int		i;
  int		pos[2];

  i = 0;
  if ((answer = malloc(150 * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
  function = "bct";
  while (function[i])
    {
      answer[i] = function[i];
      ++i;
    }
  if (map && map[y] && map[y][x])
    {
      pos[0] = y;
      pos[1] = x;
      return (fill_bct(answer, map, pos, i));
    }
  answer[i] = '\0';
  return (answer);
}

int		bct_on_tile(t_server *server, t_client *graphic)
{
  (void)server;
  (void)graphic;
  return (0);
}
