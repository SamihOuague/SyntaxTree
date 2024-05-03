/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 03:28:17 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/03 10:26:50 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include <stdio.h>


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
		ft_exec_tree(root, envp);
	}
	else
		printf("NOT BALANCED\n");
	return (0);
}
