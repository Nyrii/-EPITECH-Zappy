/*
** right_ia.c for right_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:46:42 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 10 19:10:49 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		right_ia(t_server *data, t_player *player)
{
  (void)data;
  (void)player;
  if (player->orientation + 90 > 270)
    player->orientation = 0;
  else
    player->orientation += 90;
  // send message to ALL GRAPHIC CLIENTS and player
  return (0);
}
