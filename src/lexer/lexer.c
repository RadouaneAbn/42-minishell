#include <minishell.h>

void	token_free_list(t_token_lst *token_lst);

void	lexer(char *line)
{
	t_token	token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;

	token_lst = NULL;
	while (true)
	{
		token.lexeme = NULL;
		get_next_token(&token, line);
		if (token.lexeme == NULL)
			break ;
		new_node = token_lstnew(token);
		token_lstadd_back(&token_lst, new_node);
	}
	//token_printlst(token_lst);
	t_tree *tree = parser(token_lst);
	// print_tree(tree, 0);
	execute_tree(tree);
	//tree_expand_simple_command(tree->next->next->next);
	token_free_list(token_lst);
}

// t_tree *create_fake_tree(void)
// {
// 	t_tree *compound;
// 	t_tree *and_node;
// 	t_tree *pipeline;
// 	t_tree *pipeline2;
// 	t_tree *cmd1;
// 	t_tree *cmd1_arg;
// 	t_tree *cmd1_redir;
// 	t_tree *cmd2;
// 	t_tree *cmd2_arg1;
// 	t_tree *cmd2_arg2;
// 	t_tree *exit_cmd;
// 	t_tree *exit_arg;

// 	exit_arg = gc_malloc(sizeof(t_tree));
// 	exit_arg->data_type = T_CMD_ARG;
// 	exit_arg->data = copy_string("exit");
// 	exit_arg->sibling = NULL;
// 	exit_arg->next = NULL;

// 	// T_COMPOUND_COMMAND
// 	compound = gc_malloc(sizeof(t_tree));
// 	compound->data_type = T_COMPOUND_COMMAND;
// 	compound->data = NULL;
// 	compound->sibling = NULL;

// 	// T_PIPELINE
// 	pipeline = gc_malloc(sizeof(t_tree));
// 	pipeline->data_type = T_PIPELINE;
// 	pipeline->data = NULL;
// 	pipeline->sibling = NULL;

// 	// T_AND
// 	and_node = gc_malloc(sizeof(t_tree));
// 	and_node->data_type = T_AND;
// 	and_node->data = NULL;
// 	and_node->sibling = NULL;
// 	and_node->next = NULL;

// 	// T_PIPELINE 2
// 	pipeline2 = gc_malloc(sizeof(t_tree));
// 	pipeline2->data_type = T_PIPELINE;
// 	pipeline2->data = NULL;
// 	pipeline2->sibling = NULL;

// 	// T_COMMAND exit
// 	exit_cmd = gc_malloc(sizeof(t_tree));
// 	exit_cmd->data_type = T_COMMAND;
// 	exit_cmd->data = NULL;
// 	exit_cmd->sibling = NULL;
// 	exit_cmd->next = NULL;

// 	// First command: < Makefile cat
// 	cmd1 = gc_malloc(sizeof(t_tree));
// 	cmd1->data_type = T_COMMAND;
// 	cmd1->data = NULL;
// 	cmd1->sibling = NULL;

// 	// Second command: grep SOURCE
// 	cmd2 = gc_malloc(sizeof(t_tree));
// 	cmd2->data_type = T_COMMAND;
// 	cmd2->data = NULL;
// 	cmd2->sibling = NULL;

// 	// T_CMD_ARG cat
// 	cmd1_arg = gc_malloc(sizeof(t_tree));
// 	cmd1_arg->data_type = T_CMD_ARG;
// 	cmd1_arg->data = copy_string("cat");
// 	cmd1_arg->sibling = NULL;
// 	cmd1_arg->next = NULL;

// 	// T_FILE_READ Makefile
// 	cmd1_redir = gc_malloc(sizeof(t_tree));
// 	cmd1_redir->data_type = T_FILE_READ;
// 	cmd1_redir->data = copy_string("Makefile");
// 	cmd1_redir->sibling = NULL;
// 	cmd1_redir->next = NULL;

// 	// T_CMD_ARG grep
// 	cmd2_arg1 = gc_malloc(sizeof(t_tree));
// 	cmd2_arg1->data_type = T_CMD_ARG;
// 	cmd2_arg1->data = copy_string("grep");
// 	cmd2_arg1->sibling = NULL;

// 	// T_CMD_ARG SOURCE
// 	cmd2_arg2 = gc_malloc(sizeof(t_tree));
// 	cmd2_arg2->data_type = T_CMD_ARG;
// 	cmd2_arg2->data = copy_string("SOURCE");
// 	cmd2_arg2->sibling = NULL;
// 	cmd2_arg2->next = NULL;

// 	compound->next = pipeline;
// 	pipeline->next = cmd1;
// 	cmd1->next = cmd1_arg;
// 	cmd1_arg->sibling = cmd1_redir;

// 	cmd1->sibling = cmd2;
// 	cmd2->next = cmd2_arg1;
// 	cmd2_arg1->next = cmd2_arg2;

// 	pipeline->sibling = and_node;
// 	and_node->sibling = pipeline2;

// 	pipeline2->next = exit_cmd;
// 	exit_cmd->next = exit_arg;

// 	return (compound);
// }

// void	lexer(char *line)
// {
// 	t_tree *tree;

// 	(void) line;
// 	gc_level_init();

// 	// tree = create_fake_tree();
// 	print_tree(tree, 0);
// 	execute_tree(tree);
// 	//tree_expand_simple_command(tree->next->next->next);
// 	// token_free_list(token_lst);
// 	free_level();
// }

void	token_printlst(t_token_lst *token_lst)
{
	while (token_lst)
	{
		print_token(token_lst->token);
		token_lst = token_lst->next;
	}
}

void	token_free_list(t_token_lst *token_lst)
{
	t_token_lst	*tmp;

	while (token_lst)
	{
		tmp = token_lst->next;
		free(token_lst->token.lexeme);
		free(token_lst);
		token_lst = tmp;
	}
}
