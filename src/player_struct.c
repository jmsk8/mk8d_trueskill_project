#include "../includes/mk8d_trueskill.h"

float string_to_float(const char *str)
{
	char *endptr;
	float value = strtof(str, &endptr);
	if (endptr == str)
	{
		perror("Conversion error");
		return 0.0f;
	}
	return value;
}

float	get_mu(t_data *data, char *stats)
{
	
	int		len = 0;
	char	*name = NULL;
	float	res;

	if (!stats)
		return (-1);
	while(stats[len] != ',')
		len++;
	if (!(name = strndup(stats, len)))
		ft_error("malloc error\n", data, 1);
	res = string_to_float(name);
	free(name);
	return (res);
}

float	get_sigma(t_data *data, char *stats)
{
	int		len = 0;
	char	*name = NULL;
	float	res;
	
	while(stats[len])
		len++;
	if (!(name = strndup(stats, len)))
		ft_error("malloc error\n", data, 1);
	res = string_to_float(name);
	free(name);
	return (res);
}

char *get_name(t_data *data, char *stats)
{
	int		len = 0;
	char	*name = NULL;
	while(!isspace(stats[len]))
		len++;
	if (!(name = strndup(stats, len)))
		ft_error("malloc error\n", data, 1);
	return (name);
}

void get_player_stats(t_data *data, char*stats, t_player *player)
{
	player->name = get_name(data, stats);
	stats += ft_strlen(player->name) + 6;
	player->mu = get_mu(data, stats);
	while (isdigit(*stats) || *stats == '.' || isspace(*stats))
		stats++;
	while (!isdigit(*stats))
		stats++;
	player->sigma = get_sigma(data, stats);
}

int	get_num_of_player(char **stats)
{
	int	num = 0;
	while(stats[num + 1] && ft_strlen(stats[num + 1]) > 16)
		num++;
	return (num);
}

void	init_player_struct(t_data *data)
{
	data->date = ft_strdup(data->stats[0]);
	data->num_of_player = get_num_of_player(data->stats);
	data->players = ft_player_lstnew();
	get_player_stats(data, data->stats[1], ft_player_lstlast(data->players));
	for (int i = 2; i != data->num_of_player + 1; i++)
	{
		if (!ft_player_lstadd_back(&data->players, ft_player_lstnew()))
			ft_error("malloc error\n", data, 1);
		get_player_stats(data, data->stats[i], ft_player_lstlast(data->players));
	}
	data->players = sort_players(data->players);
}
