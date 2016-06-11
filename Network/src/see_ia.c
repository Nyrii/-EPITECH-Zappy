/*r
** see_ia.c for see_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:49:54 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 19:07:45 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "enum.h"

static int	see_top(t_server *server, t_player *player, int stage)
{
  int		i;
  int		pos[2];
  char		*answer;
  int		len;

  // pos[0] = player->y;
  // pos[1] = player->x;
  // printf("Position x = %d, position y = %d\n", player->x, player->y);
  answer = NULL;
  len = 0;
  while (stage < player->level + 1)
    {
      determine_minus_x(server, player, &pos[1], stage);
      determine_minus_y(server, player, &pos[0], stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  pos[1] >= server->data.world_x ? (pos[1] = 0) : 0;
	  if (see_ia_resources(&answer, server, pos, &len) == -1)
	    return (-1);
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len++] = ',' : 0;
	  i + 1 != stage * 2 + 1  || stage == 0 ? answer[len] = '\0' : 0;
	  //   printf("pos x = %d, pos y = %d\n", pos[1], pos[0]);
	  // stocker les ressources.
	  ++i;
	  ++pos[1];
	}
      // printf("------\n");
      ++stage;
    }
  answer[len++] = '}'; // {
  answer[len] = '\0';
  printf("ANSWER = %s\n", answer);
  return (0);
}

static int	see_right(t_server *server, t_player *player, int stage)
{
  int		i;
  int		x;
  int		y;

  // y = player->y;
  // x = player->x;
  // printf("Position x = %d, position y = %d\n", player->x, player->y);
  while (stage < player->level + 1)
    {
      determine_plus_x(server, player, &x, stage);
      determine_minus_y(server, player, &y, stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  y >= server->data.world_y ? (y = 0) : 0;
	  // printf("pos x = %d, pos y = %d\n", x, y);
	  // stocker les ressources.;
	  ++i;
	  ++y;
	}
      // printf("------\n");
      ++stage;
    }
  return (0);
}

static int	see_bottom(t_server *server, t_player *player, int stage)
{
  int		i;
  int		x;
  int		y;

  // y = player->y;
  // x = player->x;
  // printf("Position x = %d, position y = %d\n", player->x, player->y);
  while (stage < player->level + 1)
    {
      determine_plus_x(server, player, &x, stage);
      determine_plus_y(server, player, &y, stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  x < 0 ? (x = server->data.world_x - 1) : 0;
	  // printf("pos x = %d, pos y = %d\n", x, y);
	  // stocker les ressources.
	  ++i;
	  --x;
	}
      // printf("------\n");
      ++stage;
    }
  return (0);
}

static int	see_left(t_server *server, t_player *player, int stage)
{
  int		i;
  int		x;
  int		y;

  // y = player->y;
  // x = player->x;
  // printf("Position x = %d, position y = %d\n", player->x, player->y);
  while (stage < player->level + 1)
    {
      determine_minus_x(server, player, &x, stage);
      determine_plus_y(server, player, &y, stage);
      i = 0;
      while (i < stage * 2 + 1)
	{
	  y < 0 ? (y = server->data.world_y - 1) : 0;
	  //   printf("pos x = %d, pos y = %d\n", x, y);
	  // stocker les ressources.
	  ++i;
	  --y;
	}
      // printf("------\n");
      ++stage;
    }
  return (0);
}

int		see_ia(t_server *server, t_player *player)
{
  if (player->orientation == TOP)
    return (see_top(server, player, 0));
  else if (player->orientation == RIGHT)
    return (see_right(server, player, 0));
  else if (player->orientation == BOTTOM)
    return (see_bottom(server, player, 0));
  return (see_left(server, player, 0));
}
