/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/20 15:04:49 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

char *string;
int	bit = 0;

int	is_end(char *str)
{
	int	i;

	i = ft_strlen(str) - 8;
	while (str[i])
	{
		if (str[i++] != '0')
			return (0);
	}
	return (1);
}

char	binary_to_char(int	binary)
{
	int decimal = 0;
	int base = 1;
	char result;
	while (binary != 0)
	{
		int digit = binary % 10;
		binary /= 10;
		decimal += digit * base;
		base *= 2;
	}
	result = (char)decimal;
	return (result);
}

void	print_string(char *str)
{
	int		i;
	int		j;
	char	c;
	char	character[9];

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i % 8 == 0)
		{
			character[j] = '\0';
			c = binary_to_char(ft_atoi(character));
			write (1, &c, 1);
			j = 0;
		}
		character[j] = str[i];
		j++;
		i++;
	}
}

void	sig_handler(int signum)
{
	if (!string)
		string = ft_strdup("");
	if (signum == SIGUSR1)
	{
		string = ft_strjoin(string, "1");
		bit++;
	}
	else if (signum == SIGUSR2)
	{
		string = ft_strjoin(string, "0");
		bit++;
	}
	if (bit % 8 == 0)
	{
		if (is_end(string))
		{
			print_string(string);
			write(1, "\n\n", 1);
			if (string)
				free(string);
			string = NULL;
		}
	}
}

int	main()
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	string = NULL;
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);
}
