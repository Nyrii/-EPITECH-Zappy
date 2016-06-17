/*
** init_perimeter.c for init_perimeter in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 14:29:09 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 17 14:44:40 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void	init_perimeter_top(t_data data, t_player *player, int *pos)
{
  pos[0] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[1] = player->x;
  pos[2] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[3] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[4] = player->y;
  pos[5] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[6] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[7] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[8] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[9] = player->x;
  pos[10] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[11] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[12] = player->y;
  pos[13] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[14] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[15] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[16] = -1;
}

void	init_perimeter_right(t_data data, t_player *player, int *pos)
{
  pos[0] = player->y;
  pos[1] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[2] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[3] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[4] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[5] = player->x;
  pos[6] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[7] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[8] = player->y;
  pos[9] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[10] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[11] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[12] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[13] = player->x;
  pos[14] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[15] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[16] = -1;
}

void	init_perimeter_bottom(t_data data, t_player *player, int *pos)
{
  pos[0] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[1] = player->x;
  pos[2] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[3] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[4] = player->y;
  pos[5] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[6] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[7] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[8] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[9] = player->x;
  pos[10] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[11] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[12] = player->y;
  pos[13] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[14] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[15] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[16] = -1;
}

void	init_perimeter_left(t_data data, t_player *player, int *pos)
{
  pos[0] = player->y;
  pos[1] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[2] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[3] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[4] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[5] = player->x;
  pos[6] = player->y + 1 >= data.world_y ? 0 : player->y + 1;
  pos[7] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[8] = player->y;
  pos[9] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[10] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[11] = player->x + 1 >= data.world_x ? 0 : player->x + 1;
  pos[12] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[13] = player->x;
  pos[14] = player->y - 1 < 0 ? data.world_y - 1 : player->y - 1;
  pos[15] = player->x - 1 < 0 ? data.world_x - 1 : player->x - 1;
  pos[16] = -1;
}

void		call_init_perimeter(t_data data, t_player *player,
				    int *perimeter)
{
  int		i;
  int		code[5];
  void		(*func[5])(t_data, t_player *, int *);

  code[0] = TOP;
  code[1] = RIGHT;
  code[2] = BOTTOM;
  code[3] = LEFT;
  code[4] = -1;
  func[0] = &init_perimeter_top;
  func[1] = &init_perimeter_right;
  func[2] = &init_perimeter_bottom;
  func[3] = &init_perimeter_left;
  func[4] = NULL;
  i = -1;
  while (code[++i] != -1)
    {
      if (player->orientation == code[i])
	{
	  func[i](data, player, perimeter);
	  return ;
	}
    }
}
