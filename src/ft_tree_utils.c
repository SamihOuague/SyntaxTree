/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:19:48 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/02 01:24:31 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"

void    ft_null(void *content)
{
        (void)content;
        content = NULL;
        return ;
}

int     ft_del_first(t_list **stack)
{
        t_list  *tmp;
        if (stack == NULL || *stack == NULL)
                return (0);
        tmp = *stack;
        *stack = (**stack).next;
        free(tmp);
        return (1);
}

int     ft_isbalanced(char *str)
{
        t_list  *stack;
        int             ret_val;
        int             i;

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

int     ft_op_out(char *expr)
{
        t_list  *stack;
        int             i;

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
