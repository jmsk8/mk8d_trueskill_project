#include "../includes/mk8d_trueskill.h"

void save_data_file(char **data)
{
	time_t rawtime;
	struct tm *timeinfo;
	char filename[128];
	int	i = 0;

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
	while (data[i])
	{
		fprintf(file, "%s\n", data[i]);
		i++;
	}
	fclose(file);
}

void save_file(t_data *data)
{
	save_data_file(data->stats);
	save_new_data(data->players);
}

void	help_cmd()
{
	printf("\n%-20s%-20s\n", "[commande]", "[argument]");
	printf("\n%-20s%-20s", "[show]", "[-stats]  pour voir un tableau de tout les joueurs.\n");
	printf("\n%-40s", 	"                    [-stats player]  pour voir les stats d'un joueur en particulier.\n");
	printf("\n%-20s%-20s", "[add]", "[-player]  pour ajouter un joueur.\n");
	printf("\n%-20s%-20s", "[delete]", "[playe_name] (ex [delete Tony]) pour supprimer un joueur.\n");
	printf("\n%-20s%-20s", "[start]", "pour generer les resultats d'un tournoi.\n");
	printf("\n%-20s%-20s", "[save]", "pour sauvegarder les modification données.\n");
	printf("\n");
}

int	is_valid_cmd(char **cmd)
{
	if (!ft_strncmp("help", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("too many arguments\n");
			return (0);
		}
		else if (!cmd[1])
			return (1);
	}
	if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("arguments error. [show -arg] needed\n");
			return (0);
		}
		else if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && !cmd[2])
			return (1);
		else if (ft_strncmp("-stats", cmd[1], MAX_LENGTH) && !cmd[2])
		{
			printf("show: invalid argument\n");
			return (0);
		}
		else if (ft_strncmp("-stats", cmd[1], MAX_LENGTH) && cmd[2] && !cmd[3])
		{
			printf("too many arguments, [show -arg] needed\n");
			return (0);
		}
	}
	if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("add: argument needed. Exemple: [add -player]\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("add: too many argument. Exemple: [add -player]\n");
			return (0);
		}
		if (!ft_strncmp(cmd[1], "-player", MAX_LENGTH))
			return (1);
		if (ft_strncmp(cmd[1], "-player", MAX_LENGTH))
		{
			printf("add: bad argument. Exemple: [add -player]\n");
			return (0);
		}
	}
	if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("delete: argument needed. Exemple: [delete -player]\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("delete: too many argument. Exemple: [delete -player]\n");
			return (0);
		}
		if (cmd[1] && ft_strlen(cmd[1]) > 1)
			return (1);
	}
	if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("start: too many arguments. exemple [start]\n");
			return (0);
		}
		return (1);
	}
	if (!ft_strncmp("save", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("save: too many arguments. exemple [save]\n");
			return (0);
		}
		return (1);
	}
	printf("invalid command\n");
	return (0);
}

void	add_player(t_data *data)
{
	char		*mu = NULL;
	char		*sigma = NULL;
	t_player	*tmp = data->players;
	t_player	*player = ft_player_lstnew();

	if (!player)
		ft_error("malloc error\n", data, 1);
	player->name = get_input("name: ");
	while (tmp)
	{
		if (!strncmp(tmp->name, player->name, MAX_LENGTH))
			break ;
		tmp = tmp->next;
	}
	if (tmp || !player->name)
	{
		printf("player already exist\n");
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
	data->players = sort_players(data->players);
}

void	delete_player(t_data *data, char *name)
{
	t_player	*player = data->players;
	t_player	*next_tmp = NULL;
	t_player	*prev_tmp = NULL;

	while (player)
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
	else
		printf("player not found\n");
	data->players = sort_players(data->players);
}

void	exec_cmd(t_data *data, char **cmd)
{
	char	*input = NULL;

	if (!ft_strncmp("help", cmd[0], MAX_LENGTH))
		help_cmd();
	else if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (cmd[1] && !cmd[2] && !ft_strncmp("-stats", cmd[1], MAX_LENGTH))
			display_players_stats(data->players, data->num_of_player);
		else if (!ft_strncmp("-start", cmd[1], MAX_LENGTH) && cmd[2])
			display_player_stats(data->players, cmd[2]);
	}
	else if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
	{
		if (!ft_strncmp("-player", cmd[1], MAX_LENGTH))
			add_player(data);
	}
	else if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
	{
		delete_player(data, cmd[1]);
	}
	else if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		prepare_tournament(data);
		if (!data->tournament_players)
			return ;
		display_competing_players(data->tournament_players);
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
					display_players_stats(data->players, data->num_of_player);
					break ;
				}
			else
				printf("invalid argument\n");
			free(input);
		}
	}
	else if (!ft_strncmp("save", cmd[0], MAX_LENGTH))
		save_file(data);
	return ;
}

int	exec(t_data *data)
{
	if (!is_valid_cmd(data->cmd))
		return (0);
	exec_cmd(data, data->cmd);
	return (0);
}
