#include "../includes/mk8d_trueskill.h"


void	prompt(t_data *data)
{
	printf("\033[2J\033[H");
	while (1)
	{
		char *prompt = "\033[1;31mM\033[0m\033[1;34mK\033[0m\033[1;33m8\033[0m\033[1;37mD\033[0m_\033[1;34mTrueSkill_Generator\033[0m 🏁 > ";

		data->input = readline(prompt);
		if (data->input == NULL)
			return ;
		if (line_is_empty(data->input))
		{
			free(data->input);
			data->input = NULL;
			continue ;
		}
		add_history(data->input);
		if (!parsing(data))
			continue ;
		exec(data);
		free_tmp_var(data);
	}
}

int	main()
{
	t_data		data;

	set_data(&data);
	signals();
	data.stats = read_stats(&data);
	init_player_struct(&data);
	prompt(&data);
	printf("exit..\n");
	end(&data, 0);
}
