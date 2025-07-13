#include <minishell.h>

void	parameter_expansion(char *str, char *expand_str, char *quote_mask)
{
	bool	quoted;
	char	quote;
	size_t	len;

	quoted = false;
	len = 0;
	while (*str)
	{
		if (is_removable_quote(*str, RESUME))
		{
			quoted = !quoted;
			quote = *str;
			set_mask_bit(quote_mask, len, 1);
		}
		if (((quoted && (quote == '"')) || !quoted) && *str == '$'
				&& first_key_ch(peakch(str)))
			set_parameter_expand_value(&str, &len, expand_str);
		else
		{
			expand_str[len] = *(str);
			len++;
			str++;
		}
	}
	is_removable_quote(0, REINITIALIZE);
}

void	set_parameter_expand_value(char **str, size_t *len, char *expand_str)
{
	int	exit_code_len;
	char	*exit_code;
	char	*key;
	char	*value;

	if (peakch(*str) == '?')
	{
		exit_code = ft_itoa(get_exit_status());
		exit_code_len = ft_strlen(exit_code);
		ft_memcpy(expand_str + *len, exit_code, exit_code_len);
		*len += exit_code_len;
		(*str) += 2;
		free(exit_code);
		return ;
	}
	(*str)++;
	key = get_key(str);
	value = expand_env(key);
	ft_memcpy(expand_str + *len, value, ft_strlen(value));
	free(key);
	*len += ft_strlen(value);
}
