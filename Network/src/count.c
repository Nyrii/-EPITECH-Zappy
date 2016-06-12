/*
** count.c for count in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 12 16:17:18 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 16:24:33 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		count_elements(t_list *list)
{
  t_list	*tmp;
  int		number;

  tmp = list;
  number = 0;
  while (tmp != NULL)
    {
      ++number;
      *tmp = (*tmp)->next;
    }
  return (number);
}
