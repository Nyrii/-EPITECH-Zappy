/*
** get_opt.c for getopt in /home/noboud_n/Share
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 10:53:46 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun  8 21:07:09 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "errors.h"
#include "server.h"

static void	init_data(t_data *data)
{
  data->port = -1;
  data->world_x = -1;
  data->world_y = -1;
  data->max_clients = -1;
  data->teams = NULL;
  data->map = NULL;
  data->resources = NULL;
  data->percentages[FOOD] = 50.0;
  data->percentages[LINEMATE] = 23.0;
  data->percentages[DERAUMERE] = 20.5;
  data->percentages[SIBUR] = 25.6;
  data->percentages[MENDIANE] = 12.8;
  data->percentages[PHIRAS] = 15.0;
  data->percentages[THYSTAME] = 2.5;
}

static t_team	*create_new_team(char *name_team)
{
  t_team	*tmp;

  if ((tmp = malloc(sizeof(t_team))) == NULL)
    return (NULL);
  tmp->nb_players = 0;
  tmp->name = name_team;
  tmp->players = NULL;
  return (tmp);
}

static int	store_team(t_data *data, char **argv, int *optind)
{
  int		i;

  i = 0;
  --(*optind);
  while (argv[*optind] != NULL
	 && strcmp(argv[*optind], "-p") != 0
	 && strcmp(argv[*optind], "-x") != 0
	 && strcmp(argv[*optind], "-y") != 0
	 && strcmp(argv[*optind], "-c") != 0
	 && strcmp(argv[*optind], "-t") != 0)
    {
      if (strcmp(argv[*optind], "-n") != 0 &&
	  list_add_elem_at_back(&data->teams,
				create_new_team(argv[*optind])) == FALSE)
	return (fprintf(stderr, ERR_PUSHBACK), -1);
      if (strcmp(argv[*optind], "-n") != 0)
	++i;
      ++(*optind);
    }
  if (i == 0)
    return (fprintf(stderr, ERR_NBTEAMS), -1);
  return (0);
}

static int	manage_options(t_data *data, char **argv,
			       int opt, int *optind)
{
  switch (opt)
    {
      case 'p':
      data->port = atoi(optarg);
      break ;
      case 'x':
      data->world_x = atoi(optarg);
      break ;
      case 'y':
      data->world_y = atoi(optarg);
      break ;
      case 'c':
      data->max_clients = atoi(optarg);
      break ;
      case 't':
      data->delay = atoi(optarg);
      break ;
      case 'n':
      if (store_team(data, argv, optind) == -1)
	return (-1);
      break ;
      default:
      return (fprintf(stderr, USAGE), -1);
    }
  return (0);
}

int		get_opt(int argc, char **argv, t_data *data)
{
  int		opt;

  init_data(data);
  while ((opt = getopt(argc, argv, "p:x:y:c:t:n:")) != -1)
    {
      if (manage_options(data, argv, opt, &optind) == -1)
	return (-1);
    }
  if (optind != argc && (data->teams == NULL
			 || list_get_size(data->teams) <= 1))
    return (fprintf(stderr, USAGE), -1);
  if (data->port < 0 || data->world_x <= 0 || data->world_y <= 0
      || data->max_clients <= 0 || data->delay <= 0 || data->teams == NULL
      || list_get_size(data->teams) <= 1)
    return (fprintf(stderr, USAGE), -1);
  if (init_resources(&data->resources) == -1)
    return (-1);
  return (0);
}
