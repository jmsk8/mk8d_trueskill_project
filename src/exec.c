#include "../includes/mk8d_trueskill.h"

int	is_valid_cmd(char **cmd)
{
	if (!ft_strncmp("help", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("Too many arguments\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		else if (!cmd[1])
			return (1);
	}
	if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && cmd[2] && cmd[3])
		{
			printf("Too many arguments. Usage: [show -arg]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (!cmd[1])
		{
			printf("Invalid arguments. Usage: [show -arg] required\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && !cmd[2])
			return (1);
		if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && cmd[2])
			return (1);
		printf("Invalid arguments. Usage: [show -arg] required\n");
		printf("Enter help for more information.\n");
		return (0);
	}
	if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("add: Argument required. Example: [add -player]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("add: Too many arguments. Example: [add -player]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (!ft_strncmp(cmd[1], "-player", MAX_LENGTH))
			return (1);
		if (ft_strncmp(cmd[1], "-player", MAX_LENGTH))
		{
			printf("add: Invalid argument. Example: [add -player]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
	}
	if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
	{
		if (!cmd[1])
		{
			printf("delete: Argument required. Example: [delete -player]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (cmd[2] && cmd[3])
		{
			printf("delete: Too many arguments. Example: [delete -player]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		if (cmd[1] && ft_strlen(cmd[1]) > 1)
			return (1);
	}
	if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("start: Too many arguments. Example: [start]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		return (1);
	}
	if (!ft_strncmp("save", cmd[0], MAX_LENGTH))
	{
		if (cmd[1])
		{
			printf("save: Too many arguments. Example: [save]\n");
			printf("Enter help for more information.\n");
			return (0);
		}
		return (1);
	}
	printf("Invalid command\n");
	printf("Enter help for more information.\n");
	return (0);
}

void	exec_cmd(t_data *data, char **cmd)
{
	char	*input = NULL;

	if (!ft_strncmp("help", cmd[0], MAX_LENGTH))
		help_cmd();
	else if (!ft_strncmp("show", cmd[0], MAX_LENGTH))
	{
		if (cmd[1] && !cmd[2] && !ft_strncmp("-stats", cmd[1], MAX_LENGTH))
			display_players_stats(data->players);
		else if (!ft_strncmp("-stats", cmd[1], MAX_LENGTH) && cmd[2])
			display_player_stats(data->players, cmd[2]);
	}
	else if (!ft_strncmp("add", cmd[0], MAX_LENGTH))
	{
		if (!ft_strncmp("-player", cmd[1], MAX_LENGTH))
			add_player(data);
	}
	else if (!ft_strncmp("delete", cmd[0], MAX_LENGTH))
		delete_player(data, cmd[1]);
	else if (!ft_strncmp("start", cmd[0], MAX_LENGTH))
	{
		prepare_tournament(data);
		if (!data->tournament_players)
			return ;
		if (!data->tournament_players->next)
		{
			printf("Need more than one player.\n");
			return ;
		}
		printf("\033[2J\033[H");
		display_competing_players(data->tournament_players);
		while (1)
		{
			printf("Are you sure you want to confirm your choice and generate the result? (y/n)\n");
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
				printf("Proceeding...\n");
				trueskill_generator(data);
				printf("New:\n");
				display_players_stats(data->players);
				break ;
			}
			else
				printf("Invalid input\n");
			free(input);
		}
	}
	else if (!ft_strncmp("save", cmd[0], MAX_LENGTH))
	{
		display_players_stats(data->players);
		while (1)
		{
			input = get_input("save this stats?(y,n)");
			if (!input || !ft_strncmp("n", input, MAX_LENGTH))
				return ;
			else if (!ft_strncmp("y", input, MAX_LENGTH))
			{
				save_file(data);
				printf("saving..\n");
				usleep(1000000);
				printf("\033[2J\033[H");
				return ;
			}
			else
				printf("invalid argument");
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
