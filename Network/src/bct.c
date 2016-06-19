/*
** bct.c for bct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 13:17:30 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 17:01:42 2016 Nyrandone Noboud-Inpeng
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
      || snprintf(buffer, 24, " %d %d", pos[1], pos[0]) == -1)
    return (fprintf(stderr, ERR_MEMSET), NULL);
  while (buffer[inc])
    answer[i++] = buffer[inc++];
  while (map[pos[0]][pos[1]][k] != -1)
    {
      answer[i++] = ' ';
      inc = 0;
      if (memset(buffer, 0, 12) == NULL
	  || snprintf(buffer, 12, "%d", map[pos[0]][pos[1]][k]) == -1)
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
  if ((answer = malloc(160 * sizeof(char))) == NULL)
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
  char		*parameters[2];
  int		pos[2];
  char		*answer;

  (void)graphic;
  if (!server->params
      || !(parameters[0] = strtok(server->params, " \t"))
      || !(parameters[1] = strtok(NULL, " \t")))
    return (fprintf(stderr, ERR_WRONG_ARGS), 0); // KO to graphical client;
  pos[0] = atoi(parameters[0]);
  pos[1] = atoi(parameters[1]);
  if (pos[0] >= 0 && pos[0] < server->data.world_y
      && pos[1] >= 0 && pos[1] < server->data.world_y)
    {
      if ((answer = bct(server->data.map, pos[0], pos[1])) == NULL)
	return (-1);
      printf("%s\n", answer);
      // Answer to graphical client;
      return (0);
    }
  fprintf(stderr, ERR_WRONG_ARGS); // KO to graphical client;
  return (-1);
}
