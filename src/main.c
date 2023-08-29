/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/29 21:00:58 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sigint_received;

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	char	*line;

	(void) argc;
	(void) argv;
	ft_memset(&vars, 0, sizeof(t_vars));
	setup_signal_handlers_main();
	init_envp_list(envp, &(vars.envp_list));
	while (1)
	{
		line = readline("myshell> ");
		if (line == NULL)
		{
			rl_clear_history();
			free_vars(&vars);
			exit(EXIT_SUCCESS);
		}
		handle_history(line);
//		exec_line(line, &vars);
		free(line);
	}
	return (EXIT_SUCCESS);
}

// TESTING

//int	main(int argc, char *argv[], char *envp[])
//{
//	t_vars		vars;
//	t_heredoc	*hd;
//	t_commande	*cmd1;
//	t_commande	*cmd2;
//	t_partition	*part;
//
//	(void)argc;
//	(void)argv;
//	ft_memset(&vars, 0, sizeof(t_vars));
//	vars.envp_list = init_envp_list(envp);
//	if (!vars.envp_list)
//		return (-1);
//	// Initialize a heredoc (not used in this example, but shown for completeness)
//	hd = malloc(sizeof(t_heredoc));
//	hd->filename = ft_strdup("some_file");
//	hd->file = ft_strdup("This is the content of some_file.");
//	// Initialize first command: cat example.txt
//	cmd1 = malloc(sizeof(t_commande));
//	cmd1->cmd = ft_strdup("cat");
//	cmd1->cmds_split = malloc(3 * sizeof(char *));
//	cmd1->cmds_split[0] = ft_strdup("cat");
//	cmd1->cmds_split[1] = ft_strdup("example.txt");
//	cmd1->cmds_split[2] = NULL;
//	cmd1->id = WORD;
//	cmd1->hd = hd;
//	cmd1->next = NULL;
//	// Initialize second command: grep "hello"
//	cmd2 = malloc(sizeof(t_commande));
//	cmd2->cmd = ft_strdup("grep");
//	cmd2->cmds_split = malloc(3 * sizeof(char *));
//	cmd2->cmds_split[0] = ft_strdup("grep");
//	cmd2->cmds_split[1] = ft_strdup("hello");
//	cmd2->cmds_split[2] = NULL;
//	cmd2->id = WORD;
//	cmd2->hd = NULL; // Not using heredoc in this command
//	cmd2->next = NULL;
//	// Link commands
//	cmd1->next = cmd2;
//	// Initialize the partition
//	part = malloc(sizeof(t_partition));
//	part->cmds = cmd1;
//	part->pid = 1; // Example PID
//	part->next = NULL;
//	// Execute partition
//	exec_partition(part, &vars);
//	// Cleaning up
//	free_partition(part);
//	return (0);
//}
