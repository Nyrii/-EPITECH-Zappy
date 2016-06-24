/*
** get_opt.c for getopt in /home/noboud_n/Share
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 10:53:46 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 24 15:30:55 2016 Nyrandone Noboud-Inpeng
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
  data->ports = NULL;
  data->world_x = -1;
  data->world_y = -1;
  data->max_clients = -1;
  data->delay = -1;
  data->teams = NULL;
  data->eggs = NULL;
  data->map = NULL;
  data->resources = NULL;
  data->required_players = NULL;
  init_percentages(data);
  init_strings_resources(data);
}

static t_team	*create_new_team(char *name_team, int max)
{
  t_team	*tmp;

  if ((tmp = malloc(sizeof(t_team))) == NULL)
    return (NULL);
  tmp->max_players = max;
  if ((tmp->name = strdup(name_team)) == NULL)
    return (NULL);
  tmp->players = NULL;
  return (tmp);
}

static int	store_team(t_server *s, char **argv, int *optind)
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
      if (strcmp(argv[*optind], "-n") != 0
	  && get_team_by_name(s, argv[*optind]) != NULL)
	return (fprintf(stderr, ERR_SAME_TEAM), -1);
      if (strcmp(argv[*optind], "-n") != 0 &&
	  list_add_elem_at_back(&s->data.teams,
				create_new_team(argv[*optind],
						s->data.max_clients)) == FALSE)
	return (fprintf(stderr, ERR_PUSHBACK), -1);
      if (strcmp(argv[*optind], "-n") != 0)
	++i;
      ++(*optind);
    }
  return (i == 0 ? fprintf(stderr, ERR_NBTEAMS), -1 : 0);
}

static int	manage_options(t_server *server, char **argv,
			       int opt, int *optind)
{
  switch (opt)
    {
      case 'p':
      ports_manager(server, argv, optind);
      break ;
      case 'x':
      server->data.world_x = atoi(optarg);
      break ;
      case 'y':
      server->data.world_y = atoi(optarg);
      break ;
      case 'c':
      server->data.max_clients = atoi(optarg);
      break ;
      case 't':
      set_delay(server, argv, optarg, optind);
      break ;
      case 'n':
      if (store_team(server, argv, optind) == -1)
	return (-1);
      break ;
      default:
      return (fprintf(stderr, USAGE), -1);
    }
  return (0);
}

int		get_opt(int argc, char **argv, t_server *server)
{
  int		opt;

  init_data(&server->data);
  while ((opt = getopt(argc, argv, "p:x:y:c:t::n:")) != -1)
    {
      if (manage_options(server, argv, opt, &optind) == -1)
	return (-1);
    }
  if (optind != argc && (server->data.teams == NULL
			 || list_get_size(server->data.teams) <= 1
			 || server->data.ports == NULL))
    return (fprintf(stderr, USAGE), -1);
  if (server->data.ports == NULL || server->data.world_x <= 0
      || server->data.world_y <= 0 || server->data.world_x > 1000
      || server->data.world_y > 1000 || server->data.max_clients <= 0
      || server->data.delay <= 0 || server->data.delay > 100000
      || server->data.teams == NULL || list_get_size(server->data.teams) <= 1)
    return (fprintf(stderr, USAGE), -1);
  if (init_resources(&server->data.resources) == -1
      || init_nb_players(&server->data.required_players) == -1
      || init_teams_max_players(server->data.teams,
				server->data.max_clients) == -1)
    return (-1);
  return (0);
}
