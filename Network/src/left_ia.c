/*
** left_ia.c for left_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:47:42 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 10 19:10:01 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		left_ia(t_server *data, t_player *player)
{
  (void)data;
  (void)player;
  if (player->orientation - 90 < 0)
    player->orientation = 270;
  else
    player->orientation -= 90;
  // send message to ALL GRAPHIC CLIENTS and player
  return (0);
}
