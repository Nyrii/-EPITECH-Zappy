/*
** generate_map.c for generate_map in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 20:59:48 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun  8 21:00:24 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"

int			get_resource(int *template)
{
  int			i;

  i = 0;
  if (template == NULL)
    return (-1);
  while (template[i] != -1)
    {
      if (template[i] > 0)
	return (i);
      ++i;
    }
  return (-1);
}

void			generate_base(int *template, int ***map, int x, int y)
{
  int			*tmp;
  int			resource;

  tmp = template;
  while ((resource = get_resource(tmp)) != -1)
    {
      y = 0;
      while (map[y] != NULL)
	{
	  x = 0;
	  while (map[y][x] != NULL)
	    {
	      if (rand() % 3 == 0)
		{
		  map[y][x][resource] += 1;
		  tmp[resource] -= 1;
                  if ((resource = get_resource(tmp)) == -1)
		    return ;
		}
	      ++x;
	    }
	  ++y;
	}
    }
}

static void		generate_tile(t_data *data, int y, int x)
{
  int			resource;
  int			i;

  i = 0;
  while (i < NONE)
    data->map[y][x][i++] = 0;
  data->map[y][x][i] = -1;
  resource = 0;
  while (resource < NONE)
    {
      if ((rand() % 100) < data->percentages[resource])
	data->map[y][x][resource] += 1;
      ++resource;
    }
}

int			generate_map(t_data *data, int x, int y)
{
  int			i;

  i = 0;
  if ((data->map = malloc((data->world_y + 1) * sizeof(int **))) == NULL
      || (data->map[y] = malloc((data->world_x + 1) * sizeof(int *))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  while (x < data->world_x * data->world_y)
    {
      if ((data->map[y][i] = malloc(9 * sizeof(int))) == NULL)
	return (fprintf(stderr, ERR_MALLOC), -1);
      generate_tile(data, y, i);
      ++i;
      ++x;
      x % data->world_x == 0 ? (data->map[y][i] = NULL) : 0;
      x % data->world_x == 0 ? (i = 0) : (int)i;
      x % data->world_x == 0 ? (y += 1) : (int)y;
      if (x % data->world_x == 0 && x + 1 < data->world_x * data->world_y
	  && (!(data->map[y] = malloc((data->world_x + 1) * sizeof(int *)))))
	return (fprintf(stderr, ERR_MALLOC), -1);
    }
  data->map[y] = NULL;
  generate_base(data->resources[0], data->map, 0, 0);
  return (0);
}
