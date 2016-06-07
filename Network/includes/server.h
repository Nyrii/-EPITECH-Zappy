/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 15:52:21 2016 Nyrandone Noboud-Inpeng
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
** avance_ia.c
*/
int		avance_ia(t_data *);

/*
** broadcast_ia.c
*/
int		broadcast_ia(t_data *);

/*
** connect_ia.c
*/
int		connect_nbr_ia(t_data *);

/*
** droite_ia.c
*/
int		droite_ia(t_data *);

/*
** expulse_ia.c
*/
int		expulse_ia(t_data *);

/*
** fork_ia.c
*/
int		fork_ia(t_data *);

/*
** free.c
*/
int		free_tab(char **, int);

/*
** gauche_ia.c
*/
int		gauche_ia(t_data *);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_data *);

/*
** incantation_ia.c
*/
int		incantation_ia(t_data *);

/*
** init.c
*/
void		init_code(char **);
void		init_ptrfunc(int (**)(t_data *));

/*
** inventaire_ia.c
*/
int		inventaire_ia(t_data *);

/*
** pose_ia.c
*/
int		pose_ia(t_data *);

/*
** prend_ia.c
*/
int		prend_ia(t_data *);

/*
** voir_ia.c
*/
int		voir_ia(t_data *);

#endif /* !SERVER_H_ */
