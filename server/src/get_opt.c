/*
** get_opt.c for getopt in /home/noboud_n/Share
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 10:53:46 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 11:47:23 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "errors.h"

int	get_opt(int argc, char **argv)
{
  int	port = -1;
  int	x = -1;
  int	y = -1;
  int	c = -1;
  int	t = -1;
  char	*n = NULL;
  int	opt;

  while ((opt = getopt(argc, argv, "p:x:y:c:t:n:")) != -1)
    {
      switch (opt)
	{
	  case 'p':
	  port = atoi(optarg);
	  break ;
	  case 'x':
	  x = atoi(optarg);
	  break ;
	  case 'y':
	  y = atoi(optarg);
	  break ;
	  case 'c':
	  c = atoi(optarg);
	  break ;
	  case 't':
	  t = atoi(optarg);
	  break ;
	  case 'n':
	  n = strdup(optarg);
	  break ;
	  default:
	  fprintf(stderr, ERR_USAGE);
	  exit(EXIT_FAILURE);
	}
    }
  printf("argc = %d, optind = %d\n", argc, optind);
  if (optind != argc && n == NULL)
    {
      fprintf(stderr, "Expected argument after options\n");
      exit(EXIT_FAILURE);
    }
  printf("port = %d, x = %d, y = %d, c = %d, t = %d, n = %s\n", port, x, y, c, t, n);
  exit(EXIT_SUCCESS);
}
