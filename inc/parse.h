/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:06 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/26 19:49:46 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum	e_error
{
    ERR_OTHER
}				t_error;

typedef struct  s_quote
{
    bool sing;
    bool doub;
}               t_quote;

typedef struct s_cl_data
{
    char	*dst;
	char	*tmp;
    int		i;
	int		old_len;
}              t_cl_data;


# define ERR_QUOTE      0
# define ERR_EXTREM     1
# define ERR_ALONE      2
# define ERR_ENVP       3

# define ERR_MSG_QUOTE   "SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM   "SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE   "SYNTAX ERROR: need separate metacharacter"

# define ERR_MSG_ENVP   "ENVIRONMENT VARIABLE NOT FOUND OR UNDEFINED"

# define SINGLE_QUOTE   '\''
# define DOUBLE_QUOTE   '"'
# define SPACE          ' '

// CHECK SYNTAX 1
int syntax_check(char*str);
int	check_quotes(char *str);
int	check_extrems(char *str);

// CHECK UTILS
int	is_space(char c);
int	is_valid_metachar(char c);
int	is_str_space(char *str);

// HANDLE ERROR
int handle_error(int error_type);

//SYNTAX CHECK 2
int	check_metachar_separate(char *str);
int do_check(char *str, int i);
int	check_pipe_separate(char *str, int i);
int	check_redir_separate(char *str, int i, char c);
int	do_redir_check(char *str,int i, char c);

//CLEAN_CMDLINE_1
char    *clean_cmdline(char *str);
void	init_cl_data(t_cl_data *data);
void	handle_quote(t_cl_data *data, char *str, char quote);
void	handle_space(t_cl_data *data, char *str);

//CLEAN_CMDLINE_2
char    *add_literal_str(char *dst, char *str, char quote);
void	handle_final_tmp(t_cl_data *data);
char	*ft_add_char_freed(char *str, char const c);


#endif