/*
** free.c for free in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 14:43:13 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 14:46:07 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>

int		free_tab(char **tab, int ret_value)
{
  int		i;

  i = 0;
  while (tab && tab[i])
    free(tab[i++]);
  if (tab)
    free(tab);
  return (ret_value);
}
