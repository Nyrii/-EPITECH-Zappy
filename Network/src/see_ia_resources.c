/*
** see_ia_resources.c for see_ia_resources in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 11 14:49:46 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 02:04:13 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "server.h"

static int	get_size(t_data data, int ***map, int const y, int const x)
{
  int		i;
  int		resources;
  unsigned int	nb_players;
  t_list	players;

  i = 0;
  resources = 0;
  nb_players = 0;
  while (map && map[y] && map[y][x] && map[y][x][i] != -1)
    {
      resources += map[y][x][i];
      ++i;
    }
  players = get_players_at_pos(&data, y, x);
  nb_players = list_get_size(players);
  if (resources == 0 && nb_players == 0)
    return (10);
  return (resources * 12 + nb_players * 10 + 10);
}

static int	store_players(char **see, t_data data, int *pos, int *i)
{
  t_list	tmp;
  char		*string;
  unsigned int	count;

  string = " joueur";
  count = 0;
  if ((tmp = get_players_at_pos(&data, pos[0], pos[1])) == NULL)
    return (0);
  count = list_get_size(tmp);
  (*see)[(*i)] = '\0';
  while (count > 0)
    {
      if ((*see = strcat(*see, string)) == NULL)
	return (fprintf(stderr, ERR_STRCAT), -1);
      --count;
    }
  *i = strlen(*see);
  return (0);
}

static int	store_resources(char **see, t_data data, int *pos, int *i)
{
  int		n;
  int		tmp;

  n = 0;
  while (data.map && data.map[pos[0]][pos[1]]
	 && data.map[pos[0]][pos[1]][n] != -1)
    {
      tmp = data.map[pos[0]][pos[1]][n];
      while (tmp > 0)
	{
	  (*i) - 1 != 0 ? (*see)[(*i)++] = ' ' : 0;
	  (*see)[*i] = '\0';
	  if ((*see = strcat(*see, data.strings_resources[n])) == NULL)
	    return (fprintf(stderr, ERR_STRCAT), -1);
	  *i = strlen(*see);
	  --tmp;
	}
      ++n;
    }
  return (0);
}

int		see_ia_resources(char **see, t_server *srv,
				 int *pos, int *i)
{
  int		is_null;
  int		size;

  is_null = *see == NULL ? 1 : 0;
  *i = *see == NULL ? 0 : (int)*i;
  size = get_size(srv->data, srv->data.map, pos[0], pos[1]);
  if (!*see ? !(*see = malloc(size)) :
      !(*see = realloc(*see, size + strlen(*see) + 1)))
    return (fprintf(stderr, ERR_MALLOC), -1);
  if (is_null == 1)
    (*see)[(*i)++] = '{';
  if (size == 10 && (is_null == 0 || is_null == 1))
    {
      (*see)[(*i)] = '\0';
      return (0);
    }
  if (store_players(see, srv->data, pos, i) == -1
      || store_resources(see, srv->data, pos, i) == -1)
    return (-1);
  (*see)[(*i)] = '\0';
  return (0);
}
