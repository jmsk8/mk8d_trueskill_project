#include "../includes/mk8d_trueskill.h"

t_player	*ft_player_lstlast(t_player *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_player	*ft_player_lstnew(void)
{
	t_player	*t_newnode;

	t_newnode = malloc(sizeof(t_player));
	if (!t_newnode)
		return (NULL);
	t_newnode->mu = 0;
	t_newnode->sigma = 0;
	t_newnode->name = NULL;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	return (t_newnode);
}

t_player	*ft_player_lstnew_stats(char *name, float mu, float sigma)
{
	t_player	*t_newnode;

	t_newnode = malloc(sizeof(t_player));
	if (!t_newnode)
		return (NULL);
	t_newnode->mu = mu;
	t_newnode->sigma = sigma;
	t_newnode->name = name;
	t_newnode->pos = 0;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	return (t_newnode);
}

int	ft_player_lstadd_back(t_player **lst, t_player *new)
{
	t_player	*tmp;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		tmp = ft_player_lstlast(*(lst));
		tmp->next = new;
		new->prev = tmp;
	}
	new->next = NULL;
	return (1);
}


void	ft_player_lstclear(t_player **lst)
{
	t_player	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->name)
			free((*lst)->name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_player *insert_sorted(t_player *head, t_player *new_player)
{
	double new_points = new_player->mu - (3 * new_player->sigma);
	if (!head || (new_points > (head->mu - (3 * head->sigma))))
	{
		new_player->next = head;
		return new_player;
	}
	t_player *current = head;
	while (current->next && (new_points <= (current->next->mu - (3 * current->next->sigma))))
		current = current->next;
	new_player->next = current->next;
	current->next = new_player;
	return head;
}

t_player	*sort_players(t_player *player)
{
	t_player *sorted = NULL;
	while (player)
	{
		t_player *next = player->next;
		player->next = NULL;
		sorted = insert_sorted(sorted, player);
		player = next;
	}
	return sorted;
}
