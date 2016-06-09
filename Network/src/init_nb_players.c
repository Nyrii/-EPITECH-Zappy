/*
** init_nb_players.c for init_nb_players in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 22:58:32 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun  9 23:05:09 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

int		init_nb_players(int **nb_players)
{
  if (((*nb_players) = malloc(10 * sizeof(int))) == NULL)
    return (fprintf(stderr, ERR_MALLOC), -1);
  (*nb_players)[0] = 0;
  (*nb_players)[1] = 1;
  (*nb_players)[2] = 2;
  (*nb_players)[3] = 2;
  (*nb_players)[4] = 4;
  (*nb_players)[5] = 4;
  (*nb_players)[6] = 6;
  (*nb_players)[7] = 6;
  (*nb_players)[8] = -1;
  return (0);
}
