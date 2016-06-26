/*
** init_strings_resources.c for strings resources in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 15:49:09 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 17 15:51:32 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void		init_strings_resources(t_data *data)
{
  data->strings_resources[FOOD] = "nourriture";
  data->strings_resources[LINEMATE] = "linemate";
  data->strings_resources[DERAUMERE] = "deraumere";
  data->strings_resources[SIBUR] = "sibur";
  data->strings_resources[MENDIANE] = "mendiane";
  data->strings_resources[PHIRAS] = "phiras";
  data->strings_resources[THYSTAME] = "thystame";
  data->strings_resources[NONE] = NULL;
}
