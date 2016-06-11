/*
** init.c for init in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:08:53 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 19:31:25 2016 Kevin Empociello
*/

#include <stdlib.h>
#include "server.h"

void		init_code(char **ia, char **graphic)
{
  ia[0] = "avance";
  ia[1] = "droite";
  ia[2] = "gauche";
  ia[3] = "voir";
  ia[4] = "inventaire";
  ia[5] = "prend";
  ia[6] = "pose";
  ia[7] = "expulse";
  ia[8] = "broadcast";
  ia[9] = "incantation";
  ia[10] = "fork";
  ia[11] = "connect_nbr";
  ia[12] = NULL;
  graphic[0] = "msz";
  graphic[1] = "bct";
  graphic[2] = "mct";
  graphic[3] = "tna";
  graphic[4] = "ppo";
  graphic[5] = "plv";
  graphic[6] = "pin";
  graphic[7] = NULL;
}

void		init_ptrfunc(int (**func_ia)(t_server *, t_player *),
			     int (**func_graphic)(t_server *, t_client *))
{
  func_ia[0] = &forward_ia;
  func_ia[1] = &right_ia;
  func_ia[2] = &left_ia;
  func_ia[3] = &see_ia;
  func_ia[4] = &inventory_ia;
  func_ia[5] = &take_ia;
  func_ia[6] = &drop_ia;
  func_ia[7] = &expulse_ia;
  func_ia[8] = &broadcast_ia;
  func_ia[9] = &incantation_ia;
  func_ia[10] = &fork_ia;
  func_ia[11] = &connect_nbr_ia;
  func_ia[12] = NULL;
  func_graphic[0] = &msz;
  func_graphic[1] = &bct_on_tile;
  func_graphic[2] = &mct;
  func_graphic[3] = &tna;
  func_graphic[4] = &ppo;
  func_graphic[5] = &plv;
  func_graphic[6] = &pin;
  func_graphic[7] = NULL;
}
