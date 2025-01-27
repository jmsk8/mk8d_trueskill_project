#include "../includes/mk8d_trueskill.h"

void	end(t_data *data, int exit_code)
{
	if (data->stats)
		ft_free_map(data->stats);
	if (data->players)
		ft_player_lstclear(&data->players);
	exit(exit_code);
}

void	*ft_free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
	return (0);
}

void	ft_error(char *str, t_data *data, int exit_code)
{
	(void)data;
	write(2, str, ft_strlen(str));
	end(data, exit_code);
}

