/*
** init_resources.c for init_resources in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:27:15 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  9 21:27:20 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include "enum.h"
#include "errors.h"

int		init_resources_by_final_elevation(int ***resources,
						   int *template)
{
  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 1;
  template[DERAUMERE] = 2;
  template[SIBUR] = 3;
  template[MENDIANE] = 0;
  template[PHIRAS] = 1;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[6] = template;
  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 2;
  template[DERAUMERE] = 2;
  template[SIBUR] = 2;
  template[MENDIANE] = 2;
  template[PHIRAS] = 2;
  template[THYSTAME] = 1;
  template[NONE] = -1;
  (*resources)[7] = template;
  (*resources)[8] = NULL;
  return (0);
}

int		init_resources_by_higher_elevation(int ***resources)
{
  int		*template;

  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 1;
  template[DERAUMERE] = 1;
  template[SIBUR] = 2;
  template[MENDIANE] = 0;
  template[PHIRAS] = 1;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[4] = template;
  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 1;
  template[DERAUMERE] = 2;
  template[SIBUR] = 1;
  template[MENDIANE] = 0;
  template[PHIRAS] = 3;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[5] = template;
  return (init_resources_by_final_elevation(resources, NULL));
}

int		init_resources_by_middle_elevation(int ***resources)
{
  int		*template;

  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 1;
  template[DERAUMERE] = 1;
  template[SIBUR] = 1;
  template[MENDIANE] = 0;
  template[PHIRAS] = 0;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[2] = template;
  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 2;
  template[DERAUMERE] = 0;
  template[SIBUR] = 1;
  template[MENDIANE] = 0;
  template[PHIRAS] = 2;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[3] = template;
  return (init_resources_by_higher_elevation(resources));
}

int		init_resources(int ***resources, int *template)
{
  if (((*resources) = malloc(9 * sizeof(int *))) == NULL
      || (template = malloc(9 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 9;
  template[DERAUMERE] = 8;
  template[SIBUR] = 10;
  template[MENDIANE] = 5;
  template[PHIRAS] = 6;
  template[THYSTAME] = 1;
  template[NONE] = -1;
  (*resources)[0] = template;
  if ((template = malloc(8 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  template[FOOD] = 0;
  template[LINEMATE] = 1;
  template[DERAUMERE] = 0;
  template[SIBUR] = 0;
  template[MENDIANE] = 0;
  template[PHIRAS] = 0;
  template[THYSTAME] = 0;
  template[NONE] = -1;
  (*resources)[1] = template;
  return (init_resources_by_middle_elevation(resources));
}
