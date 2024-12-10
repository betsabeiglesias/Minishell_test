/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:18:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/10 09:28:01 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// COMPROBAR EN EL PROMPT COMO SE IMPRIME EL SALTO DE LÍNEA 

#include "../inc/minishell.h"

int	builtin_pwd(int fd)
{
	char	*currentwd;

	currentwd = getcwd(NULL, 0);
	if (currentwd == NULL)
	{
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(currentwd, fd);
		ft_putchar_fd('\n', fd);
		free(currentwd);
	}
	return (EXIT_SUCCESS);
}

int handle_exec_built(t_exec *node, t_mini *shell)
{
	t_fd	*fd;
	int		len;
	
	len = ft_strlen(node->cmd_all[0]);
	fd = do_redir_built(node);
	if (!fd)
		return(shell->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	else if (!ft_strncmp(node->cmd_all[0], ENV, len))
		shell->exit_status = builtin_env(shell, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], CD, len))
		shell->exit_status = builtin_cd(node, shell);
	else if (!ft_strncmp(node->cmd_all[0], PWD, len))
		shell->exit_status = builtin_pwd(fd->out);
	else if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
		shell->exit_status = builtin_export(node, shell, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], UNSET, len))
		shell->exit_status = builtin_unset(node, shell);
	else if (!ft_strncmp(node->cmd_all[0], "echo", len))
		shell->exit_status = builtin_echo(node, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], EXIT, len))
		shell->exit_status = builtin_exit(node, shell);
	return(shell->exit_status);
}

int	execute_builtin(t_exec *node, t_mini *shell)
{
	int	len;


	len = ft_strlen(node->cmd_all[0]);
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
	{
		printf("ENTRA EN ENV\n\n");
		builtin_env(shell, STDOUT_FILENO);
	}
	else if (!ft_strncmp(node->cmd_all[0], EXIT, len))
	{
		printf("ENTRA EN EXIT\n\n");
		builtin_exit(node, shell);
	}
	else if (!ft_strncmp(node->cmd_all[0], "echo", len))
	{
		builtin_echo(node, STDOUT_FILENO);
	}
	else if (!ft_strncmp(node->cmd_all[0], PWD, len))
	{
		builtin_pwd(STDOUT_FILENO);
	}
	else if (!ft_strncmp(node->cmd_all[0], CD, len))
	{
		builtin_cd(node, shell);
	}
	else if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
	{
		builtin_export(node, shell, STDOUT_FILENO);
	}
	else if (!ft_strncmp(node->cmd_all[0], UNSET, len))
	{
		builtin_unset(node, shell);
	}
	return(EXIT_SUCCESS);
}
t_fd *do_redir_built(t_exec *node)
{
	t_fd *fd;
	
	fd = malloc(sizeof(t_fd));
	if(!fd)
		return(handle_error(ERR_MALLOC), NULL);
	fd->in = 0;
	fd->out = 1;
	// printf("FD IN REDIR %i\n", fd->in);
	// printf("FD OUT REDIR %i\n", fd->out);
	if (node->filename_in != NULL)
    {
        fd->in = open(node->filename_in, O_RDONLY);
		// printf("FD2 IN REDIR %i\n", fd->in);
        if (fd->in == ERROR)
		    return (handle_error(ERR_OPEN), NULL);
    }
    if (node->filename_out != NULL && node->out_append == 0)
	{
		// printf("fileout %s\n", node->filename_out);	
        fd->out =  open(node->filename_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		// printf("FD2 OUT REDIR %i, dir %p\n", fd->out, &fd->out);
	}
    else if (node->filename_out != NULL && node->out_append == 1)
        fd->out = open(node->filename_out, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd->out == ERROR)
		return (handle_error(ERR_OPEN), NULL);
	return (fd);
}
