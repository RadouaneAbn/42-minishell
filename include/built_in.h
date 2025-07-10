/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:31:45 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:43:21 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <minishell.h>

typedef struct s_info
{
	t_map	exports;
	char	**path;
	int		last_exit_status;
	int		env_size;
}			t_info;

typedef enum e_cmd_type
{
	RUN_EXPORT,
	RUN_ENV,
	RUN_UNSET,
	RUN_ECHO,
	RUN_PWD,
	RUN_CD,
	RUN_EXIT,
	RUN_EXECUTABLE,
	TYPE_COUNT
}			t_cmd_type;

/* echo flag */
# define NO_FLAG 0
# define NO_NL 1
/* cd */
# define CUR 0
# define PAR 1

t_map		*get_map(void);
char		**split_export_args(char *arg);

int			echo(char **vec, int fd);
int			export(char *key, char *value);
int			unset(char *key);
char		*expand_env(char *key);
int			pre_export(char *exported);

/* Helpers */
int			command_is_empty(char *cmd);
char		*get_path_from_env(void);
char		*join_path(char *path, char *cmd);
bool		file_exist(char *path);
char		*find_file(char *cmd);
char		*node_to_string(t_node *node);
char		**build_env(void);
bool		has_exec_perm(char *path);

int			print_env(int fd);
int			print_exports(int fd);

int			run_export(t_executable_data *data);
int			run_env(t_executable_data *data);
int			run_unset(t_executable_data *data);
int			run_echo(t_executable_data *data);
int			run_pwd(t_executable_data *data);
int			run_cd(t_executable_data *data);
int			run_exit(t_executable_data *data);

long		convert_exist_status(char *arg);

t_cmd_type	get_command_type(char *cmd);

#endif