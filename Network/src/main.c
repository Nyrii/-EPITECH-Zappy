/*
** main.c for main in /Users/noboud_n/Documents/Share/PSU_2015_zappy/serv/src
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.net>
**
** Started on  Tue Jun  7 11:35:34 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 14:48:35 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		main(int argc, char **argv)
{
  t_data	data;

  get_opt(argc, argv, &data);
  free_tab(data.teams, 0);
  return (0);
}
