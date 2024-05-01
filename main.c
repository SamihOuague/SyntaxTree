/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 03:28:17 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/01 14:40:19 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef struct s_tree
{
	void		*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

void	ft_null(void *content)
{
	(void)content;
	content = NULL;
	return ;
}

t_tree	*ft_tree_new(void *content)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (node == NULL)
		return (NULL);
	(*node).content = content;
	(*node).left = NULL;
	(*node).right = NULL;
	return (node);
}

t_tree	*ft_break_expr(char *str, int index)
{
	t_tree	*node;
	char	*tmp;
	char	*op;

	tmp = ft_strdup(str);
	*(tmp + index + 1) = '\0';
	op = ft_strdup((tmp + index));
	*(tmp + index) = '\0';
	node = ft_tree_new(op);
	(*node).left = ft_tree_new(ft_strtrim(tmp, " "));
	(*node).right = ft_tree_new(ft_strtrim(tmp + index + 2, " "));
	return (node);
}

int	ft_del_first(t_list **stack)
{
	t_list	*tmp;
	if (stack == NULL || *stack == NULL)
		return (0);
	tmp = *stack;
	*stack = (**stack).next;
	free(tmp);
	return (1);
}

int	ft_isbalanced(char *str)
{
	t_list	*stack;
	int		ret_val;
	int		i;

	i = -1;
	ret_val = 1;
	stack = NULL;
	while (*(str + (++i)) != '\0')
	{
		if (*(str + i) == '(')
			ft_lstadd_front(&stack, ft_lstnew((str + i)));
		else if (*(str + i) == ')' && !ft_del_first(&stack))
		{
			ret_val = 0;
			break ;
		}
	}
	if (ret_val)
		ret_val = stack == NULL;
	ft_lstclear(&stack, ft_null);
	return (ret_val);
}

int	ft_op_out(char *expr)
{
	t_list	*stack;
	int		i;

	i = -1;
	stack = NULL;
	while (*(expr + (++i) + 1) != '\0')
	{
		if (*(expr + i) == '(')
			ft_lstadd_front(&stack, ft_lstnew((expr + i)));
		else if (*(expr + i) == ')')
			ft_del_first(&stack);
		else if (ft_strchr("&|", *(expr + i))
				&& *(expr + i + 1) == *(expr + i) 
				&& stack == NULL)
			return (1);
	}
	return (0);
}

void	ft_str_to_tree(t_tree **root)
{
	t_list	*stack;
	char	*expr;
	int		i;

	stack = NULL;
	expr = (**root).content;
	i = ft_strlen(expr) - 1;
	if (*(expr) == '(' && *(expr + i) == ')')
	{
		*(expr + i) = '\0';
		(**root).content = ft_strtrim(expr + 1, " ");
		ft_str_to_tree(root);
	}
	i = 0;
	while (*(expr + i) != '\0')
	{
		if (ft_strchr("&|", *(expr + i))
			&& stack == NULL && i > 0
			&& *(expr + i + 1) == *(expr + i))
		{
			*root = ft_break_expr(expr, i);
			ft_str_to_tree(&(**root).left);
			ft_str_to_tree(&(**root).right);
		}
		else if (*(expr + i) == '(')
			ft_lstadd_front(&stack, ft_lstnew((expr + i)));
		else if (*(expr + i) == ')')
			ft_del_first(&stack);
		i++;
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

int	main(int argc, char **argv)
{
	t_tree	*root;

	if (argc != 2)
		return (1);
	root = ft_tree_new(ft_strdup(argv[1]));
	if (ft_isbalanced(argv[1]))
	{
		printf("IS BALANCED\n");
		ft_str_to_tree(&root);
		ft_print_tree(root, 0);
	}
	else
		printf("NOT BALANCED\n");
	return (0);
}
