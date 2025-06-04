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
//

void	expand(char *str, char *complete_string)
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
			expand_word(&str, &len, complete_string);
		else
		{
			complete_string[len] = *str;
			len++;
			str++;
		}
	}
	complete_string[len] = 0;
}

//to do: you have to handle "$"
//to do: you have to handle $?
//to do: create a function that return the key to be expanded
void	expand_word(char **str, size_t *len, char *complete_string)
{
	if (peakch(*str) == '?')
	{
		complete_string[*len] = '0';
		*len += ft_strlen("0");
		(*str) += 2;
		return ;
	}
	if (!ft_isalpha(peakch(*str)) && peakch(*str) != '_')
	{
		complete_string[*len] = (*str)[0];
		complete_string[*len + 1] = (*str)[1];
		(*str) += 2;
		*len += 2;
		return ;
	}
	(*str)++;
	char *key = get_key(str);
	if (key == NULL)
		return ;
	ft_memcpy(complete_string + *len, "hey hey", 7);
	free(key);
	*len += 7;
}
