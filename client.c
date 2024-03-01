/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:18:34 by locharve          #+#    #+#             */
/*   Updated: 2024/03/01 17:02:26 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(int pid, unsigned char c)
{
	int	pow;

	pow = 7;
	while (pow >= 0)
	{
		if (c >> pow != 0)
		{
			kill(pid, SIGUSR1);
			c -= 1 << pow;
		}
		else if (c >> pow == 0)
		{
			kill(pid, SIGUSR2);
		}
		usleep(200);
		pow--;
	}
	//usleep(100);
	return ;
}

static void	handle_sig(int sig)
{	
	if (sig == SIGUSR1)
	{
		ft_putstr_fd("--- Message received by server ---\n", 1);
	}
	return ;
}

static void	send_msg(struct sigaction sa, char *str, int pid)
{
	int	i;

	(void) sa;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		usleep(100);
		i++;
	}
	if (!str[i])
	{
		send_char(pid, str[i]);
		usleep(100);
	}
	return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	pid = ft_atoi(argv[1]); // verifs
	if (pid <= 0)
		return (0);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	if (argc == 3)
	{
		send_msg(sa, argv[2], pid);
	}
	return (0);
}
