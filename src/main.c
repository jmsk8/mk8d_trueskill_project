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

int	main()
{
	t_data		data;
	t_player	*player;

	set_data(&data);
	data.stats = read_stats(&data);
	init_player_struct(&data);
	for(int i = 0; data.stats[i]; i++)
		printf("%s\n", data.stats[i]);
	init_player_struct(&data);
	player = data.players;
	printf("\n%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma");
	printf("--------------------------------------------\n");
	while (player)
	{
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f\n" RESET, player->sigma);
		player = player->next;
	}
	save_to_file(data.players);
	end(&data, 0);
}
