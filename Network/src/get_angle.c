/*
** get_angle.c for get_angle in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun 16 13:58:31 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 16 16:47:13 2016 Nyrandone Noboud-Inpeng
*/

#include <math.h>
#include "server.h"

double		get_angle(t_player *player, int const dest_y, int const dest_x,
			  double *rad)
{
  double	angle;

  angle = atan2((1.0 * player->y - 1.0 * dest_y),
		(1.0 * player->x - 1.0 * dest_x));
  if (angle >= -0.000001 && angle <= 0.000001
	    && player->x < dest_x)
    angle = angle + M_PI;
  if (angle < 0.0)
    angle += (2 * M_PI);
  *rad = angle;
  angle = (angle * 180) / M_PI;
  return (angle);
}

int		get_best_tile_by_angle(double const angle, double const rad,
				       t_player *target)
{
  int		orientation;
  double	template_angles[9];
  int		i;

  orientation = target->orientation == RIGHT ? 0
      : target->orientation == TOP ? 2 : -1;
  orientation = target->orientation == LEFT ? 4
      : target->orientation == BOTTOM ? 6 : (int)orientation;
  template_angles[0] = 22.5;
  template_angles[1] = 67.5;
  template_angles[2] = 112.5;
  template_angles[3] = 157.5;
  template_angles[4] = 202.5;
  template_angles[5] = 247.5;
  template_angles[6] = 292.5;
  template_angles[7] = 337.5;
  if (rad == 0.0)
    return (-1);
  i = -1;
  if (angle <= 22.5 || angle >= 337.5)
    return ((1 + 8 - orientation) % 8);
  while (template_angles[++i] != 337.5)
    if (angle >= template_angles[i] && angle < template_angles[i + 1])
      return (((8 - i) + 8 - orientation) % 8);
  return (-1);
}
