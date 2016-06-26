/*
** pic.c for pic in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:22:55 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 14:02:57 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static char	*store_pic_answer(t_player *player, char *buf,
				  t_list tmp, int *len)
{
  unsigned int	i;
  t_player	*p;
  char		*answer;

  i = -1;
  if ((answer = malloc((50 + list_get_size(tmp) * 45) + 1)) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
  answer[(*len)] = '\0';
  if ((answer = strcat(answer, buf)) == NULL || (*len = strlen(answer)) == -1)
    return (fprintf(stderr, ERR_STRCAT), NULL);
  while (++i < list_get_size(tmp))
    {
      if ((p = list_get_elem_at_position(tmp, i)) != NULL
	  && p->sock != player->sock)
	{
	  answer[(*len)++] = ' ';
	  answer[(*len)] = '\0';
	  if (memset(buf, 0, 40) == NULL || snprintf(buf, 40, "%d", p->id) == -1)
	    return (fprintf(stderr, ERR_MEMSET), NULL);
	  if ((answer = strcat(answer, buf)) == NULL)
	    return (fprintf(stderr, ERR_STRCAT), NULL);
	  *len = strlen(answer);
	}
    }
  return (answer);
}

int		pic(t_server *server, t_player *player)
{
  t_list	tmp;
  char		buffer[50];
  int		len;
  char		*answer;

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if ((tmp = get_players_at_pos(&server->data, player->y,
				player->x)) == NULL)
    return (fprintf(stderr, ERR_PLAYER), -1);
  if (memset(buffer, 0, 50) == NULL
      || snprintf(buffer, 50, PIC,
		  player->x, player->y, player->level, player->id) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  len = 0;
  if ((answer = store_pic_answer(player, buffer, tmp, &len)) == NULL)
    return (-1);
  answer[len++] = '\n';
  answer[len] = '\0';
  send_all_graphics(server, answer);
  free_nodes_only(tmp);
  return (0);
}
