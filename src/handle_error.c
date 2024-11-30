/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:26 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/30 16:31:21 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_error(int error_type)
{
	if (error_type == ERR_QUOTE)
		ft_putendl_fd(ERR_MSG_QUOTE, STDOUT_FILENO);
	if (error_type == ERR_EXTREM)
		ft_putendl_fd(ERR_MSG_EXTREM, STDOUT_FILENO);
	if (error_type == ERR_ALONE)
		ft_putendl_fd(ERR_MSG_ALONE, STDOUT_FILENO);
	if (error_type == ERR_CONSECUTIVE)
		ft_putendl_fd(ERR_MSG_CONSECUTIVE, STDOUT_FILENO);
	if (error_type == ERR_ENVP)
		ft_putendl_fd(ERR_MSG_ENVP, STDOUT_FILENO);
	if (error_type == ERR_ATTR)
		ft_putendl_fd(ERR_MSG_ATTR, STDOUT_FILENO);
	if (error_type == ERR_MALLOC)
		ft_putendl_fd(ERR_MSG_MALLOC, STDOUT_FILENO);
	if (error_type == ERR_ACCESS)
		ft_putendl_fd(ERR_MSG_ACCESS, STDOUT_FILENO);
	if (error_type == ERR_OPEN)
		ft_putendl_fd(ERR_MSG_OPEN, STDOUT_FILENO);
	return (EXIT_FAILURE);
}