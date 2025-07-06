//star mask functions
char *get_star_mask (char *field, char *quote_mask, size_t start, size_t	len);
void	set_star_mask(char *field, t_list **star_mask, char *quote_mask, size_t start_tmp, size_t	len);

// field splitting functions
void	cp_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end, t_list **star_mask);
void	set_field(char **field, char *expand_str, char *quote_mask, size_t start, size_t end, t_list **star_mask);

struct s_all
{
	char **fields;
	char **quote_mask;
}
