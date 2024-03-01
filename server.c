/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:12:49 by locharve          #+#    #+#             */
/*   Updated: 2024/03/01 17:16:47 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_buff
{
	unsigned char	buff[1000];
	struct s_byte	*nxt;
}	t_buff;

static void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	byte = 0;
	static int				pow = 7;
	int						pid;
	
	(void) ucontext;

	pid = info->si_pid;
	if (sig == SIGUSR1)
		byte += 1 << pow;
	else
		byte += 0 << pow;
	pow--;
	if (pow < 0)
	{
		ft_putchar_fd(byte, 1);
		if (!byte)
		{
			kill(pid, SIGUSR1); // end string
			ft_putchar_fd('\n', 1);
		}

		byte = 0;
		pow = 7;
		//kill(pid, SIGUSR2); // end char
		//usleep(100);
	}
	//usleep(100);
	return ;
}

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;
	int					pid;

	ft_memset(&sa1, 0, sizeof(sa1));
	sa1.sa_sigaction = &handle_sigusr;
	sa1.sa_flags = SA_SIGINFO;

	ft_memset(&sa2, 0, sizeof(sa2));
	sa2.sa_sigaction = &handle_sigusr;
	sa2.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);

	pid = getpid();
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);

	while (1)
		pause();

	return (0);
}
