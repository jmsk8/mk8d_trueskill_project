/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk8d_trueskill.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:37:35 by jmiccio           #+#    #+#             */
/*   Updated: 2025/02/05 17:03:37 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MK8D_TRUESKILL_H
# define MK8D_TRUESKILL_H

# include "../libft/includes/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <ctype.h>
# include <time.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <math.h>

# define RESET        "\033[0m"
# define BLUE         "\033[34m"
# define BOLD_BLUE     "\033[1;34m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_RED     "\033[1;31m"
# define BOLD_YELLOW "\033[1;33m" 
# define BOLD_ORANGE "\033[1;38;5;214m"
# define BOLD_GRAY "\033[1;37m"
# define BOLD_BROWN "\033[1;38;5;94m"

# define RANK_S "\033[1;38;2;255;127;127m"
# define RANK_A "\033[1;38;2;179;239;120m"
# define RANK_B "\033[1;38;2;119;236;236m"
# define RANK_C "\033[1;38;2;177;118;237m"

#define MAX_LENGTH 4096

typedef struct t_player
{
	char			*name;
	double			mu;
	double			sigma;
	int				pos;
	struct t_player	*next;
	struct t_player	*prev;
	
}				t_player;


typedef struct t_data
{
	t_player	*players;
	t_player	*tournament_players;
	char	**stats;
	char	**resul_stats;
	char	**cmd;
	char	*input;
	int		num_of_player;

}				t_data;

/*initialization*/
void		set_data(t_data *data);
void		ft_player_lstclear(t_player **lst);
int			ft_player_lstadd_back(t_player **lst, t_player *new);
char		**read_stats(t_data *data);
void		init_player_struct(t_data *data);
void		signals(void);


/*lst_utils*/
t_player	*ft_player_lstnew_stats(char *name, float mu, float sigma);
t_player	*ft_player_lstnew(void);
t_player	*ft_player_lstlast(t_player *lst);
t_player	*sort_players(t_player *player);

/*parsing*/
int			parsing(t_data *data);
int			line_is_empty(char *str);
int			get_num_of_player(char **stats);
void		get_player_stats(t_data *data, char*stats, t_player *player);
int			check_arg(char *str);
char		*get_stats_array(int fd, int *is_error);

/*commands*/
void		trueskill_generator(t_data *data);
void		help_cmd();
void		save_file(t_data *data);
void		add_player(t_data *data);
void		delete_player(t_data *data, char *name);
void		prepare_tournament(t_data *data);
void		display_players_stats(t_player *player, int num_of_player);
void		display_player_stats(t_player *player, char *name);

/*utils*/
void		ft_error(char *str, t_data *data, int exit_code);
void		*ft_free_array(char **map);
void		end(t_data *data, int exit_code);
int			exec(t_data *data);
void		free_tmp_var(t_data *data);
float		string_to_float(const char *str);
char		*get_input(char *str);
char		**read_result(t_data *data);
void		save_tmp_data(t_player *players);
void		save_old_file(t_player *players);
void		save_new_data(t_player *players);
void		refresh_player_struct(t_player *player, t_player *player_tour);
void		refresh_tournament_player_struct(t_data *data);
void		display_competing_players(t_player *player);
void		display_competing_players_result(t_player *player);
void		display_competing_players_result2(t_player *player, float diff[12]);
void		ensure_directory_exists(const char *dir);
void		save_data_file(char **data);;


#endif
