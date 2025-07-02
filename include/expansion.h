#ifndef EXPANSION_H
#define EXPANSION_H
#define REINITIALIZE true
#define RESUME false
bool	valid_key_char(char c);
void	expand_word(char **str, size_t *index, char *complete_string);
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




/* field splitting functions */
bool	field_char_quoted(char *quote_mask, int size);
int	get_fields_len(char **expand_strs, char **quote_mask);
unsigned char get_bit(char *quote_mask, size_t size);
void	cp_field(char *field, char *expand_str, char *quote_mask, size_t start, size_t end);
size_t	get_field_len(char *expand_str, char *quote_mask);
void	set_field(char **field, char *expand_str, char *quote_mask, size_t start, size_t end);
void	fill_fields(char **expand_strs, char **fields, char **quote_mask);
void	filed_splitting(char **expand_strs, char **quote_mask);




void	tree_expand_simple_command(t_tree *simple_command);

void	expand(char *str, char *complete_string, char *quote_array);
#endif
