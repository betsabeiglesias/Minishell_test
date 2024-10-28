/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:31 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/28 11:19:20 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"


char	*do_expansion(char *cmd_line, t_mini *mini)
{
	t_varenv	*var;
	char		*new_line;
	int			i;
	

	i = 0;
	new_line = NULL;
	var = malloc(sizeof(t_varenv));
	if (var == NULL)
		return (NULL);
	if (!has_dollar(cmd_line, var, &i))
	{
		return(cmd_line) ;
	}
	trim_to_expand(cmd_line, var, &i);
	new_line = expanded_cmd_line(var, mini);
	new_line = do_expansion(new_line, mini);
	return (new_line);
}

int main(int argc, char **argv, char **envp)
{
	t_mini *mini;
	mini = malloc(sizeof(t_mini));
    if (mini == NULL) {
        printf("Error al asignar memoria\n");
        return (1);
	}
	t_varenv *var = malloc(sizeof(t_varenv));
   	if (var == NULL) {
   	   printf("Error al asignar memoria\n");
        return (1);
    }
	// int	i;

	// i = 0;	
	mini->env = get_my_env(envp, mini);
	if (mini->env == NULL) 
	{
		printf("Error al inicializar el entorno\n");
		free_mini(mini);
    	return (1);
	}
	if (argc < 2)
	{
		printf("not enough arguments\n");
		free(mini);
		return (1);
	}
	else
	{
		printf("%s\n", do_expansion(argv[1], mini));
	}
	// free_env(mini);
	//free(mini);
	//free(var);
	return(0);
}