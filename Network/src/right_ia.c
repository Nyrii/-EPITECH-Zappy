/*
** right_ia.c for right_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:46:42 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 15:06:33 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "enum.h"

int		right_ia(t_server *server, t_player *player)
{
  if (player->orientation + 90 > LEFT)
    player->orientation = TOP;
  else
    player->orientation += 90;
  ppo_ia(server, player);
  // send message to ALL GRAPHIC CLIENTS and player
  return (0);
}
