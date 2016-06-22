/*
** buffer_manager_pop_back.c for buffer_manager_pop_back in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 13:49:19 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 14:10:46 2016 Nyrandone Noboud-Inpeng
*/

#include <stdio.h>
#include <stdlib.h>
#include "buffer_manager.h"

void		free_content(t_bmanager *list)
{
  t_bmanager	*tmp;

  tmp = list;
  while (tmp)
    {
      free(tmp->struc);
      tmp = tmp->next;
    }
}

t_bmanager		*push_back_list(t_bmanager *this, void *struc)
{
  t_bmanager		*elem;

  if (!this || !*this->last || !(elem = create_list(struc, this)))
    return (NULL);
  elem->prev = (*this->last);
  (*this->last)->next ? elem->next = (*this->last)->next : 0;
  (*this->last)->next ? elem->next->prev = elem : 0;
  (*this->last)->next = elem;
  (*this->last) = elem;
  return ((*this->size)++, *this->first);
}
