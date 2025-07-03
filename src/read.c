#include "../includes/mk8d_trueskill.h"

char	*get_stats_array(int fd, int *is_error)
{
	char	*res;
	char	*str;

	str = NULL;
	res = NULL;
	while (1)
	{
		res = get_next_line(fd, is_error);
		if (!res && !*is_error)
			break ;
		if (*is_error)
		{
			free(str);
			ft_error("Memory error\n", NULL, 1);
		}
		str = ft_strjoin(str, res);
		free(res);
		if (!str)
			ft_error("Memory error\n", NULL, 1);
	}
	return (str);
}

char	**read_stats(t_data *data)
{
	int		fd;
	int		is_error;
	char	**file;

	file = NULL;
	is_error = 0;

	fd = open("data/data.log", O_RDONLY);
	if (fd > 0 && BUFFER_SIZE > 0)
	{
		file = ft_split(get_stats_array(fd, &is_error), '\n');
		// for (int i = 0; file[i]; i++)
		// 	printf("%s\n", file[i]);
		// exit(1);
		close(fd);
		if (!file)
			ft_error("Memory error\n", data, 1);
	}
	else
		ft_error("Error\nFailed to open file\n", data, 1);
	return (file);
}
