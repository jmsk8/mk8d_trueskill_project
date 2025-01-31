#include "../includes/mk8d_trueskill.h"

void	display_players_stats(t_player *player, int num_of_player)
{
	double gap = (double)num_of_player / 4.0;
	int quartiles = 4;
	int i = 1;

	player = sort_players(player);
	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
	printf("--------------------------------------------------------------------------\n");
	while (player)
	{
		double points = player->mu - (3 * player->sigma);
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
		if (quartiles == 4)
			printf(BOLD_YELLOW "%-20.3f\n" RESET, points);
		else if (quartiles == 3)
			printf(BOLD_GRAY "%-20.3f\n" RESET, points);
		else if (quartiles == 2)
			printf(BOLD_ORANGE "%-20.3f\n" RESET, points);
		else if (quartiles == 1)
			printf(BOLD_BROWN "%-20.3f\n" RESET, points);
		else
			printf(BOLD_BROWN "%-20.3f\n" RESET, points);

		player = player->next;
		if (i >= (int)gap)
		{
			quartiles--;
			i = 1;
		}
		else
			i++;
	}
}

void	display_competing_players(t_player *player)
{
	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Position");
	printf("--------------------------------------------------------------------------\n");
	while (player)
	{
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
		printf(BOLD_YELLOW "%d\n" RESET, player->pos + 1);
		player = player->next;
	}
}

void	display_player_stats(t_player *player, char *name)
{
	while (player)
	{
		if ((!ft_strncmp(name, player->name, MAX_LENGTH)))
		{
			printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
			printf("--------------------------------------------------------------------------\n");
			double points = player->mu - (3 * player->sigma);
			printf(BOLD_RED "%-20s" RESET, player->name);
			printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
			printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
			printf(BOLD_YELLOW "%-20.3f\n" RESET, points);
			return ;
		}
		player = player->next;
	}
	printf("player [%s] not found\n", name);
}
