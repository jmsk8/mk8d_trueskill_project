#include "../includes/mk8d_trueskill.h"


void	prompt(t_data *data)
{
	while (1)
	{
		data->input = readline("mk8d_TrueSkill_Generator > ");
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
