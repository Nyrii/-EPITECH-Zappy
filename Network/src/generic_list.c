/*
** simple_list.c for  in /home/empoci_k/rendu_tek2/piscine_cpp_d02a/ex00
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Thu Jan  7 15:14:51 2016 Kévin Empociello
** Last update Tue Jun  7 18:21:45 2016 nekfeu
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "generic_list.h"

void   *list_get_elem_at_front(t_list list)
{
  if (list_get_size(list) == 0)
    return 0;
  else
    return list->value;
}

t_bool          list_add_elem_at_front(t_list *front_ptr, void *elem)
{
  t_list        new_elem;

  if ((new_elem = malloc(sizeof(t_node))) == NULL)
    return (FALSE);
  if (*front_ptr == NULL)
    {
      new_elem->value = elem;
      new_elem->next = NULL;
      *front_ptr = new_elem;
    }
  else
    {
      new_elem->value = elem;
      new_elem->next = *front_ptr;
      *front_ptr = new_elem;
    }
  return (TRUE);
}

void   *list_get_elem_at_position(t_list list, unsigned int position)
{
  t_list	tmp;
  unsigned int	i;

  i = 0;
  tmp = list;
  if (list == NULL)
    return 0;
  if (position == 0)
    {
      return (list_get_elem_at_front(list));
    }
  if (position > list_get_size(list))
    return 0;
  while (tmp->next && i < position)
    {
      tmp = tmp->next;
      i++;
    }
  if (tmp != NULL)
    return (tmp->value);
  return (NULL);
}

t_bool		list_add_elem_at_back(t_list *front_ptr, void *elem)
{
  t_list	new_elem;
  t_list	tmp;

  tmp = *front_ptr;
  if (elem == NULL || (new_elem = malloc(sizeof(t_node))) == NULL)
    return (FALSE);
  if (*front_ptr == NULL)
    {
      new_elem->value = elem;
      new_elem->next = NULL;
      *front_ptr = new_elem;
    }
  else
    {
      new_elem->value = elem;
      while (tmp->next)
	tmp = tmp->next;
      new_elem->next = NULL;
      tmp->next = new_elem;
    }
  return (TRUE);
}

t_bool		list_add_elem_at_position(t_list *front_ptr, void *elem,
				 unsigned int position)
{
  t_list	new_elem;
  t_list	tmp;
  unsigned int	i;

  i = 0;
  tmp = *front_ptr;
  if ((new_elem = malloc(sizeof(t_node))) == NULL ||
      position > list_get_size(*front_ptr))
    return (FALSE);
  if (*front_ptr == NULL || position == 0)
    return (list_add_elem_at_front(front_ptr, elem));
  else
    {
      new_elem->value = elem;
      while (tmp->next && i < position - 1)
	{
	  tmp = tmp->next;
	  i++;
	}
      new_elem->next = tmp->next;
      tmp->next = new_elem;
      return (TRUE);
    }
  return (FALSE);
}
