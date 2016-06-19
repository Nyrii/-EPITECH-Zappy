/*
** incantation_ia.c for incantation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:11 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 17:43:04 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static int	pie(t_server *server, t_player *player)
{
  char		buffer[40];
  int		pos[2];

  pos[0] = player->y;
  pos[1] = player->x;
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    {
      if (memset(buffer, 0, 40) == NULL
	  || snprintf(buffer, 40, PIE,
		      player->x, player->y, 1) == -1)
	return (fprintf(stderr, ERR_MEMSET), -1);
      return (send_all_graphics(server, buffer));
    }
  if (memset(buffer, 0, 40) == NULL
	  || snprintf(buffer, 40, PIE,
		      player->x, player->y, 0) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  if (send_all_graphics(server, buffer) == -1)
    return (-1);
  return (-2);
}

char		*store_pic_answer(t_player *player, char *buf,
				  t_list tmp, int *len)
{
  int		inc;
  unsigned int	i;
  t_player	*p;
  char		*answer;

  i = -1;
  inc = 0;
  if ((answer = malloc(((*len) + list_get_size(tmp) * 14) + 1)) == NULL)
    return (fprintf(stderr, ERR_MALLOC), NULL);
  while (buf[inc])
    answer[(*len)++] = buf[inc++];
  while (++i < list_get_size(tmp))
    {
      if ((p = list_get_elem_at_position(tmp, i)) != NULL
	  && p->sock != player->sock)
	{
	  inc = 0;
	  answer[(*len)++] = ' ';
	  if (memset(buf, 0, 40) == NULL || snprintf(buf, 40, "%d", p->id) == -1)
	    return (fprintf(stderr, ERR_MEMSET), NULL);
	  while (buf[inc])
	    answer[(*len)++] = buf[inc++];
	}
    }
  return (answer);
}

static int	pic(t_server *server, t_player *player)
{
  t_list	tmp;
  char		buffer[50];
  int		len;
  char		*answer;

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
  answer[len++] = '\r';
  answer[len++] = '\n';
  answer[len] = '\0';
  free(answer);
  return (0);
}

static int	manage_level_player(t_server *server,
				    t_player *player, int *pos)
{
  int		i;
  int		ret_value;

  i = -1;
  if ((ret_value = pie(server, player)) == 0)
    {
      player->level += 1;
      while (server->data.map[pos[0]][pos[1]][++i] != -1)
	server->data.map[pos[0]][pos[1]][i]
      -= server->data.resources[player->level][i];
    }
  else if (ret_value == -1)
    return (-1);
  return (0);
}

int		incantation_ia(t_server *server, t_player *player)
{
  int		pos[2];

  pos[0] = player->y;
  pos[1] = player->x;
  if (is_elevation_legit(&server->data, player->level, pos) == 0)
    {
      if (dprintf(player->sock, ELEVATION_IN_PROGRESS) == -1
	  || pic(server, player) == -1
	  || manage_level_player(server, player, pos) == -1)
	return (-1);
      if (player->level == 8)
	{
	  if (dprintf(player->sock, CURRENT_LEVEL, 8) == -1)
	    return (-1);
	  return (2);
	}
      if (dprintf(player->sock, CURRENT_LEVEL, player->level) == -1
	  || plv_ia(server, player) == -1)
	return (-1);
      return (0);
    }
  if (dprintf(player->sock, KO) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
