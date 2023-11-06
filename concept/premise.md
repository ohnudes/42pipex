
/*	Prototype
 *	./pipex file1 cmd1 cmd2 file2
 *	file = file name
 *	cmd are shell commands with parameters
 *	
 *	Examples:
 *	./pipex infile "ls -l" "wc -l" outfile
 *	< infile ls -l | wc -l outfile
 */

/* Functions allowed:
 *	close
 *	read
 *	write
 *
 *	malloc
 *	free
 *
 *	perror
 *	strerror
 *
 *	access
 *	
 *	dup
 *	dup2
 *	excve
 *	exit
 *	fork
 *	pipe
 *	unlink
 *	wait
 *	waitpid
 *
 */

/* WARNINGS
 *	memory leaks
 *	segfaults
 *	bus error
 *	double free
 *	etc
 */

/* Bonus
 * 1. multiple pipes
 * file 1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
 * 2. support << and >> when the first parameter is
 * here_doc
 * i.e
 * ./pipex here_doc LIMITER cmd cmd1 file
 * as
 * cmd << LIMITER || cmd1 >> file
 */
