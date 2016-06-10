/*
** see_ia_calculs.c for see_ia_calculs in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 23:13:47 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 10 23:23:09 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void		determine_minus_x(t_server *server, t_player *player,
				  int *x, int stage)
{
  int		tmp;

  *x = player->x;
  if ((*x) - stage < 0)
    {
      tmp = -1;
      while (++tmp < stage)
	{
	  --(*x);
	  *x = *x < 0 ? server->data.world_x - 1 : (int)*x;
	}
    }
  else
    (*x) -= stage;
}

void		determine_minus_y(t_server *server, t_player *player,
				  int *y, int stage)
{
  int		tmp;

  *y = player->y;
  if ((*y) - stage < 0)
    {
      tmp = -1;
      while (++tmp < stage)
	{
	  --(*y);
	  *y = *y < 0 ? server->data.world_y - 1 : (int)*y;
	}
    }
  else
    (*y) -= stage;
}

void		determine_plus_x(t_server *server, t_player *player,
				 int *x, int stage)
{
  int		tmp;

  *x = player->x;
  if ((*x) + stage >= server->data.world_x)
    {
      tmp = -1;
      while (++tmp < stage)
	{
	  ++(*x);
	  *x = *x >= server->data.world_x ? 0 : (int)*x;
	}
    }
  else
    (*x) += stage;
}

void		determine_plus_y(t_server *server, t_player *player,
				 int *y, int stage)
{
  int		tmp;

  *y = player->y;
  if ((*y) + stage >= server->data.world_y)
    {
      tmp = -1;
      while (++tmp < stage)
	{
	  ++(*y);
	  *y = *y >= server->data.world_y ? 0 : (int)*y;
	}
    }
  else
    (*y) += stage;
}
