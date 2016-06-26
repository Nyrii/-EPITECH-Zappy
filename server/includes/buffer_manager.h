/*
** buffer_manager.h for buffer_manager in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 13:42:43 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 14:31:24 2016 Nyrandone Noboud-Inpeng
*/

#ifndef BUFFER_MANAGER_H_
# define BUFFER_MANAGER_H_

typedef struct		s_bmanager
{
  struct s_bmanager	**last;
  struct s_bmanager	**first;
  struct s_bmanager	*next;
  struct s_bmanager	*prev;
  void			*struc;
  unsigned int		*size;
  struct s_bmanager	*(*push_back)(struct s_bmanager *, void *);
  void			(*destroy)(struct s_bmanager *);
}			t_bmanager;

t_bmanager		*create_list(void *, t_bmanager *);
t_bmanager		*push_back_list(t_bmanager *, void *);
int			make_circular_list(t_bmanager *);
int			get_size_list(t_bmanager *);
void			destroy_list(t_bmanager *);
void			free_content(t_bmanager *);

#endif /* !BUFFER_MANAGER_H_ */
