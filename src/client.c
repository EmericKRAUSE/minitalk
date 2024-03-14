/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:27 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/14 11:31:38 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int	ft_count(char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = (int)c;
	while (nb != 0)
	{
		nb /= 2;
		i++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_to_binary(char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	int		nb;

	len = (8 * ft_strlen(str));
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (j < len)
		result[j++] = '0';
	result[j] = '\0';
	j = 0;
	while (str[j])
	{
		i = 7 + (j * 8);
		nb = (int)str[j];
		while (nb != 0)
		{
			result[i--] = (nb % 2) + 48;
			nb /= 2;
		}
		j++;
	}
	return(result);
}

void	send_signal(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			kill(pid, SIGUSR1);
		else if (str[i] == '0')
			kill(pid, SIGUSR2);
		usleep(1000);
		i++;
	}
}

int main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;
	if (argc != 3)
		return (1);
	pid = atoi(argv[1]);
	str = str_to_binary(argv[2]);
	send_signal(str, pid);
	free(str);
	return (0);
}