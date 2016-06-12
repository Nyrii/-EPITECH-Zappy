/*
** see_ia_resources.c for see_ia_resources in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 11 14:49:46 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 14:17:41 2016 Nyrandone Noboud-Inpeng
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
    return (5);
  return (resources * 9 + nb_players * 9 + 5);
}

static void	store_players(char **see, t_data data, int *pos, int *i)
{
  t_list	tmp;
  char		*string;
  unsigned int	count;
  int		n;

  string = " joueur";
  count = 0;
  if ((tmp = get_players_at_pos(&data, pos[0], pos[1])) == NULL)
    return ;
  count = list_get_size(tmp);
  while (count > 0)
    {
      n = 0;
      while (string[n])
	(*see)[(*i)++] = string[n++];
      --count;
    }
}

static void	store_resources(char **see, t_data data, int *pos, int *i)
{
  int		n;
  int		x;
  int		tmp;

  n = 0;
  while (data.map && data.map[pos[0]][pos[1]]
	 && data.map[pos[0]][pos[1]][n] != -1)
    {
      tmp = data.map[pos[0]][pos[1]][n];
      while (tmp > 0)
	{
	  x = 0;
	  (*i) - 1 != 0 ? (*see)[(*i)++] = ' ' : 0;
	  while (data.strings_resources[n][x])
	    (*see)[(*i)++] = data.strings_resources[n][x++];
	  --tmp;
	}
      ++n;
    }
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
  if (size == 5 && (is_null == 0 || is_null == 1))
    {
      (*see)[(*i)] = '\0';
      return (0);
    }
  store_players(see, srv->data, pos, i);
  store_resources(see, srv->data, pos, i);
  (*see)[(*i)] = '\0';
  return (0);
}
