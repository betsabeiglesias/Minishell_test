/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:56:42 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/08 10:19:48 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	char *line;

	line = prompt( );
	free(line);
	    	
	return(0);
}