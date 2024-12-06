/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_aux_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:24:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/06 12:33:46 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	only_exit()
{
	ft_putstr_fd(EXIT, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	ft_atoi_exit(char *str)
{
	int	nb;
	
	nb = ft_atoi(str);
	nb = nb % 256;
	return(nb);
}

int	ft_str_hasalpha(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}