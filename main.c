/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 03:28:17 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/02 05:36:15 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

char    *set_exec(char *cmd)
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
	printf("%s\n", cmd);
        free(abs_path);
        return (cmd);
}

int     exec_cmd(char **argv, char **envp)
{
        pid_t   pid;
        int             wstatus;

        pid = fork();
        if (pid < 0)
                return (-1);
        else if (pid == 0)
        {
                argv[0] = set_exec(argv[0]);
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

void	ft_print_tab(int level)
{
	int	i;

	i = -1;
	while ((++i) < level)
		printf("\t");
}

void	ft_print_tree(t_tree *root, int level)
{
	if (root == NULL)
	{
		ft_print_tab(level);
		printf("<---- empty ---->\n");
		return ;
	}
	ft_print_tab(level);
	printf("Value [%s]\n", (char *)(*root).content);
	ft_print_tab(level);
	printf("Left Node\n");
	ft_print_tree((*root).left, level + 1);
	ft_print_tab(level);
	printf("Right Node\n");	
	ft_print_tree((*root).right, level + 1);
	ft_print_tab(level);
	printf("Done\n");
}

t_list	*ft_pop(t_list **queue)
{
	t_list	*tmp;

	tmp = *queue;
	*queue = (**queue).next;
	return (tmp);
}

void	exec_tree(t_tree *root, char **envp)
{
	t_list	*queue;
	t_list	*poped;
	t_tree	*node;

	node = NULL;
	queue = NULL;
	ft_lstadd_back(&queue, ft_lstnew(root));
	while (queue != NULL)
	{
		node = (*queue).content;
		if ((*node).left != NULL)
			ft_lstadd_back(&queue, ft_lstnew((*node).left));
		if ((*node).right != NULL)
			ft_lstadd_back(&queue, ft_lstnew((*node).right));
			
		poped = ft_pop(&queue);
		node = (*poped).content;
		if (!ft_strchr("&|", *(char *)(*node).content))
			exec_cmd(ft_split((*node).content, ' '), envp);
		free(poped);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tree	*root;
		
	if (argc != 2)
		return (1);
	root = ft_tree_new(ft_strtrim(argv[1], " "));
	if (ft_isbalanced(argv[1]))
	{
		ft_str_to_tree(&root);
		ft_print_tree(root, 0);
		exec_tree(root, envp);
	}
	else
		printf("NOT BALANCED\n");
	return (0);
}
