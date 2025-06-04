//#include <minishell.h>
//
////this function get a string and return first key inside
////that string witout dollar sign
////and this function allocates space for that key using malloc
////so the user should free the pointer after using it
////NOTE: just env varaibles not $?
//char	*get_key(char **str)
//{
	//char	*key;
	//size_t	len;
//
	//len = 0;
	//while (valid_key_char((*str)[len]))
		//len++;
	//key = ft_substr(*str, 0, len);
	//if (key == NULL)
		//return (NULL);
	//*str += len;
	//return (key);
//}
//
//bool	valid_key_char(char c)
//{
	//return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
//}
