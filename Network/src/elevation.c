/*
** elevation.c for elevation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:55:46 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  9 22:06:18 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		is_elevation_legit(t_data *data, int elevation, int y, int x)
{
  int		i;

  i = 0;
  if (!data->map || !data->map[y] || !data->map[y][x] || !data->resources)
    return (-1);
  while (data->map[y][x][i] != -1)
    {
      if (data->resources[elevation][i] > data->map[y][x][i])
	return (-1);
      ++i;
    }
  return (0);
}
