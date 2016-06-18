/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 18 15:01:40 2016 Nyrandone Noboud-Inpeng
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/timeb.h>
# include "generic_list.h"

typedef struct		s_timer
{
  struct timeb		val;
  int			is_done;
  double		end;
}			t_timer;

typedef struct		s_task
{
  char			*cmd;
  char			*params;
  char			*real;
  t_timer		*timer;
}			t_task;

typedef struct		s_client
{
  int			sock;
  int			timer;
}			t_client;

typedef struct		s_player
{
  int     		sock;
  int			id;
  int			x;
  int			y;
  int			orientation;
  int			level;
  int			inventory[8];
  t_timer		timer;
}			t_player;

typedef struct		s_team
{
  int			max_players;
  char			*name;
  t_list		players;
}			t_team;

typedef struct		s_egg
{
  int			x;
  int			y;
  int			timer;
  int			is_born;
  char			*team_name;
}			t_egg;

typedef struct		s_data
{
  int			port;
  int			world_x;
  int			world_y;
  int			max_clients;
  int			delay;
  t_list	       	teams;
  t_list		eggs;
  int			***map;
  int			**resources;
  float			percentages[8];
  int			*required_players;
  char			*strings_resources[8];
}			t_data;

typedef struct		s_server
{
  /* DATA WORLD */
  t_data		data;

  /* Clients */
  t_list  		queue_clients;
  t_list		graphic_clients;
  t_list		all_players;

  /* CMDS */
  char			*params;
  char			*cmd;
  char			*cmd_tab_ia[13];
  int			(*cmd_ptr_ia[13])();
  char			*cmd_tab_graphic[8];
  int			(*cmd_ptr_graphic[8])();

  /* SOCKET */
  struct timeval	timeout;
  struct hostent	*hostinfo;
  int			max;
  int			sock;
  fd_set		rdfs;
}			t_server;


/* Socket */
int   		init_server(int, int);
int   		error(char *);
int   		loop_server(t_server *);
void  		set_all_clients(t_server *);
int  		check_sockets_loop(t_server *);
t_player	*new_player(t_server *, t_team *, t_client *);
t_egg		*new_egg(t_server *, t_player *);
t_client	*new_client(t_server *);
int		handle_new_player(t_server *, t_team *, t_player *);
int		handle_new_client(t_server *);
int		handle_new_graphic(t_server *, t_client *);

/*
** bct.c
*/
char		*bct(int ***map, int const, int const);
int		bct_on_tile(t_server *, t_client *);

/*
** broadcast_ia.c
*/
int		broadcast_ia(t_server *, t_player *);

/*
** broadcast_init.c
*/
void		init_calculs(t_data, int *, t_player *);
int		get_best_tile(int *, t_player *);

/*
** close_all_clients.c
*/
int		close_all_clients(t_server *);

/*
** connect_ia.c
*/
int		connect_nbr_ia(t_server *, t_player *);

/*
** count.c
*/
int		count_elements(t_list *);

/*
** drop_ia.c
*/
int		drop_ia(t_server *, t_player *);

/*
** elevation.c
*/
int		is_elevation_legit(t_data *, int, int *);

/*
** expulse_ia.c
*/
int		expulse_ia(t_server *, t_player *);

/*
** epur.c
*/
char		*epur_bf(char *str);

/*
** fork_ia.c
*/
int		fork_ia(t_server *, t_player *);

/*
** forward_ia.c
*/
int		forward_ia(t_server *, t_player *);

/*
** free.c
*/
int		free_map(int ***, int const);
int		free_teams(t_list, int const);
int		free_list(t_list, int const);
int		free_int_tab(int *, int const);
int		free_double_int_tab(int **, int const);

/*
** free_all.c
*/
int		free_all(t_server *, int const);

/*
** generate_map.c
*/
void		generate_food(t_data *);
int		generate_map(t_data *, int, int, int);

/*
** generate_resources.c
*/
int		init_resources(int ***);

/*
** get_angle.c
*/
double		get_angle(t_player *, int const, int const, double *);
int		get_best_tile_by_angle(double const, double const, t_player *);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_server *);

/*
** get_opt_set_delay.c
*/
void		set_delay(t_server *, char *, int *);

/*
** get_player.c
*/
t_list		get_players_at_pos(t_data *, int, int);
int		get_max_player_id(t_server *);
t_player	*get_player_by_id(t_server *, int const);

/*
** get_team.c
*/
t_team		*get_team_by_name(t_server *, const char *);
t_team		*get_team_by_player(t_server *, t_player *);

/*
** left_ia.c
*/
int		left_ia(t_server *, t_player *);

/*
** incantation_ia.c
*/
int		incantation_ia(t_server *, t_player *);

/*
** init.c
*/
void		init_code(char **, char **);
void		init_ptrfunc(int (**)(t_server *, t_player *),
			     int (**)(t_server *, t_client *));

/*
** init_nb_players.c
*/
int		init_nb_players(int **);

/*
** init_percentages.c
*/
void		init_percentages(t_data *);

/*
** init_perimeter.c
*/
void		call_init_perimeter(t_data, t_player *, int *);

/*
** init_strings_resources.c
*/
void		init_strings_resources(t_data *);

/*
** init_teams_max_players.c
*/
int		init_teams_max_players(t_list, int const);

/*
** inventory_ia.c
*/
int		inventory_ia(t_server *, t_player *);

/* main */
int		run_zappy(t_server *);

/*
** mct.c
*/
int		mct(t_server *, t_client *);

/*
** msz.c
*/
int		msz(t_server *, t_client *);

/*
** take_ia.c
*/
int		take_ia(t_server *, t_player *);

/*
** tna.c
*/
int		tna(t_server *, t_client *);

/*
** parse.c
*/
char		*parse_cmd(t_server *, char *);

/*
** plv.c
*/
int		plv(t_server *, t_client *);

/*
** pin.c
*/
int		pin_ia(t_server *, t_player *);
int		pin(t_server *, t_client *);

/*
** ppo.c
*/
int		ppo_ia(t_server *, t_player *);
int		ppo(t_server *, t_client *);

/*
** process.c
*/
int		manage_commands_graphic(t_server *, t_client *, const char *);
int		manage_commands_ia(t_server *, t_player *, const char *);
int		manage_auth(t_server *, t_client *, const char *);

/*
** remove.c
*/
int		remove_client_from_queue(t_server *, t_client *);

/*
** right_ia.c
*/
int		right_ia(t_server *, t_player *);

/*
** save_server.c
*/
t_server	*save_server(t_server *, int const);

/*
** see_ia.c
*/
int		see_ia(t_server *, t_player *);

/*
** see_ia_calculs.c
*/
void		determine_minus_x(t_server *, t_player *, int *, int);
void		determine_minus_y(t_server *, t_player *, int *, int);
void		determine_plus_x(t_server *, t_player *, int *, int);
void		determine_plus_y(t_server *, t_player *, int *, int);

/*
** see_ia_resources.c
*/
int		see_ia_resources(char **, t_server *,
				 int *, int *);

/*
** send.c
*/
int		send_all_players(t_server *, t_player *, const char *);
int		send_all_graphics(t_server *, const char *);

/*
** sgt.c
*/
int		sgt(t_server *, t_client *);

/*
** sst.c
*/
int		sst(t_server *, t_client *);

#endif /* !SERVER_H_ */
