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

static void	ensure_directory_exists(const char *dir)
{
	struct stat st = {0};
	if (stat(dir, &st) == -1)
		mkdir(dir, 0777);
}

static void save_tmp_data(t_player *players)
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

void	refresh_tournament_player_struct(t_data *data)
{
	ft_player_lstclear(&data->tournament_players);
	int num_of_player = get_num_of_player(data->resul_stats);
	data->tournament_players = ft_player_lstnew();
	get_player_stats(data, data->resul_stats[0], ft_player_lstlast(data->tournament_players));
	for (int i = 1; i < num_of_player; i++)
	{
		if (!ft_player_lstadd_back(&data->tournament_players, ft_player_lstnew()))
			ft_error("malloc error\n", data, 1);
		get_player_stats(data, data->resul_stats[i], ft_player_lstlast(data->tournament_players));
	}
}

void	trueskill_generator(t_data *data)
{
	pid_t	pid;
	char	*python = "/usr/bin/python3";
	char	*script = "Trueskill.py";
	char	*args[] = {python, script, NULL};
	char	*envp[] = {NULL};

	save_tmp_data(data->tournament_players);
	pid = fork();
	if (pid == -1)
		ft_error("fork error\n", data, 1);
	if (!pid)
	{
		execve(python, args, envp);
		perror("execve failed");
		exit(1);
	}
	wait(NULL);
	usleep(1000000);
	printf("\033[2J\033[H");
	printf("old:\n");
	display_players_stats(data->tournament_players);
	data->resul_stats = read_result(data);
	refresh_tournament_player_struct(data);
	remove("data/tmp_data.log");
	return ;
}
