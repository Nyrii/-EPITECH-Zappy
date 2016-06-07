/*
** get_opt.c for getopt in /home/noboud_n/Share
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 10:53:46 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 13:21:29 2016 Nyrandone Noboud-Inpeng
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
}

static int	init_teams(t_data *data, char **argv, int optind)
{
  int		i;

  i = 0;
  while (argv[optind] != NULL
	 && strcmp(argv[optind], "-p") != 0
	 && strcmp(argv[optind], "-x") != 0
	 && strcmp(argv[optind], "-y") != 0
	 && strcmp(argv[optind], "-c") != 0
	 && strcmp(argv[optind], "-t") != 0)
    ++optind;
  if ((data->teams = malloc((optind + 1) * sizeof(char *))) == NULL)
    {
      fprintf(stderr, ERR_MALLOC);
      return (-1);
    }
  data->teams[i] = NULL;
  return (i);
}

static int	store_team(t_data *data, char **argv, int *optind)
{
  int		i;

  --(*optind);
  if ((i = init_teams(data, argv, *optind)) == -1)
    return (-1);
  while (argv[*optind] != NULL
	 && strcmp(argv[*optind], "-p") != 0
	 && strcmp(argv[*optind], "-x") != 0
	 && strcmp(argv[*optind], "-y") != 0
	 && strcmp(argv[*optind], "-c") != 0
	 && strcmp(argv[*optind], "-t") != 0)
    {
      if (strcmp(argv[*optind], "-n") != 0
	  && (data->teams[i++] = strdup(argv[*optind])) == NULL)
	{
	  fprintf(stderr, ERR_MALLOC);
	  return (-1);
	}
      ++(*optind);
    }
  if (i == 0)
    return (fprintf(stderr, ERR_NBTEAMS), -1);
  data->teams[i] = NULL;
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
  if (optind != argc && data->teams == NULL)
    {
      fprintf(stderr, USAGE);
      return (-1);
    }
  if (data->port < 0 || data->world_x <= 0 || data->world_y <= 0
      || data->max_clients <= 0 || data->delay < 0)
    {
      fprintf(stderr, ERR_VALUES_USAGE);
      return (-1);
    }
  return (0);
}
