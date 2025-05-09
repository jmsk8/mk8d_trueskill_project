#include "../includes/mk8d_trueskill.h"

static double calculate_quartile(double *points, int count, double position)
{
	int index = (int)position;
	double fraction = position - index;

	if (index >= count - 1)
		return points[count - 1];
	return points[index] + fraction * (points[index + 1] - points[index]);
}

void quartile_generator(t_player *player, double *q1, double *q2, double *q3, int count)
{
	if (count < 2)
		return;

	double *points = (double *)malloc(count * sizeof(double));
	if (!points)
		return;

	t_player *tmp = player;
	for (int i = 0; i < count; i++)
	{
		points[i] = tmp->mu - (3 * tmp->sigma);
		tmp = tmp->next;
	}

	double pos_q3 = 0.25 * (count + 1) - 1;
	double pos_q2 = 0.50 * (count + 1) - 1;
	double pos_q1 = 0.75 * (count + 1) - 1;

	*q3 = calculate_quartile(points, count, pos_q3);
	*q2 = calculate_quartile(points, count, pos_q2);
	*q1 = calculate_quartile(points, count, pos_q1);

	printf("Quartiles : Q1 = %.3f, Q2 = %.3f, Q3 = %.3f\n", *q1, *q2, *q3);

	free(points);
}

void ecart_type_generator(t_player *player, double *mu, double *sigma)
{
	int	count = 0;

	t_player *tmp = player;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (count < 2)
		return;
	double *points = (double *)malloc(count * sizeof(double));
	if (!points)
		return;
	for (int i = 0; i < count; i++)
	{
		points[i] = player->mu - (3 * player->sigma);
		*mu += points[i];
		player = player->next;
	}
	*mu /= count;
	double variance = 0;
	for (int i = 0; i < count; i++)
		variance += (points[i] - *mu) * (points[i] - *mu);
	variance /= count;
	*sigma = sqrt(variance);

	printf("mu = %.3f, sigma = %.3f\n", *mu, *sigma);
	printf("rank S > %.3f, rank A > %.3f, rank B < %.3f, rank c < %.3f,\n", (*mu +*sigma), *mu, *mu, (*mu - *sigma));
	free(points);
}

t_player	*sort_player(t_player *player)
{
	t_player	*tmp = NULL;

	while (player)
	{
		if (player && player->sigma < 4)
		{
			ft_player_lstadd_back(&tmp, ft_player_lstnew());
			ft_player_lstlast(tmp)->name = ft_strdup(player->name);
			ft_player_lstlast(tmp)->mu = player->mu;
			ft_player_lstlast(tmp)->sigma = player->sigma;
		}
		player = player->next;
	}
	return (tmp);
}

void display_players_stats(t_player *player, char *date)
{
	double		mu = 0;
	double		sigma = 0;
	t_player	*tmp_player = sort_player(player);

	printf("date: %s\n", date);
	ecart_type_generator(tmp_player, &mu, &sigma);
	printf("\n%-20s%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma", "Points");
	printf("--------------------------------------------------------------------------\n");

	while (tmp_player)
	{
		double points = tmp_player->mu - (3 * tmp_player->sigma);

		printf(BOLD_RED "%-20s" RESET, tmp_player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, tmp_player->mu);
		printf(BOLD_GREEN "%-20.3f" RESET, tmp_player->sigma);

		if (points > mu + sigma )
			printf(RANK_S "%-20.3f\n" RESET, points);
		else if (points > mu && points < mu + sigma)
			printf(RANK_A "%-20.3f\n" RESET, points);
		else if (points < mu && points > mu - sigma)
			printf(RANK_B "%-20.3f\n" RESET, points);
		else if (points < mu - sigma )
			printf(RANK_C "%-20.3f\n" RESET, points);

		tmp_player = tmp_player->next;
	}
	while (player)
	{
		if (player && player->sigma > 4)
		{
			double points = player->mu - (3 * player->sigma);

			printf(BOLD_RED "%-20s" RESET, player->name);
			printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
			printf(BOLD_GREEN "%-20.3f" RESET, player->sigma);
			printf("%-20.3f\n", points);
		}
		player = player->next;
	}
	printf("--------------------------------------------------------------------------\n");
	ft_player_lstclear(&tmp_player);
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
