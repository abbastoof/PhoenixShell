# PhoenixShell Project
This project is a minimal shell implementation in C, supporting various built-in functions like `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`, as well as the ability to execute other commands, handle signals, and manage environment variables. The project includes lexer and parser modules to process and execute commands, a tree structure to represent the commands, and several utility functions.

## First thing first
[A quick introduction to bash](/bash_intro.md)

## Envirenment variables
Use linked list of structure to store envirenment variables. We divided the Envirenment variables to keys and values.
Keep it in mind to turn the env linked list to a char **ptr before the execution in exec command part.

## Lexical analysis
Take user input and store it into a linked-list as "tokens". Each "token" contains a "token value"(string) and a "token type"(int).
It would be better to use a linked list for this part since we might receive an empty "" from the user input.
For example the behaviour of bash for this command "echo "" "" | cat -e" the result would be
 $
 The bash will interpret the "" as NULL and insert a space between two null arguments

## Quotes validity and Syntax
Since the school's subject didn't ask to consider the open quotes. So we just check if the user left any quotes open, if the quotes validity were fine we could move on to the Syntax errors.
What is a Syntax error in bash?
When the bash interpreter encounters an angle bracket or a pipe that isn't used correctly - for example:
echo "hello world" <

In this part if we find any kind of error we should free our linked lists of tokens and environment variables and return the prompt.

## Expansion
The expansion is processed after the creation of envirenment variables' linked list and the lexical token list.
Based on the subject and bash behaviour we expand when the a double quotes or without quotes.
For example "echo "$USER"" will show username from the environment variables but the command "echo '$USER'" will show $USER as the result on STDOUT.

## Parsing
We take the token list and send it to the create_tree to create an binary tree.
The tree will have all the pipes as forking point and have left and right as commands.
When there is more then 1 pipe, the first pipe will be connected to the second pipe's left side.
The second pipe will be connected to the third pipe's left side. And so on...
If there is redirection token, we will create a linked-list to store all redirection types and it's filename inside.
All the "WORD" token directly after the redirection token will be the file name, the other WORDs after the first WORD will all be put into the command's argument list.
(ex: `echo > a hello > b` becomes: `["echo", "hello"]/(TOKEN_OUTPUT)"a"->(TOKEN_OUTPUT)"b"` and `> a echo hello > b` will produce the same element as above.
In our tree the redirectors are kept in a linked list.
Be careful to check and run the heredocs during in the Parser.
So the command: `echo hello > file1 | cat file2 | grep a | wc > outfile1 -l > out1 >out2 ` will produce a tree like:
```
                            PIPE
                           /    \
                          /      CMD
                       PIPE      ["wc", "-l"]
                       /  \      (TOKEN_OUTPUT)"out1"->(TOKEN_OUTPUT)"out2"
                      /    CMD
                     PIPE  ["grep", "a"]
                    /    \
                  CMD     CMD
    ["echo", "hello"]     ["cat" "file2"]
  (TOKEN_OUTPUT)"file1"
```

## Features
- Built-in functions: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.
- Execution of external commands.
- Signal handling (SIGINT, SIGQUIT).
- Redirections (input, output, append, heredoc) and pipes.
- Environment variable expansion.
- Syntax error handling.

## Usage
1. Clone the repository.
2. Run `make` to compile the source files.
3. Run `./phoenix` to start the shell.

## Example
```
$ ./phoenix
🐦‍🔥 Phoenix Prompt> echo Hello, world!
Hello, world!
🐦‍🔥 Phoenix Prompt> pwd
/home/user/phoenix
🐦‍🔥 Phoenix Prompt> cd ..
🐦‍🔥 Phoenix Prompt> pwd
/home/user
🐦‍🔥 Phoenix Prompt> exit
$
```

## Conclusion
The phoenix project is a challenging and rewarding exercise in systems programming, requiring a deep understanding of various aspects of the C programming language, as well as knowledge of shell behaviour, environment variables, and signal handling. The final result is a functional shell with support for various built-in functions, command execution, redirections, and pipes. This project provides a strong foundation for further exploration and development in the field of systems programming.
