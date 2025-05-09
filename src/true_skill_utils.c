#include "../includes/mk8d_trueskill.h"

char	**read_result(t_data *data)
{
	int		fd;
	int		is_error;
	char	**map;

	map = NULL;
	is_error = 0;

	fd = open("data/tmp_data.log", O_RDONLY);
	if (fd > 0 && BUFFER_SIZE > 0)
	{
		map = ft_split(get_stats_array(fd, &is_error), '\n');
		close(fd);
		if (!map)
			ft_error("Memory error\n", data, 1);
	}
	else
		ft_error("Error\nFailed to open file\n", data, 1);
	return (map);
}

void	ensure_directory_exists(const char *dir)
{
	struct stat st = {0};
	if (stat(dir, &st) == -1)
		mkdir(dir, 0777);
}

void save_tmp_data(t_player *players)
{
	ensure_directory_exists("data");

	FILE *file = fopen("data/tmp_data.log", "w");
	if (!file)
	{
		perror("Error opening tmp_data.log");
		return;
	}

	t_player *player = players;
	while (player)
	{
		fprintf(file, "%s = mu=%.3f, sigma=%.3f pos=%d\n", player->name, player->mu, player->sigma, player->pos);
		player = player->next;
	}

	fclose(file);
}

void save_old_file(void)
{
	time_t rawtime;
	struct tm *timeinfo;
	char filename[128];

	ensure_directory_exists("data/old");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(filename, sizeof(filename), "data/old/%Y%m%d_%H%M%S.log", timeinfo);

	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}

	FILE *source = fopen("data/data.log", "r");
	if (source != NULL)
	{
		char buffer[1024];
		size_t bytesRead;
		while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0)
			fwrite(buffer, 1, bytesRead, file);
		fclose(source);
	}
	else
	{
		perror("Error opening source file (data/data.log)");
	}

	fclose(file);
}

void save_new_data(t_player *players, char *date)
{
	ensure_directory_exists("data");
	players =  sort_players(players);
	FILE *file = fopen("data/data.log", "w");
	if (!file)
	{
		perror("Error opening tmp_data.log");
		return;
	}

	fprintf(file, "%s\n", date);
	t_player *player = players;
	while (player)
	{
		fprintf(file, "%s = mu=%.3f, sigma=%.3f\n", player->name, player->mu, player->sigma);
		player = player->next;
	}

	fclose(file);
}

void	refresh_player_struct(t_player *player, t_player *player_tour)
{
	t_player	*head = player;

	while (player_tour)
	{
		player = head;
		while (player)
		{
			if (!ft_strncmp(player->name, player_tour->name, ft_strlen(player_tour->name)))
			{
				player->mu = player_tour->mu;
				player->sigma = player_tour->sigma;
				break ;
			}
			player = player->next;
		}
		player_tour = player_tour->next;
	}
}


static int get_num_of_player2(char **stats)
{
	int	num = 0;
	while(stats[num] && ft_strlen(stats[num]) > 16)
		num++;
	return (num);
}

void	refresh_tournament_player_struct(t_data *data)
{
	ft_player_lstclear(&data->tournament_players);
	data->tournament_players = NULL;
	int num_of_player = get_num_of_player2(data->resul_stats);
	data->tournament_players = ft_player_lstnew();
	if (!data->tournament_players)
		ft_error("malloc error\n", data, 1);
	get_player_stats(data, data->resul_stats[0], ft_player_lstlast(data->tournament_players));
	for (int i = 1; i < num_of_player; i++)
	{
		if (!ft_player_lstadd_back(&data->tournament_players, ft_player_lstnew()))
			ft_error("malloc error\n", data, 1);
		get_player_stats(data, data->resul_stats[i], ft_player_lstlast(data->tournament_players));
	}
}
