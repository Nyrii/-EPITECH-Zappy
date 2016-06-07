/*
** init.c for init in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:08:53 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 15:24:00 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include "server.h"

void		init_code(char **code)
{
  code[0] = "avance";
  code[1] = "droite";
  code[2] = "gauche";
  code[3] = "voir";
  code[4] = "inventaire";
  code[5] = "prend";
  code[6] = "pose";
  code[7] = "expulse";
  code[8] = "broadcast";
  code[9] = "incantation";
  code[10] = "fork";
  code[11] = "connect_nbr";
  code[12] = NULL;
}

void		init_ptrfunc(int (**func)(const int, char *,
					  t_list **, t_list **))
{
  code[0] = &avance_ia;
  code[1] = &droite_ia;
  code[2] = &gauche_ia;
  code[3] = &voir_ia;
  code[4] = &inventaire_ia;
  code[5] = &prend_ia;
  code[6] = &pose_ia;
  code[7] = &expulse_ia;
  code[8] = &broadcast_ia;
  code[9] = &incantation_ia;
  code[10] = &fork_ia;
  code[11] = &connect_nbr;
  code[12] = NULL;
}
