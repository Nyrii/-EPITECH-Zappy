/*
** init_percentages.c for init_percentages in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 15:50:39 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 22:11:18 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void		init_percentages(t_data *data)
{
  data->percentages[FOOD] = 40.0;
  data->percentages[LINEMATE] = 23.0;
  data->percentages[DERAUMERE] = 20.5;
  data->percentages[SIBUR] = 25.6;
  data->percentages[MENDIANE] = 12.8;
  data->percentages[PHIRAS] = 15.0;
  data->percentages[THYSTAME] = 2.5;
  data->percentages[NONE] = -1;
}
