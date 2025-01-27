/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk8d_trueskill.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:37:35 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/28 00:13:51 by jmiccio          ###   ########.fr       */
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

# define RESET        "\033[0m"
# define BLUE         "\033[34m"
# define BOLD_BLUE     "\033[1;34m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_RED     "\033[1;31m"


typedef struct t_player
{
	char			*name;
	double			mu;
	double			sigma;
	struct t_player	*next;
	struct t_player	*prev;
	
}				t_player;


typedef struct t_data
{
	t_player	*players;
	char	**stats;
	int		num_of_player;

}				t_data;

void		set_data(t_data *data);
void		ft_error(char *str, t_data *data, int exit_code);
void		*ft_free_map(char **map);
char		**read_stats(t_data *data);
void		end(t_data *data, int exit_code);
void		ft_player_lstclear(t_player **lst);
int			ft_player_lstadd_back(t_player **lst, t_player *new);
t_player	*ft_player_lstnew(void);
void		init_player_struct(t_data *data);
t_player	*ft_player_lstlast(t_player *lst);

#endif
