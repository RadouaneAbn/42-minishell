#include <minishell.h>

//bool	is__operator(int	type)
//{
	//return (type == RED_IN || type == RED_OUT
		//|| type == APPEND_OUT || type == HERE_DOC);
//}
//
////function idea: report
////function idea: throw
////function tree_append
//void	parse_simple_command(t_token_lst	*token_lst)
//{
	////t_list	*outfiles;
	////t_list	*infiles;
	////t_list	*cmd;
//
	//int	redirect_operator;
//
	//redirect_operator = -1;
	//while (token_lst)
	//{
		//if (is_operator(token_lst->token->type) && redirect_operator == -1)
			//redirect_operator = token_lst->token->type;
		//else if (token_lst->token->type == WORD && redirect_operator != -1)
		//{
			//if (redirect_operator == HERE_DOC)
				//printf("delimeter: "BLUE"%s"RESET" %s\n", token_lst->token->lexeme, get_operator(redirect_operator));
			//else
				//printf("file: "BLUE"%s"RESET" %s\n", token_lst->token->lexeme, get_operator(redirect_operator));
			//redirect_operator = -1;
		//}
		//else if (token_lst->token->type == WORD && redirect_operator == -1)
			//printf("arg: %s arg_list\n", token_lst->token->lexeme);
		//else if (token_lst->token->type != WORD && redirect_operator != -1)
		//{
			//printf ("syntax error near unexpected token '%s'\n", token_lst->token->lexeme);
			//break ;
		//}
		//else
			//break;
		//token_lst = token_lst->next;
	//}
	//if (redirect_operator != -1)
			//printf ("syntax error near unexpected token 'end of line'\n");
//}
//
