# Minishell
`minishell` is a simple shell program developed as a part of the 42 School curriculum.  
This project aims to mimic a basic bash shell, introducing students to the intricacies of process creation,
signaling, and basic shell functionalities in a Unix/Linux environment.  
It is developed in C, adhering to the 42 School's norminette coding standards.  

## Features
Command Execution: Ability to execute commands found in the PATH.  
Builtin Commands: Implements several builtin commands including echo, cd, pwd, export, unset, env, and exit.  
Signal Handling: Handles signals (Ctrl-C, Ctrl-D, and Ctrl-\) similar to bash.  
Environment Variables: Supports setting, unsetting, and using environment variables.  
Redirections: Handles input and output redirections (>, >>, <) as well as pipes (|).  
Quoting: Supports single and double quotes, allowing for command arguments that include spaces.  

## Installation
Clone the repository and compile minishell using Make:
```
git clone https://github.com/guillaume-salle/minishell.git
cd minishell
make
```
This will generate the minishell executable in your project directory.

## Usage
To run minishell, execute the following command in your terminal:
```
./minishell
```
You'll be presented with a prompt where you can start typing your commands, similar to bash.


