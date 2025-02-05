#include "../includes/mk8d_trueskill.h"

void	display_players_stats(t_player *player, int num_of_player)
{
	double gap = (double)num_of_player / 4.0;
	int quartiles = 4;
	int i = 1;

	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
	printf("--------------------------------------------------------------------------\n");
	while (player)
	{
		double points = player->mu - (3 * player->sigma);
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
		if (quartiles == 4)
			printf(RANK_S "%-20.3f\n" RESET, points);
		else if (quartiles == 3)
			printf(RANK_A "%-20.3f\n" RESET, points);
		else if (quartiles == 2)
			printf(RANK_B "%-20.3f\n" RESET, points);
		else if (quartiles == 1)
			printf(RANK_C "%-20.3f\n" RESET, points);
		else
			printf(RANK_C "%-20.3f\n" RESET, points);

		player = player->next;
		if (i >= (int)gap)
		{
			quartiles--;
			i = 1;
		}
		else
			i++;
	}
	printf("--------------------------------------------------------------------------\n");
}

void	display_competing_players_result(t_player *player)
{
	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
	printf("--------------------------------------------------------------------------\n");
	while (player)
	{
		double points = player->mu - (3 * player->sigma);
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
		printf(BOLD_YELLOW "%-20.3f\n" RESET, points);
		player = player->next;
	}
	printf("--------------------------------------------------------------------------\n");
}

void	display_competing_players_result2(t_player *player, float diff[12])
{
	int	i = 0;
	printf("\n%-20s%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points", "Diff");
	printf("------------------------------------------------------------------------------------------\n");
	while (player)
	{
		double points = player->mu - (3 * player->sigma);
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
		printf(BOLD_YELLOW "%-20.3f" RESET, points);
		if (diff[i] > 0)
			printf(BOLD_GREEN "+%-20.3f\n" RESET, diff[i]);
		else
			printf(BOLD_RED "%-20.3f\n" RESET, diff[i]);
		player = player->next;
		i++;
	}
	printf("------------------------------------------------------------------------------------------\n");
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
	printf("--------------------------------------------------------------------------\n");
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
			printf("--------------------------------------------------------------------------\n");
			return ;
		}
		player = player->next;
	}
	printf("player [%s] not found\n", name);
}
