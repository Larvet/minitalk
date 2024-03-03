/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:57:38 by locharve          #+#    #+#             */
/*   Updated: 2024/03/03 15:57:44 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("--- Message received by server ---\n", 1);
	return ;
}

static void	send_byte(int pid, unsigned char c)
{
	int	pow;

	pow = 7;
	while (pow >= 0)
	{
		usleep(200);
		if (c >> pow != 0)
		{
			kill(pid, SIGUSR1);
			c -= 1 << pow;
		}
		else if (c >> pow == 0)
			kill(pid, SIGUSR2);
		pause();
		pow--;
	}
	return ;
}

static void	send_msg(char *str, int pid)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			send_byte(pid, str[i]);
			i++;
		}
		send_byte(pid, str[i]);
	}
	else
		ft_putstr_fd("Cannot read NULL pointer.\n", 2);
	return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			return (1);
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &handle_sig;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		send_msg(argv[2], pid);
	}
	return (0);
}
