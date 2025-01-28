#include "../includes/mk8d_trueskill.h"

void ensure_directory_exists(const char *dir)
{
	struct stat st = {0};
	if (stat(dir, &st) == -1)
	{
		if (mkdir(dir, 0700) == -1)
		{
			perror("Error creating directory");
		}
	}
}

void save_to_file(t_player *players)
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
	t_player *player = players;
	while (player != NULL)
	{
		fprintf(file, "%s = mu=%.3f, sigma=%.3f\n", player->name, player->mu, player->sigma);
		player = player->next;
	}
	fclose(file);
}

void	prompt(t_data *data)
{
	while (1)
	{
		data->input = readline("mk8d_TrueSkill_Generator > ");
		if (data->input == NULL)
			return ;
		if (line_is_empty(data->input))
		{
			free(data->input);
			data->input = NULL;
			continue ;
		}
		add_history(data->input);
		if (!parsing(data))
			continue ;
		exec(data);
		free_tmp_var(data);
	}
}

int	main()
{
	t_data		data;

	set_data(&data);
	signals();
	data.stats = read_stats(&data);
	init_player_struct(&data);
	prompt(&data);
	save_to_file(data.players);
	printf("exit..\n");
	end(&data, 0);
}
