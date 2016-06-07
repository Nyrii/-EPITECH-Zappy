/*
** generate_map.c for generate_map in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 20:59:48 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 23:15:17 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"

static void		generate_tile(int *tile)
{
  int			nb_ressources;
  int			ressource;
  int			i;
  int			tmp;
  int			pass;

  i = 0;
  tile[i] = -1;
  nb_ressources = rand() % 7;
  while (nb_ressources > 0)
    {
      tmp = -1;
      pass = 0;
      ressource = rand() % 7;
      while (tile[++tmp] != -1)
	{
	  if (tile[tmp] == ressource)
	    pass = 1;
	}
      pass != 1 ? (tile[i++] = ressource) : (void)pass;
      pass != 1 ? (tile[i] = -1) : (void)pass;
      --nb_ressources;
    }
  tile[i] = -1;
}

int			generate_map(t_data *data, int ***map, int x, int y)
{
  int			i;

  i = 0;
  if ((map = malloc((data->world_y + 1) * sizeof(int **))) == NULL
      || (map[y] = malloc((data->world_x + 1) * sizeof(int *))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  while (x < data->world_x * data->world_y)
    {
      if ((map[y][i] = malloc(7 * sizeof(int))) == NULL)
	return (fprintf(stderr, ERR_MALLOC), -1);
      generate_tile(map[y][i]);
      ++i;
      ++x;
      x % data->world_x == 0 ? (map[y][i] = NULL) : 0;
      x % data->world_x == 0 ? (i = 0) : (int)i;
      x % data->world_x == 0 ? (y += 1) : (int)y;
      if (x % data->world_x == 0 && x + 1 < data->world_x * data->world_y
	  && (!(map[y] = malloc((data->world_x + 1) * sizeof(int *)))))
	return (fprintf(stderr, ERR_MALLOC), -1);
    }
  map[y] = NULL;
  return (0);
}
