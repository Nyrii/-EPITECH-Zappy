/*
** enum.h for enum in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun  8 16:12:29 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 16:22:52 2016 Nyrandone Noboud-Inpeng
*/

#ifndef ENUM_H_
# define ENUM_H_

# define TOP 0
# define RIGHT 90
# define BOTTOM 180
# define LEFT 270

typedef enum	e_bool
{
  FALSE,
  TRUE
}		t_bool;

typedef enum	e_ressources
{
  FOOD = 0,
  LINEMATE,
  DERAUMERE,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME,
  NONE
}		t_ressources;

#endif /* !ENUM_H_ */
