#include "../includes/mk8d_trueskill.h"

int	cmd_size(char *input)
{
	int size = 0;

	while (*input && isspace(*input))
		input++;
	while (*input)
	{
		while (*input && !isspace(*input))
			input++;
		size++;
		while (*input && isspace(*input))
			input++;
	}
	printf("size %d\n", size);
	return (size);
}

char	*get_cmd(char **input)
{
	int len = 0;
	char *res;

	while (*(*input + len) && !isspace(*(*input + len)))
		len++;
	res = ft_strndup(*input, len);
	if (!res)
		return NULL;
	*input += len;
	while (**input && isspace(**input))
		(*input)++;

	return res;
}


int fill_cmd(t_data *data)
{
	char *cmd = data->input;
	int i = 0;

	while (*cmd)
	{
		while (*cmd && isspace(*cmd))
			cmd++;

		if (*cmd)
		{
			data->cmd[i] = get_cmd(&cmd);
			if (!data->cmd[i])
				return 0;
			i++;
		}
	}
	data->cmd[i] = NULL;
	return (1);
}

int	init_cmd_memory(t_data *data, int len)
{
	data->cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!data->cmd)
		return (0);
	for (int i = 0; i < len; i++)
		data->cmd[i] = NULL;
	return (1);
}

int	parsing(t_data *data)
{
	int	cmd_len;

	cmd_len = cmd_size(data->input);
	
	if (!init_cmd_memory(data, cmd_len))
		ft_error("malloc error\n", data, 1);
	if (!fill_cmd(data))
		ft_error("malloc error\n", data, 1);
	for (int i = 0; data->cmd[i]; i++)
		printf("cmd [%s] \n", data->cmd[i]);
	return (1);
}
