/*
** create_buffer_manager.c for create_buffer_manager in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 13:52:02 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 14:10:03 2016 Nyrandone Noboud-Inpeng
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "buffer_manager.h"

t_bmanager	*create_list(void *struc, t_bmanager *old)
{
  t_bmanager	*list;

  if (!(list = malloc(sizeof(*list))) ||
      !(list->first = old ? old->first : malloc(sizeof(t_bmanager *))) ||
      !(list->last = old ? old->last : malloc(sizeof(t_bmanager *))) ||
      !(list->size = old ? old->size : malloc(sizeof(unsigned int))))
    return (fprintf(stderr, ERR_MALLOC), NULL);
  !old ? *list->first = list : 0;
  !old ? *list->last = list : 0;
  !old ? *list->size = 1 : 0;
  list->struc = struc;
  list->next = NULL;
  list->prev = NULL;
  list->push_back = &push_back_list;
  list->destroy = &destroy_list;
  return (list);
}

void		destroy_list(t_bmanager *this)
{
  t_bmanager	*tmp;
  t_bmanager	*back;
  unsigned int	i;

  if (!this)
    return ;
  free(this->last);
  free(this->first);
  free(this->size);
  back = this;
  i = 0;
  while (this != NULL && (this != back || !i))
    {
      i = 1;
      tmp = this;
      this = this->next;
      free(tmp);
    }
}
