#include "../includes/mk8d_trueskill.h"

void free_tmp_var(t_data *data)
{
	if (data->cmd)
	{
		ft_free_array(data->cmd);
		data->cmd = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}

int	line_is_empty(char *str)
{
	while (*str)
	{
		if (!(isspace(*str)))
			return (0);
		str++;
	}
	return (1);
}

void	end(t_data *data, int exit_code)
{
	if (data->stats)
		ft_free_array(data->stats);
	if (data->players)
	{
		ft_player_lstclear(&data->players);
		data->players = NULL;
	}
	if (data->tournament_players)
	{
		ft_player_lstclear(&data->tournament_players);
		data->tournament_players = NULL;
	}
	if (data->cmd)
		ft_free_array(data->cmd);
	if (data->input)
		free(data->input);
	
	rl_clear_history();
	exit(exit_code);
}

void	*ft_free_array(char **map)
{
	int		i;

	i = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		if (map[i])
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

