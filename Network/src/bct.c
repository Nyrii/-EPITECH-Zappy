/*
** bct.c for bct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 13:17:30 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 02:03:45 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static char	*fill_bct(char *answer, int ***map,
			  int const *pos, int i)
{
  int		k;
  char		buffer[30];

  k = 0;
  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, "bct %d %d", pos[1], pos[0]) == -1)
    return (fprintf(stderr, ERR_MEMSET), NULL);
  answer[i] = '\0';
  if ((answer = strcat(answer, buffer)) == NULL)
    return (fprintf(stderr, ERR_STRCAT), NULL);
  i = strlen(answer);
  while (map[pos[0]][pos[1]][k] != -1)
    {
      answer[i++] = ' ';
      if (memset(buffer, 0, 12) == NULL
	  || snprintf(buffer, 12, "%d", map[pos[0]][pos[1]][k]) == -1)
	return (NULL);
      ++k;
      answer[i] = '\0';
      if ((answer = strcat(answer, buffer)) == NULL)
	return (fprintf(stderr, ERR_STRCAT), NULL);
      i = strlen(answer);
    }
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
      free(answ);
      if (store_answer_c(graphic, strdup(buf), 0) == -1)
	return (fprintf(stderr, ERR_BUFFER), -1);
      return (0);
    }
  return (sbp(graphic));
}

int			bct_ia(t_server *server, int const y, int const x)
{
  char			*tmp;
  char			buffer[4096];

  if ((tmp = bct(server->data.map, y, x)) == NULL)
    return (-1);
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, MSG, tmp) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  send_all_graphics(server, strdup(buffer));
  free(tmp);
  return (0);
}
