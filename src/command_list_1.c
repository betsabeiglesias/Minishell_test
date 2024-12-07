/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/07 18:52:34 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_execution_list(t_list *tk_lst, t_mini *shell)
{
	t_list	*exe_lst;
	t_exec	*node;
	int		is_redir;

	exe_lst = NULL;
	node = NULL;
	while(tk_lst != NULL)
	{
		is_redir = 0;
		if (!node)
			node = init_cmd_node();
		handle_all_redir(tk_lst, &is_redir, node);
		if (create_outfile(node, (char *)(tk_lst->content)))
			return (NULL);
		if (is_redir == 0 && is_str_pipe((char *)(tk_lst->content)))
		{
			ft_free_v(tk_lst->content);
			if (!is_builtin(node->cmd_all))
			{
				if (!is_cmd_executable(node->cmd_all))
				{
					if (node->cmd_all != NULL)
						node->path = get_path(shell->all_paths, node->cmd_all[0]);
					//if (!node->path)
					//	return (free_node_exec(node), NULL);
				}
				else
					node->path = ft_strdup(node->cmd_all[0]);
			}
			if (save_exe_node(&exe_lst, node))
				return (NULL);
			node = NULL;
		}
		else if (is_redir == 0)
			if (handle_commands(tk_lst, node))
				return(NULL);
		if (is_redir)
		{
			ft_free_v(tk_lst->content);
			tk_lst = tk_lst->next;
		}
		tk_lst = tk_lst->next;
	}
	if (handle_last_save_node(&exe_lst, &node, shell))
		return (NULL);
	return (exe_lst);
}

/*
int handle_save_node(t_exec *node, t_mini *shell, t_list **exe_lst)
{
	if (!is_builtin(node->cmd_all[0]))
	{
		node->path = get_path(shell->all_paths, node->cmd_all[0]);
		if (!node->path)
			return (EXIT_FAILURE);
	}
	if (save_exe_node(exe_lst, node))
		return (EXIT_FAILURE);
	node = NULL;
	return (EXIT_SUCCESS);
}
*/

void handle_all_redir(t_list *tk_lst, int *is_redir, t_exec *node)
{
	if (is_str_redir((char *)(tk_lst->content), REDIR_IN_S))
		*is_redir = handle_redir(tk_lst, node, REDIR_IN_S);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_IN_D))
		*is_redir = handle_redir(tk_lst, node, REDIR_IN_D);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_S))
		*is_redir = handle_redir(tk_lst, node, REDIR_OUT_S);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_D))
		*is_redir = handle_redir(tk_lst, node, REDIR_OUT_D);
	return ;
}

int	handle_redir(t_list *tk_lst, t_exec *node, char *redir)
{
	char	*delimiter;
	
	if (!ft_strncmp(redir, REDIR_IN_S, ft_strlen(redir)))
		node->filename_in = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_IN_D, ft_strlen(redir)))
	{
		delimiter = (char *)tk_lst->next->content;
		delimiter = ft_strjoin_freed(delimiter, NEW_LINE);
		node->filename_in = ft_strdup(HERE_DOC);
		read_stdin(node, delimiter);
		//ft_free(delimiter);
	}
	else if (!ft_strncmp(redir, REDIR_OUT_S, ft_strlen(redir)))
		node->filename_out = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_OUT_D, ft_strlen(redir)))
	{
		node->filename_out = (char *)tk_lst->next->content;
		node->out_append = 1;
	}
	return (1);
}

int create_outfile(t_exec *node, char *redir)
{
	int fd;
	
	if (!ft_strncmp(redir, REDIR_OUT_S, ft_strlen(redir)) || !ft_strncmp(redir, REDIR_OUT_D, ft_strlen(redir)))
	{
		fd = open(node->filename_out, O_CREAT, 0644);
		if (fd == ERROR)
			return (handle_error(ERR_OPEN), EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	read_stdin(t_exec *node, char *delimiter)
{
	char	*buffer;
	//int		fd;

	node->heredoc_content = ft_strdup(EMPTY);
	buffer = ft_strdup(EMPTY);
	if (!buffer || !node->heredoc_content)
		return (ft_free(buffer), ft_free(delimiter), handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (buffer)
	{
		if (buffer)
			ft_free(buffer);
		buffer = get_next_line(STDIN_FILENO);
		if (is_identical_str(buffer, delimiter))
		{
			ft_free(delimiter);
			ft_free(buffer);
			break ;
		}
		if (buffer)
			node->heredoc_content = ft_strjoin_freed(node->heredoc_content, buffer);
	}
	// fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (fd == ERROR)
	// 	return (handle_error(ERR_OPEN), EXIT_FAILURE);
	// ft_putstr_fd(node->heredoc_content, fd);
	// close (fd);
	return (EXIT_SUCCESS);
}

int is_cmd_executable(char **cmd_all)
{
	if (cmd_all == NULL)
		return (0);
	if (ft_strlen(*cmd_all) < 3)
		return (0);
	if ((*cmd_all)[0] == POINT && (*cmd_all)[1] == SLASH_CHAR)
		return (1);
	return (0);
}
