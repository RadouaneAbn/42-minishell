#include <minishell.h>

/*NOTE: 
	you have two choces for now to handle malloc failure
		first:
			you can use a function that allocate using malloc 
			and this func has a static so if malloc failed that var
			will indicate that
		second:
			using a struct that contain a void pointer
			and an indicator that has a value (for example: M_FAIL for malloc fail)
		third:
			use errno var to indicate the error*/

void	expand(char *str)
{
	bool	quoted;
	char	quote;
	size_t	len;

	quoted = false;
	len = 0;
	while (*str)
	{
		if (char_in_set(*str, "'\"") && !quoted)
			quote = *str;
		if (quote == *str)
			quoted = !quoted;
		if (!quoted && *str == '$' && char_in_set(peakch(str), "'\""))
			str++;
		else if (((quoted && (quote == '"')) || !quoted) && *str == '$' && peakch(str))
			expand_word(&str, &len);
		else
		{
			printf("%c", *str);
			len++;
			str++;
		}
	}
	printf("\nlen: %lu\n", len);
}

bool	valid_key_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

//this function get a string and return first key inside
//that string witout dollar sign
//and this function allocates space for that key using malloc
//so the user should free the pointer after using it
//NOTE: just env varaibles not $?
char	*get_key(char **str)
{
	char	*key;
	size_t	len;

	len = 0;
	while (valid_key_char((*str)[len]))
		len++;
	key = ft_substr(*str, 0, len);
	if (key == NULL)
		return (NULL);
	*str += len;
	return (key);
}

//to do: you have to handle "$"
//to do: you have to handle $?
//to do: create a function that return the key to be expanded
void	expand_word(char **str, size_t *len)
{
	if (peakch(*str) == '?')
	{
		printf("["BLUE"expand: ?"RESET"]");
		*len += ft_strlen("0");
		(*str) += 2;
		return ;
	}
	if (!ft_isalpha(peakch(*str)) && peakch(*str) != '_')
	{
		printf("%c%c", **str, peakch(*str));	
		(*str) += 2;
		*len += 2;
		return ;
	}
	(*str)++;
	char *key = get_key(str);
	if (key == NULL)
		return ;
	printf("["BLUE"expand: %s", key);
	free(key);
	*len += 7;
	printf(RESET"]");
}
