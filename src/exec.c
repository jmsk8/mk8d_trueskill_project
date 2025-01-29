#include "../includes/mk8d_trueskill.h"

void	display_players_stats(t_player *player)
{
	printf("\n%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma");
	printf("--------------------------------------------\n");
	while (player)
	{
		printf(BOLD_RED "%-20s" RESET, player->name);
		printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
		printf(BOLD_GREEN "%-20.3f\n" RESET, player->sigma);
		player = player->next;
	}
}

void	display_player_stats(t_player *player, char *name)
{
	while (player)
	{
		if ((!ft_strncmp(name, player->name, MAX_LENGTH)))
		{
			printf("\n%-20s%-20s%-20s\n", "Player Name", "Mu", "Sigma");
			printf("--------------------------------------------\n");
			printf(BOLD_RED "%-20s" RESET, player->name);
			printf(BOLD_BLUE "%-20.3f" RESET, player->mu);
			printf(BOLD_GREEN "%-20.3f\n" RESET, player->sigma);
			return ;
		}
		player = player->next;
	}
	printf("player [%s] not found\n", name);
}

void	help_cmd()
{
	printf("\n%-20s%-20s\n", "commande", "argument");
	printf("\n%-20s%-20s", "show", "-stats  pour voir un tableaux de tout les joueurs\n");
	printf("\n%-40s", 	"                    -stats player  pour les stats d'un joueur en particulier\n");
}

char	*get_input(char *str)
{
	char	*input = NULL;
	while (1)
	{
		input = readline(str);
		if (line_is_empty(input))
		{
			free(input);
			input = NULL;
			continue ;
		}
		if (input == NULL)
		{
			printf("abort..\n");
			return (NULL);
		}
		if (input)
			break ;
	}
	return (input);
}

int	is_valid_cmd(char **cmd)
{
	if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("arguments error. [show -arg] needed\n");
			return (0);
		}
		else if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && !cmd[2])
			return (1);
		else if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && cmd[2] && !cmd[3])
			return (1);
		else
		{
			printf("too many arguments\n");
			return (0);
		}
	}
	if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("argument needed. Exemple: [add player]\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("too many argument. Exemple: [add player]\n");
			return (0);
		}
		else
			return (1);
	}
	if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("argument needed. Exemple: [delete player]\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("too many argument. Exemple: [delete player]\n");
			return (0);
		}
		else
			return (1);
	}
	if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("too many arguments. exemple [start]\n");
			return (0);
		}
		return (1);
	}
	printf("invalid command\n");
	return (0);
}

void	add_player(t_data *data)
{
	char	*mu = NULL;
	char	*sigma = NULL;
	t_player	*player = ft_player_lstnew();
	if (!player)
		ft_error("malloc error\n", data, 1);
	player->name = get_input("name: ");
	if (!player->name)
	{
		free(player);
		return ;
	}
	mu = get_input("mu: ");
	if (!mu)
	{
		free(player->name);
		free(player);
		return ;
	}
	sigma = get_input("sigma: ");
	if (!sigma)
	{
		free(mu);
		free(player->name);
		free(player);
		return ;
	}
	player->mu = string_to_float(mu);
	player->sigma = string_to_float(sigma);
	free(mu);
	free(sigma);
	ft_player_lstadd_back(&data->players, player);
}

void	delete_player(t_data *data, char *name)
{
	t_player	*player = data->players;
	t_player	*next_tmp = NULL;
	t_player	*prev_tmp = NULL;

	while (1)
	{
		if (!strncmp(name, player->name, MAX_LENGTH))
			break ;
		player = player->next;
	}

	if (player)
	{
		free(player->name);
		player->name = NULL;
		if (!player->prev)
		{
			next_tmp = player->next;
			free(player);
			data->players = next_tmp;
			data->players->prev = NULL;
			return ;
		}
		else if (!player->next)
		{
			prev_tmp = player->prev;
			free(player);
			prev_tmp->next = NULL;
			return ;
		}
		else
		{
			prev_tmp = player->prev;
			next_tmp = player->next;
			free(player);
			prev_tmp->next = next_tmp;
			next_tmp->prev = prev_tmp;
		}
		return ;
	}
}

int	check_player_list(t_player *player, char *str)
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

t_player	*get_player(t_player *player, t_player *tour_player, char *str)
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

char	*genere_prompt(int i)
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
	int			i = 1;
	char		*prompt;


	printf("put the Player in the right order. 1er 2e 3e...\n Enter EXIT when its done\n");
	printf("--------------------------------------------\n");
	while (1)
	{
		input = get_input("1er: ");
		if (!input)
			return ;
		tmp = get_player(data->players, NULL, input);
		if (tmp)
			break ;
	}
	player = ft_player_lstnew_stats(input, tmp->mu, tmp->sigma);
	player->pos = i;
	input = NULL;
	while (1)
	{
		prompt = genere_prompt(i);
		input = get_input(prompt);
		if (!ft_strncmp("+", input, MAX_LENGTH))
		{
			i++;
			free(input);
			free(prompt);
			input = NULL;
			continue ;
		}
		free(prompt);
		tmp = NULL;
		if (!input)
		{
			ft_player_lstclear(&player);
			return ;
		}
		if(! ft_strncmp("EXIT", input, MAX_LENGTH))
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
			ft_player_lstlast(player)->pos = i;
		}
		input = NULL;
	}
	data->tournament_players = player;

}

void	exec_cmd(t_data *data, char **cmd)
{
	char	*input = NULL;

	if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (cmd[1] && !cmd[2] && !ft_strncmp("-stats", cmd[1], MAX_LENGTH))
			display_players_stats(data->players);
		else if (cmd[2])
			display_player_stats(data->players, cmd[2]);
	}
	else if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
		add_player(data);
	else if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
		delete_player(data, cmd[1]);
	else if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		prepare_tournament(data);
		if (!data->tournament_players)
			return ;
		display_players_stats(data->tournament_players);
		while (1)
		{
			printf("confirm your choice and generate the result ?(y,n)\n");
			input = get_input("> ");
			if (!input || !ft_strncmp("n", input, MAX_LENGTH))
			{
				if (input)
					free(input);
				ft_player_lstclear(&data->tournament_players);
				break ;
			}
				if (!ft_strncmp("y", input, MAX_LENGTH))
				{
					free(input);
					printf("proceed..\n ");
					trueskill_generator(data);
					printf("new:\n");
					display_players_stats(data->tournament_players);
					break ;
				}
			else
				printf("invalid argument\n");
			free(input);
		}

	}
	return ;
}

int	exec(t_data *data)
{
	if (!is_valid_cmd(data->cmd))
		return (0);
	exec_cmd(data, data->cmd);
	return (0);
}
