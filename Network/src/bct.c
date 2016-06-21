/*
** bct.c for bct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 13:17:30 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:13:06 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static char 	*fill_bct(char *answer, int ***map,
			  int const *pos, int i)
{
  int		inc;
  int		k;
  char		buffer[30];

  inc = 0;
  k = 0;
  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, "bct %d %d", pos[1], pos[0]) == -1)
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
  int		i;
  int		pos[2];

  i = 0;
  if ((answer = malloc(160 * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
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
  char		*answ;
  char		buf[4096];

  if (!server || !server->params || !graphic
      || !(parameters[0] = strtok(server->params, " \t"))
      || !(parameters[1] = strtok(NULL, " \t")))
    return (sbp(graphic));
  pos[0] = atoi(parameters[1]);
  pos[1] = atoi(parameters[0]);
  if (pos[0] >= 0 && pos[0] < server->data.world_y
      && pos[1] >= 0 && pos[1] < server->data.world_x)
    {
      if ((answ = bct(server->data.map, pos[0], pos[1])) == NULL)
	return (-1);
      if (memset(buf, 0, 4096) == NULL || snprintf(buf, 4096, MSG, answ) == -1)
        return (fprintf(stderr, ERR_PRINTF), -1);
      if (dprintf(graphic->sock, "%s", buf) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  return (sbp(graphic));
}
