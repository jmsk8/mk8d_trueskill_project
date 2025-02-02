/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk8d_trueskill.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:37:35 by jmiccio           #+#    #+#             */
/*   Updated: 2025/02/02 17:37:59 by jmiccio          ###   ########.fr       */
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

void		set_data(t_data *data);
void		ft_error(char *str, t_data *data, int exit_code);
void		*ft_free_array(char **map);
char		**read_stats(t_data *data);
void		end(t_data *data, int exit_code);
void		ft_player_lstclear(t_player **lst);
int			ft_player_lstadd_back(t_player **lst, t_player *new);
t_player	*ft_player_lstnew(void);
void		init_player_struct(t_data *data);
t_player	*ft_player_lstlast(t_player *lst);
int			line_is_empty(char *str);
int			parsing(t_data *data);
int			exec(t_data *data);
void		free_tmp_var(t_data *data);
void		signals(void);
float		string_to_float(const char *str);
t_player	*ft_player_lstnew_stats(char *name, float mu, float sigma);
void		trueskill_generator(t_data *data);
char		*get_stats_array(int fd, int *is_error);
void		get_player_stats(t_data *data, char*stats, t_player *player);
int			get_num_of_player(char **stats);
char		*get_input(char *str);
t_player	*sort_players(t_player *player);
char	**read_result(t_data *data);
void	save_tmp_data(t_player *players);
void	save_old_file(t_player *players);
void	save_new_data(t_player *players);
void	refresh_player_struct(t_player *player, t_player *player_tour);
void	refresh_tournament_player_struct(t_data *data);
void	prepare_tournament(t_data *data);
void	display_competing_players(t_player *player);
void	display_players_stats(t_player *player, int num_of_player);
void	display_player_stats(t_player *player, char *name);
void	display_competing_players_result(t_player *player);
void	ensure_directory_exists(const char *dir);


#endif
