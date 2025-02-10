/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:04 by jmiccio           #+#    #+#             */
/*   Updated: 2025/02/08 15:50:39 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mk8d_trueskill.h"

int	check_arg(char *str)
{
	while (*str)
	{
		if (!isdigit(*str) && *str != '.')
		{
			printf("Invalid argument. Exemple: 4.536\n");
			return (0);
		}
		str++;
	}
	return (1);
}

void	add_player(t_data *data)
{
	char		*mu = NULL;
	char		*sigma = NULL;
	t_player	*tmp;
	t_player	*player = ft_player_lstnew();

	if (!player)
		ft_error("malloc error\n", data, 1);
	while (1)
	{
		player->name = get_input("name: ");
		if (!player->name)
		{
			free(player);
			return ;
		}
		tmp = data->players;
		while (tmp)
		{
			if (!strncmp(tmp->name, player->name, MAX_LENGTH))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
		{
			printf("player already exist\n");
			free(player->name);
		}
		else
			break ;
	}
	while (1)
	{
		mu = get_input("mu: ");
		if (!mu)
		{
			free(player->name);
			free(player);
			return ;
		}
		if (check_arg(mu))
			break ;
		else
			free(mu);
	}
	while (1)
	{
		sigma = get_input("sigma: ");
		if (!sigma)
		{
			free(mu);
			free(player->name);
			free(player);
			return ;
		}
		if (check_arg(sigma))
			break ;
		else
			free(sigma);
	}
	player->mu = string_to_float(mu);
	player->sigma = string_to_float(sigma);
	free(mu);
	free(sigma);
	ft_player_lstadd_back(&data->players, player);
	data->num_of_player++;
	data->players = sort_players(data->players);
}

void delete_player(t_data *data, char *name)
{
	t_player *player = data->players;
	t_player *prev_player = NULL;

	while (player)
	{
		if (!strncmp(name, player->name, MAX_LENGTH))
			break;
		prev_player = player;
		player = player->next;
	}

	if (player)
	{
		free(player->name);
		if (prev_player)
			prev_player->next = player->next;
		else
			data->players = player->next;
		free(player);
		data->num_of_player--;
	}
	else
	{
		printf("player not found\n");
	}
}

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

void help_cmd()
{
	printf("\n%-20s%-20s\n", "[command]", "[argument]");
	printf("\n%-20s%-20s", "[show]", "[-stats]  to display a table of all players.\n");
	printf("\n%-40s", 	"                    [-stats player]  to view the stats of a specific player.\n");
	printf("\n%-20s%-20s", "[add]", "[-player]  to add a player.\n");
	printf("\n%-20s%-20s", "[delete]", "[player_name] (e.g., [delete Tony]) to remove a player.\n");
	printf("\n%-20s%-20s", "[start]", "to generate tournament results.\n");
	printf("\n%-20s%-20s", "[save]", "to save the changes.\n");
	printf("\n");
}
