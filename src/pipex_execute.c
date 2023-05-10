/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:47:54 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 09:41:56 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	Execute the command in the child process
/* TODO
 * 1. check if the command is in PATH or not
 * 1a. if in PATH, check if the command is in PATH and join it with the command
 * 1b. if not in PATH, check if the command is in the current directory
 * 1X. if the command is not found, exit with status 127
 * 2. if the command is found, check if the file is executable
 * 2X. if the file is not executable, exit with status 126
 * 3. check if it is the first process
 * 3a. if proc==0, check if the file is readable
 * 3aa. if the file is readable, open the file and dup2 it to stdin
 * 3aX. if the file is not readable, exit with status 2
 * 3b. if proc!=0, dup2 the previous pipe to stdin (write end)
 * 4. check if it is the last process
 * 4a. if proc==pipex->proc-1, check if the file is writable
 * 4aa. if the file is writable, open the file and dup2 it to stdout
 * 4aX. if the file is not writable, exit with status 2
 * 4b. if proc!=pipex->proc-1, dup2 the current pipe to stdout (read end)
 * 5. close the pipe and all files, leaving only STDIN and STDOUT open
 * 6. execve the command
*/
void	pipex_exec(t_pipex *pipex, int pnum)
{
}
