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

void	set_byte(char *quote_array, int size, char bit)
{
	int	byte_index;

	byte_index = size / 8;
	quote_array[byte_index] = (quote_array[byte_index] << 1) | bit;
	printf("%d\n", bit);
}

void	expand(char *str, char *complete_string, char *quote_array)
{
	bool	quoted;
	char	quote;
	size_t	len;
	size_t	start;

	quoted = false;
	len = 0;
	start = 0;
	while (*str)
	{
		if (char_in_set(*str, "'\""))
		{
			if (!quoted)
				quote = *str;
			if (quote == *str)
			{
				set_byte(quote_array, start, 1);
				start = len;
				start++;
				quoted = !quoted;
			}
		}
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
		while (start < len)
		{
			set_byte(quote_array, start, 0);
			start++;
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
	ft_memcpy(complete_string + *len, "ha za", 5);
	free(key);
	*len += 5;
}
