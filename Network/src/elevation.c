/*
** elevation.c for elevation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:55:46 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 15:57:05 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		is_elevation_legit(t_data *data, int elevation,
				   int *pos, t_list tmp)
{
  int		i;
  int		count;

  i = -1;
  count = 0;
  if (!data->map || !data->map[pos[0]]
      || !data->map[pos[0]][pos[1]] || !data->resources)
    return (-1);
  while (data->map[pos[0]][pos[1]][++i] != -1)
    if (i != FOOD
	&& data->resources[elevation][i] != data->map[pos[0]][pos[1]][i])
      return (-1);
  if ((tmp = get_players_at_pos(data, pos[0], pos[1])) == NULL)
    return (-1);
      count = list_get_size(tmp);
  if (count < data->required_players[elevation])
    return (tmp = NULL, -1);
  return (0);
}
