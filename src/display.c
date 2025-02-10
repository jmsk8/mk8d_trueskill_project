#include "../includes/mk8d_trueskill.h"

void quartile_generator(t_player *player, double *q1, double *q2, double *q3, int count)
{
	int q1_idx, q2_idx, q3_idx;
	t_player *tmp = player;
	int	pair = 0;

	if (count % 2 != 0)
		pair = 1;
	q3_idx = (count + pair) / 4;
	q2_idx = (count + pair) / 2;
	q1_idx = 3 * (count + pair) / 4;

	for (int i = 0; i < count; i++)
	{
		double points = tmp->mu - (3 * tmp->sigma);

		if (i == q3_idx)
			*q3 = points;
		if (i == q2_idx)
			*q2 = points;
		if (i == q1_idx)
			*q1 = points;

		tmp = tmp->next;
	}

	 printf("Quartiles : Q1 = %.3f, Q2 = %.3f, Q3 = %.3f\n", *q1, *q2, *q3);
}

void display_players_stats(t_player *player, int num_of_players)
{
	double pos_q1 = 0;
	double pos_q2 = 0;
	double pos_q3 = 0;

	quartile_generator(player, &pos_q1, &pos_q2, &pos_q3, num_of_players);

	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
	printf("--------------------------------------------------------------------------\n");

	while (player)
	{
		double points = player->mu - (3 * player->sigma);

		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);

		if (points > pos_q3)
			printf(RANK_S "%-20.3f\n" RESET, points);
		else if (points > pos_q2)
			printf(RANK_A "%-20.3f\n" RESET, points);
		else if (points > pos_q1)
			printf(RANK_B "%-20.3f\n" RESET, points);
		else
			printf(RANK_C "%-20.3f\n" RESET, points);

		player = player->next;
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
