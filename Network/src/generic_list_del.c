/*
** generic_list_del.c for  in /home/nekfeu/rendu/PSU_2015_myirc/server_src
**
** Made by nekfeu
** Login   <nekfeu@epitech.net>
**
** Started on  Sat Jun  4 15:47:24 2016 nekfeu
** Last update Sun Jun 26 09:58:37 2016 Nyrandone Noboud-Inpeng
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "generic_list.h"

unsigned int	list_get_size(t_list list)
{
  t_list	tmp;
  unsigned int	i;

  i = 0;
  tmp = list;
  if (list == NULL)
    return (0);
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i++;
    }
  return (i);
}

t_bool		list_del_elem_at_front(t_list *front_ptr)
{
  t_list	tmp;

  if (front_ptr == NULL)
    return (FALSE);
  tmp = *front_ptr;
  *front_ptr = (*front_ptr)->next;
  free(tmp);
  return (TRUE);
}

t_bool		delete_node(t_list tmp)
{
  t_list	to_delete;

  if (tmp->next == NULL)
    return (FALSE);
  else
    {
      to_delete = tmp->next;
      tmp->next = tmp->next->next;
      free(to_delete);
    }
  return (TRUE);
}

t_bool		list_del_elem_at_position(t_list *front_ptr, unsigned int position)
{
  t_list	tmp;
  unsigned int	i;

  i = 0;
  tmp = *front_ptr;
  if (*front_ptr == NULL)
    return (FALSE);
  if (position > list_get_size(*front_ptr))
    return (FALSE);
  if (position == 0)
    {
      list_del_elem_at_front(front_ptr);
      return (TRUE);
    }
  while (tmp->next && i < position - 1)
    {
      tmp = tmp->next;
      i++;
    }
  if (delete_node(tmp) == FALSE)
    return (FALSE);
  return (TRUE);
}
