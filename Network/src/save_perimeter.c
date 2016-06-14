/*
** save_perimeter.c for save_perimeter in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun 14 19:12:46 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 14 19:14:41 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void		save_perimeter_top(int *perimeter, int const y, int const x)
{
  perimeter[0] = y - 1;
  perimeter[1] = x;
  perimeter[2] = y - 1;
  perimeter[3] = x - 1;
  perimeter[4] = y;
  perimeter[5] = x - 1;
  perimeter[6] = y + 1;
  perimeter[7] = x - 1;
  perimeter[8] = y + 1;
  perimeter[9] = x;
  perimeter[10] = y + 1;
  perimeter[11] = x + 1;
  perimeter[12] = y;
  perimeter[13] = x + 1;
  perimeter[14] = y - 1;
  perimeter[15] = x + 1;
  perimeter[16] = y;
  perimeter[17] = x;
  perimeter[18] = -1;
}

void		save_perimeter_right(int *perimeter, int const y, int const x)
{
  perimeter[0] = y;
  perimeter[1] = x + 1;
  perimeter[2] = y - 1;
  perimeter[3] = x + 1;
  perimeter[4] = y - 1;
  perimeter[5] = x;
  perimeter[6] = y - 1;
  perimeter[7] = x - 1;
  perimeter[8] = y;
  perimeter[9] = x - 1;
  perimeter[10] = y + 1;
  perimeter[11] = x - 1;
  perimeter[12] = y + 1;
  perimeter[13] = x;
  perimeter[14] = y + 1;
  perimeter[15] = x + 1;
  perimeter[16] = y;
  perimeter[17] = x;
  perimeter[18] = -1;
}

void		save_perimeter_bottom(int *perimeter, int const y, int const x)
{
  perimeter[0] = y + 1;
  perimeter[1] = x;
  perimeter[2] = y + 1;
  perimeter[3] = x + 1;
  perimeter[4] = y;
  perimeter[5] = x + 1;
  perimeter[6] = y - 1;
  perimeter[7] = x + 1;
  perimeter[8] = y - 1;
  perimeter[9] = x;
  perimeter[10] = y - 1;
  perimeter[11] = x - 1;
  perimeter[12] = y;
  perimeter[13] = x - 1;
  perimeter[14] = y + 1;
  perimeter[15] = x - 1;
  perimeter[16] = y;
  perimeter[17] = x;
  perimeter[18] = -1;
}

void		save_perimeter_left(int *perimeter, int const y, int const x)
{
  perimeter[0] = y;
  perimeter[1] = x - 1;
  perimeter[2] = y + 1;
  perimeter[3] = x - 1;
  perimeter[4] = y + 1;
  perimeter[5] = x;
  perimeter[6] = y + 1;
  perimeter[7] = x + 1;
  perimeter[8] = y;
  perimeter[9] = x + 1;
  perimeter[10] = y - 1;
  perimeter[11] = x + 1;
  perimeter[12] = y - 1;
  perimeter[13] = x;
  perimeter[14] = y - 1;
  perimeter[15] = x - 1;
  perimeter[16] = y;
  perimeter[17] = x;
  perimeter[18] = -1;
}

void		save_perimeter(t_player *target, int *tiles,
			       int const y, int const x)
{
  int		i;
  int		code[5];
  void		(*func[5])(int *, int const, int const);

  code[0] = TOP;
  code[1] = RIGHT;
  code[2] = BOTTOM;
  code[3] = LEFT;
  code[4] = -1;
  func[0] = &save_perimeter_top;
  func[1] = &save_perimeter_right;
  func[2] = &save_perimeter_bottom;
  func[3] = &save_perimeter_left;
  func[4] = NULL;
  i = -1;
  while (code[++i] != -1)
    {
      if (target->orientation == code[i])
	{
	  func[i](tiles, y, x);
	  return ;
	}
    }
}
