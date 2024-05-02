/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:17:45 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/02 01:24:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"

t_tree  *ft_tree_new(void *content)
{
        t_tree  *node;

        node = malloc(sizeof(t_tree));
        if (node == NULL)
                return (NULL);
        (*node).content = content;
        (*node).left = NULL;
        (*node).right = NULL;
        return (node);
}

t_tree  *ft_break_expr(char *str, int index)
{
        t_tree  *node;
        char    *tmp;
        char    *op;

        tmp = ft_strdup(str);
        *(tmp + index + 1) = '\0';
        op = ft_strdup((tmp + index));
        *(tmp + index) = '\0';
        node = ft_tree_new(op);
        (*node).left = ft_tree_new(ft_strtrim(tmp, " "));
        (*node).right = ft_tree_new(ft_strtrim(tmp + index + 2, " "));
        return (node);
}

void    ft_str_to_tree(t_tree **root)
{
        t_list  *stack;
        char    *expr;
        int             i;

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
