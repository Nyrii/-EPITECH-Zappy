/*
** init.c for init in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:08:53 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 16:14:22 2016 Nyrandone Noboud-Inpeng
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

void		init_ptrfunc(int (**func)(t_server *))
{
  func[0] = &avance_ia;
  func[1] = &droite_ia;
  func[2] = &gauche_ia;
  func[3] = &voir_ia;
  func[4] = &inventaire_ia;
  func[5] = &prend_ia;
  func[6] = &pose_ia;
  func[7] = &expulse_ia;
  func[8] = &broadcast_ia;
  func[9] = &incantation_ia;
  func[10] = &fork_ia;
  func[11] = &connect_nbr_ia;
  func[12] = NULL;
}
