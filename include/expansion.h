#ifndef EXPANSION_H
#define EXPANSION_H
#define REINITIALIZE true
#define RESUME false

typedef struct s_expand_info
{
	bool	should_expand;
	char	*unquoted_delimiter;
} t_expand_info;



typedef	struct s_range
{
	size_t	start;
	//size_t	end;
	size_t	len;
}	t_range;	


typedef struct s_fields_info
{
	char **fields;
	t_list *star_mask;
}	t_fields_info;

bool	valid_key_char(char c);
void	set_parameter_expand_value(char **str, size_t *index, char *complete_string);
void	expand_len(char *str);
char	*get_key(char **str);
bool	valid_key_char(char c);
size_t expand_word_len(char **str);
size_t expand_str_len(char *str);
void	print_bits(char *quote_array, int size);
int	get_byte_len(int len);
void	add_bits(char *quote_array, int size);
char	*get_value(char *key);
bool	first_key_ch(char c);
bool	key_ch(char c);

void	shift_bits(char *quote_array, int size);
void	set_mask_bit(char *quote_array, int size, char bit);

bool	quoted_char(char *quote_mask, size_t size);





/* field splitting functions */
bool	field_char_quoted(char *quote_mask, int size);
size_t get_fields_len(char *expand_strs, char *quote_mask);
unsigned char get_bit(char *quote_mask, size_t size);
void	cp_field(char *field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask);
size_t	get_field_len(char *expand_str, char *quote_mask, size_t *start);
void	set_field(char **field, char *expand_str, char *quote_mask, t_range range, t_list **star_mask);
void	fill_fields(char *expand_strs, char **fields, char *quote_mask, t_list **star_mask);
char **field_splitting(char **expand_strs, char **quote_mask, t_list **star_mask);




t_tree	*tree_expand_simple_command(t_tree *simple_command);
void	parameter_expansion(char *str, char *complete_string, char *quote_array);


/* HERE DOC FUNCTIONS */
void	write_expand_var(char **line, int fd);
void	write_expand_line(int fd, char *line);
size_t	get_unquoted_del_size(char *delimiter);
t_expand_info	heredoc_expand_info(char *delimiter);
char	*heredoc(char *delimiter);


#endif
