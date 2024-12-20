/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:46 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/18 13:07:57 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

// LIBRERIAS STANDARD
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stddef.h>
# include <limits.h>
# include <termios.h>
# include <stdarg.h>

//LIBRERIAS PROPIAS
# include "../lib/libft/src/libft.h"
# include "../lib/liblst/src/liblst.h"

//HEADERS
# include "variables.h"
# include "macros.h"
# include "functions.h"

#endif