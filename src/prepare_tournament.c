#include "../includes/mk8d_trueskill.h"

static char	*get_input2(char *str)
{
	char	*input = NULL;
	while (1)
	{
		input = readline(str);
		if (input == NULL)
		{
			printf("abort..\n");
			return (NULL);
		}
		else if (line_is_empty(input))
		{
			free(input);
			input = NULL;
			return (ft_strdup("+"));
		}
		if (input)
			break ;
	}
	return (input);
}

static int	check_player_list(t_player *player, char *str)
{
	t_player	*tmp = player;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->name, MAX_LENGTH))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static t_player	*get_player(t_player *player, t_player *tour_player, char *str)
{
	if (tour_player)
	{
		if (!check_player_list(tour_player, str))
		{
			printf("player is already in the list\n");
			return (NULL);
		}
	}
	while (player)
	{
		if (!ft_strncmp(str, player->name, MAX_LENGTH))
				return (player);
		player = player->next;
	}
	printf("player not found\n");
	return (NULL);
}

static char	*genere_prompt(int i)
{
	char *res;
	int len;

	len = snprintf(NULL, 0, "%d", i);
	res = (char *)malloc(len + 4 + 1);
	if (!res)
		return NULL;

	snprintf(res, len + 4 + 1, "%de: ", i);
	return res;
}

void prepare_tournament(t_data *data)
{
	t_player	*player = NULL;
	t_player	*tmp = NULL;
	char		*input = NULL;
	int			i = 0;
	char		*prompt;
	int			gap = 0;

	while (1)
	{
		printf("\033[2J\033[H");
		display_players_stats(data->players, data->num_of_player);
		display_competing_players(player);
		printf("Put the players in the correct order: 1st, 2nd, 3rd... Press ENTER to move to the next position.\nType DONE when finished.\n");
		printf("--------------------------------------------\n");
		input = get_input2("1er: ");
		if (!input)
			return ;
		add_history(input);
		tmp = get_player(data->players, NULL, input);
		if (tmp)
			break ;
	}
	player = ft_player_lstnew_stats(input, tmp->mu, tmp->sigma);
	player->pos = i;
	input = NULL;
	while (1)
	{
		printf("\033[2J\033[H");
		display_players_stats(data->players, data->num_of_player);
		display_competing_players(player);
		printf("Put the players in the correct order: 1st, 2nd, 3rd... Press ENTER to move to the next position.\nType DONE when finished.\n");
		printf("--------------------------------------------\n");
		prompt = genere_prompt(i + 1);
		input = get_input2(prompt);
		if (!input)
		{
			ft_player_lstclear(&player);
			return ;
		}
		if (!ft_strncmp("+", input, MAX_LENGTH))
		{
			if (!i)
				i += gap;
			else
				i += gap - 1;
			i++;
			gap = 0;
			free(input);
			free(prompt);
			input = NULL;
			continue ;
		}
		add_history(input);
		free(prompt);
		tmp = NULL;
		if(! ft_strncmp("DONE", input, MAX_LENGTH))
		{
			free(input);
			break ;
		}
		tmp = get_player(data->players, player, input);
		if (!tmp)
		{
			free(input);
			continue ;
		}
		else
		{
			if (!ft_player_lstadd_back(&player, ft_player_lstnew_stats(input, tmp->mu, tmp->sigma)))
			{
				ft_player_lstclear(&player);
				printf("malloc error\n");
				free(input);
				return ;
			}
			gap++;
			ft_player_lstlast(player)->pos = i;
		}
		input = NULL;
	}
	data->tournament_players = player;

}
