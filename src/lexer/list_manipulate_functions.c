#include <minishell.h>

t_token_lst	*token_lstnew(t_token *token)
{
	t_token_lst	*new_node;

	new_node = malloc(sizeof(t_token_lst));
	if (new_node == NULL)
		return (NULL);
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

t_token_lst	*token_lstlast(t_token_lst *lst)
{
	t_token_lst	*last_node;

	if (lst == NULL)
		return (NULL);
	last_node = lst;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

void	token_lstadd_back(t_token_lst	**lst, t_token_lst *new)
{
	t_token_lst	*last_node;

	last_node = token_lstlast(*lst);
	if (last_node == NULL)
	{
		*lst = new;
		return ;
	}
	last_node->next = new;
}	
