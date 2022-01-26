# pipex
UNIX Project for 42 school
This project is meant to reproduce this shell command : ```< file1 cmd1 | cmd2 > file2```.

The bonus reproduce multiple pipes such as : ```< file1 cmd1 | cmd2 | cmd3 | ... > file2``` and also this command ```cmd << LIMITER | cmd1 >> file```.

# Compilation & execution

Use the ```make``` command to compile the program. For multiple pipes and here_doc, use ```make bonus```.

Then, launch the program using the command : ```./pipex file1 cmd1 cmd2 file2``` or ```./pipex_bonus here_doc LIMITER cmd1 cmd2 cmd3 ... file``` or ```./pipex_bonus file1 cmd1 cmd2 ... file2```
