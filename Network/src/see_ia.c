/*r
** see_ia.c for see_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:49:54 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 20:25:50 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "enum.h"

static char	*see_top(t_server *server, t_player *player,
			 int stage, int len)
{
  int		i;
  int		pos[2];
  char		*answer;

  answer = NULL;
  while (++stage < player->level + 1)
    {
      determine_minus_x(server, player, &pos[1], stage);
      determine_minus_y(server, player, &pos[0], stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  pos[1] >= server->data.world_x ? (pos[1] = 0) : 0;
	  if (see_ia_resources(&answer, server, pos, &len) == -1)
	    return (NULL);
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len++] = ',' : 0;
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len] = '\0' : 0;
	  ++i;
	  ++pos[1];
	}
    }
  answer[len++] = '}';
  answer[len] = '\0';
  return (answer);
}

static char	*see_right(t_server *server, t_player *player,
			   int stage, int len)
{
  int		i;
  int		pos[2];
  char		*answer;

  answer = NULL;
  while (++stage < player->level + 1)
    {
      determine_plus_x(server, player, &pos[1], stage);
      determine_minus_y(server, player, &pos[0], stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  pos[0] >= server->data.world_y ? (pos[0] = 0) : 0;
	  if (see_ia_resources(&answer, server, pos, &len) == -1)
	    return (NULL);
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len++] = ',' : 0;
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len] = '\0' : 0;
	  ++i;
	  ++pos[0];
	}
    }
  answer[len++] = '}';
  answer[len] = '\0';
  return (answer);
}

static char	*see_bottom(t_server *server, t_player *player,
			    int stage, int len)
{
  int		i;
  int		pos[2];
  char		*answer;

  answer = NULL;
  while (++stage < player->level + 1)
    {
      determine_plus_x(server, player, &pos[1], stage);
      determine_plus_y(server, player, &pos[0], stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  pos[1] < 0 ? (pos[1] = server->data.world_x - 1) : 0;
	  if (see_ia_resources(&answer, server, pos, &len) == -1)
	    return (NULL);
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len++] = ',' : 0;
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len] = '\0' : 0;
	  ++i;
	  --pos[1];
	}
    }
  answer[len++] = '}';
  answer[len] = '\0';
  return (answer);
}

static char	*see_left(t_server *server, t_player *player,
			  int stage, int len)
{
  int		i;
  int		pos[2];
  char		*answer;

  answer = NULL;
  while (++stage < player->level + 1)
    {
      determine_minus_x(server, player, &pos[1], stage);
      determine_plus_y(server, player, &pos[0], stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  pos[0] < 0 ? (pos[0] = server->data.world_y - 1) : 0;
	  if (see_ia_resources(&answer, server, pos, &len) == -1)
	    return (NULL);
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len++] = ',' : 0;
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len] = '\0' : 0;
	  ++i;
	  --pos[0];
	}
    }
  answer[len++] = '}';
  answer[len] = '\0';
  return (answer);
}

int		see_ia(t_server *server, t_player *player)
{
  char		*answer;

  if (player->orientation == TOP)
    answer = see_top(server, player, -1, 0);
  else if (player->orientation == RIGHT)
    answer = see_right(server, player, -1, 0);
  else if (player->orientation == BOTTOM)
    answer = see_bottom(server, player, -1, 0);
  else
    answer = see_left(server, player, -1, 0);
  if (answer == NULL)
    return (-1);
  return (0);
}
