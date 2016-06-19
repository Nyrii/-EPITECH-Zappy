/*
** get_opt_set_delay.c for set_delay in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 18 15:00:19 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 18:36:47 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

void		set_delay(t_server *server, char **argv, char *optarg, int *optind)
{
  if (argv[*optind] != NULL
      && strcmp(argv[*optind], "-p") != 0
      && strcmp(argv[*optind], "-x") != 0
      && strcmp(argv[*optind], "-y") != 0
      && strcmp(argv[*optind], "-c") != 0
      && strcmp(argv[*optind], "-n") != 0)
    server->data.delay = atoi(argv[*optind]);
  else if (argv[*optind] != NULL
	   && (strcmp(argv[*optind], "-p") == 0
	       || strcmp(argv[*optind], "-x") == 0
	       || strcmp(argv[*optind], "-y") == 0
	       || strcmp(argv[*optind], "-c") == 0
	       || strcmp(argv[*optind], "-n") == 0))
    {
      printf("Changing time delay to default value : t = 100...\n");
      server->data.delay = 100;
    }
  else if (optarg == NULL)
    server->data.delay = 100;
}
