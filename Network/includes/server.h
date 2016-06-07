/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun  7 22:06:28 2016 Nyrandone Noboud-Inpeng
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "generic_list.h"

typedef struct		s_player
{
  int			x;
  int			y;
  int			level;
  int			stones[6];
  double		timer;
}			t_player;

typedef struct		s_team
{
  int			nb_players;
  char			*name;
  t_list		players;
}			t_team;

typedef struct		s_data
{
  int			port;
  int			world_x;
  int			world_y;
  int			max_clients;
  int			delay;
  t_list	       	teams;
  int			**map;
}			t_data;

typedef struct		s_server
{
  /* DATA WORLD */
  t_data		data;

  /* CMDS */
  char			*cmd_tab[13];
  int			(*cmd_ptr[13])();

  /* SOCKET */
  struct timeval	timeout;
  struct hostent	*hostinfo;
  int			max;
  int			sock;
  fd_set		rdfs;
}			t_server;

/*
** avance_ia.c
*/
int		avance_ia(t_server *);

/*
** broadcast_ia.c
*/
int		broadcast_ia(t_server *);

/*
** connect_ia.c
*/
int		connect_nbr_ia(t_server *);

/*
** droite_ia.c
*/
int		droite_ia(t_server *);

/*
** expulse_ia.c
*/
int		expulse_ia(t_server *);

/*
** fork_ia.c
*/
int		fork_ia(t_server *);

/*
** free.c
*/
int		free_tab(char **, int);

/*
** gauche_ia.c
*/
int		gauche_ia(t_server *);

/*
** generate_map.c
*/
int		generate_map(t_data *, int **);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_data *);

/*
** incantation_ia.c
*/
int		incantation_ia(t_server *);

/*
** init.c
*/
void		init_code(char **);
void		init_ptrfunc(int (**)(t_server *));

/*
** inventaire_ia.c
*/
int		inventaire_ia(t_server *);

/* main */
int		run_zappy(t_server *);

/*
** pose_ia.c
*/
int		pose_ia(t_server *);

/*
** prend_ia.c
*/
int		prend_ia(t_server *);

/*
** voir_ia.c
*/
int		voir_ia(t_server *);

#endif /* !SERVER_H_ */
