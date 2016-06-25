/*
** generate_map.c for generate_map in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 20:59:48 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 18:42:09 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int			generate_new_resources(t_server *server)
{
  int			y;
  int			x;
  int			resource;

  y = -1;
  while (server->data.map[++y] != NULL)
    {
      x = -1;
      while (server->data.map[y][++x] != NULL)
	{
	  resource = 0;
	  while (resource < NONE)
	    {
	      if ((rand() % 100) < server->data.percentages[resource] / 2)
		{
		  server->data.map[y][x][resource] += 1;
  		  if (bct_ia(server, y, x) == -1)
  		    return (-1);
		}
	      ++resource;
	    }
	}
    }
  return (0);
}

int			generate_food(t_server *server)
{
  int			y;
  int			x;

  y = 0;
  while (server->data.map && server->data.map[y] != NULL)
    {
      x = 0;
      while (server->data.map[y][x] != NULL)
	{
	  if ((rand() % 100) < server->data.percentages[FOOD])
	    {
	      server->data.map[y][x][FOOD] += 1;
  	      if (bct_ia(server, y, x) == -1)
  		return (-1);
	    }
	  ++x;
	}
      ++y;
    }
  return (0);
}

static void		generate_resources(int resource,
					   int quantity, int ***map)
{
  int			x;
  int			y;

  if (resource >= NONE)
    return ;
  while (quantity > 0)
    {
      y = 0;
      while (map[y] != NULL)
	{
	  x = 0;
	  while (map[y][x] != NULL)
	    {
	      if (resource < NONE && rand() % 2 == 0)
		{
		  map[y][x][resource] += 1;
		  quantity -= 1;
                  if (quantity <= 0)
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
  resource = 1;
  while (resource < NONE)
    {
      if ((rand() % 100) < data->percentages[resource])
	data->map[y][x][resource] += 1;
      ++resource;
    }
}

int			generate_map(t_data *data, int x, int y, int i)
{
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
  i = -1;
  while (++i < NONE)
    generate_resources(i, data->resources[0][i], data->map);
  return (0);
}
