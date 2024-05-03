/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:03:18 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/03 11:56:49 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

char    *ft_set_exec(char *cmd)
{
        char    **path;
        char    *abs_path;
        char    *tmp;
        int             i;

        i = 0;
        path = ft_split(getenv("PATH"), ':');
        abs_path = ft_strdup(cmd);
        while (path[i] != NULL)
        {
                if (access(abs_path, X_OK) == 0)
                        return (abs_path);
                free(abs_path);
                tmp = ft_strjoin(path[i], "/");
                abs_path = ft_strjoin(tmp, cmd);
                free(tmp);
                i++;
        }
        free(abs_path);
        return (cmd);
}

int     ft_exec_cmd(char **argv, char **envp)
{
        pid_t   pid;
        int             wstatus;

        pid = fork();
        if (pid < 0)
                return (-1);
        else if (pid == 0)
        {
                argv[0] = ft_set_exec(argv[0]);
                execve(argv[0], argv, envp);
                perror("execve");
                exit(EXIT_FAILURE);
        }
        else
        {
                waitpid(-1, &wstatus, 0);
                return (WEXITSTATUS(wstatus));
        }
}

int	ft_exec_tree(t_tree *root, char **envp)
{
	char	*cmd;
	int		exit_code;

	exit_code = 0;
	if (root == NULL)
		return (0);
	cmd = (*root).content;
	if (ft_strncmp(cmd, "&", 2) && ft_strncmp(cmd, "|", 2))
		return (ft_exec_cmd(ft_split(cmd, ' '), envp));
	else if (!ft_strncmp(cmd, "&", 2))
	{
		exit_code = 1;
		if (!ft_exec_tree((*root).left, envp))
			exit_code = ft_exec_tree((*root).right, envp);
	}
	else if (!ft_strncmp(cmd, "|", 2) && ft_exec_tree((*root).left, envp))
			exit_code = ft_exec_tree((*root).right, envp);
	return (exit_code);
}
