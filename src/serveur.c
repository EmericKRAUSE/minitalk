/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/18 11:42:36 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

char *character;
char *string;
int	bit = 0;

int	is_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

char	*binary_to_char(int	binary)
{
	int decimal = 0;
	int base = 1;
	char *result = malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	while (binary != 0)
	{
		int digit = binary % 10;
		binary /= 10;
		decimal += digit * base;
		base *= 2;
	}
	result[0] = (char)decimal;
    result[1] = '\0';
	return (result);
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		character = ft_strjoin(character, "1");
		bit++;
	}
	else if (signum == SIGUSR2)
	{
		character = ft_strjoin(character, "0");
		bit++;
	}
	if (bit % 8 == 0)
	{
		if (is_end(character))
			write(1, "t", 1);
		else
		{
			char *test = binary_to_char(ft_atoi(character));
			string = ft_strjoin(string, test);
			printf("%s\n", string);
			free(test);
			character = ft_strdup("");
		}
			
	}
}

int	main()
{
	pid_t	pid;

	pid = getpid();
	printf ("%d\n", pid);
	string = ft_strdup("");
	character = ft_strdup("");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		sleep(1);
	return (0);
}
