/*
** generic_list.h for  in /home/empoci_k/rendu_tek2/PSU_2015_myirc
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Mon May 16 18:28:12 2016 Kévin Empociello
** Last update Tue Jun  7 18:22:41 2016 nekfeu
*/

#ifndef GENERIC_LIST_H_
# define GENERIC_LIST_H_

/*
** Types
*/

typedef enum	e_bool
{
  FALSE,
  TRUE
}		t_bool;

typedef struct		s_node
{
  void			*value;
  struct s_node      	*next;
}		        t_node;

typedef t_node		*t_list;
/*
** Functions
*/

/* Informations */

unsigned int    list_get_size(t_list);
t_bool          list_is_empty(t_list);

/* Modification */

t_bool  list_add_elem_at_front(t_list *, void *);
t_bool  list_add_elem_at_back(t_list *, void *);
t_bool  list_add_elem_at_position(t_list *, void *, unsigned int);

t_bool  list_del_elem_at_front(t_list *);
t_bool  list_del_elem_at_back(t_list *);
t_bool  list_del_elem_at_position(t_list *, unsigned int);

void    list_clear(t_list *);

/* Value Access */

void    *list_get_elem_at_front(t_list);
void    *list_get_elem_at_back(t_list);
void    *list_get_elem_at_position(t_list, unsigned int);

#endif /* !GENERIC_LIST_H_ */
