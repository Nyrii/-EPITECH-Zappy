/*
** get_opt_set_delay.c for set_delay in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 18 15:00:19 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 18 15:22:48 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"

void		set_delay(t_server *server, char *optarg, int *optind)
{
  if (optarg != NULL
      && strcmp(optarg, "-p") != 0
      && strcmp(optarg, "-x") != 0
      && strcmp(optarg, "-y") != 0
      && strcmp(optarg, "-c") != 0
      && strcmp(optarg, "-n") != 0)
    server->data.delay = atoi(optarg);
  else if (optarg != NULL
	   && (strcmp(optarg, "-p") == 0
	       || strcmp(optarg, "-x") == 0
	       || strcmp(optarg, "-y") == 0
	       || strcmp(optarg, "-c") == 0
	       || strcmp(optarg, "-n") == 0))
    {
      printf("Changing time delay to default value : t = 100...\n");
      server->data.delay = 100;
      *optind = *optind > 0 ? (*optind) - 1 : *optind;
    }
  if (optarg == NULL)
    server->data.delay = 100;
}
