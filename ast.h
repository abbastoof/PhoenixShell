/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:45:44 by atoof             #+#    #+#             */
/*   Updated: 2023/06/13 16:11:52 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef AST_H
// # define AST_H

// // AST Node Structure
// typedef struct s_astnode
// {
// 	int					type;
// 	char				*value;
// 	struct s_astnode	*left;
// 	struct s_astnode	*right;
// }						t_astnode;

// // Function Declarations

// // AST Construction
// t_astnode				*build_ast(t_token *tokens);
// t_astnode				*create_ast_node(int type, char *value);
// void					free_ast(t_astnode *node);

// // AST Execution
// void					execute_ast(t_astnode *node);

// // AST Cleanup
// void					cleanup_ast(t_astnode *node);

// #endif