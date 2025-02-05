#include "../includes/mk8d_trueskill.h"

void	save_data(t_data *data)
{
	char	*input = NULL;
	printf("save the result ?(y,n)\n");
	input = get_input("> ");
	if (input || !ft_strncmp("n", input, MAX_LENGTH))
	{
		printf("\033[2J\033[H");
		printf("suppressing...\n");
		usleep(1000000);
		printf("\033[2J\033[H");
	}
	else if (!ft_strncmp("y", input, MAX_LENGTH))
	{
		printf("\033[2J\033[H");
		printf("saving...\n");
		save_old_file(data->players);
		refresh_player_struct(data->players, data->tournament_players);
		save_new_data(data->players);
		usleep(1000000);
		printf("\033[2J\033[H");
	}
}

void	get_points(float scors[12], t_player *player)
{
	int	i = 0;
	while (player)
	{
		scors[i] = player->mu - (3 * player->sigma);
		i++;
		player = player->next;
	}
}

void get_diff_points(float scors[12], t_player *player)
{
	int i = 0;
	float new_scors[12];

	while (player)
	{
		new_scors[i] = player->mu - (3 * player->sigma);
		i++;
		player = player->next;
	}

	for (int y = 0; y < i; y++)
	{
		if (new_scors[y] < scors[y])
		{
			scors[y] = -(fabs(scors[y] - new_scors[y]));
		}
		else
		{
			scors[y] = fabs(scors[y] - new_scors[y]);
		}
	}
}

void	trueskill_generator(t_data *data)
{
	pid_t	pid;
	char	*python = "/usr/bin/python3";
	char	*script = "Trueskill.py";
	char	*args[] = {python, script, NULL};
	char	*envp[] = {NULL};
	float	scors[12];

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
	display_competing_players_result(data->tournament_players);
	get_points(scors, data->tournament_players);
	data->resul_stats = read_result(data);
	refresh_tournament_player_struct(data);
	get_diff_points(scors, data->tournament_players);
	printf("new:\n");
	display_competing_players_result2(data->tournament_players, scors);
	save_data(data);
	remove("data/tmp_data.log");
	return ;
}
