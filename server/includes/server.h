/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 15:26:21 2016 Nyrandone Noboud-Inpeng
*/

#ifndef SERVER_H_
# define SERVER_H_

typedef struct		s_data
{
  int			port;
  int			world_x;
  int			world_y;
  int			max_clients;
  int			delay;
  char			**teams;
}			t_data;

/*
** free.c
*/
int		free_tab(char **, int);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_data *);

/*
** init.c
*/
void		init_code(char **);
void		init_ptrfunc(int (**)(const int, char *,
				      t_list **, t_list **));

#endif /* !SERVER_H_ */
