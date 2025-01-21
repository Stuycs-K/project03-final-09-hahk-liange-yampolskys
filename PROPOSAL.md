# Final Project Proposal

## Group Members:

Stella Yampolsky, Keith Hah, Edmund Liang

# Intentions:
Create a music player program. We will build upon project 1 by incorporating a music player, saving the library data, and using actual music files. The user will be able to add files from the directory of the program to the library, and play them.

# Intended usage:
Running the program will prompt the user to type in the commands for what they want to do, whether it's add songs, play songs, loop songs, view their library, and more.

# Technical Details:
The project will allocate memory and work with files (the music library), write and read files (playlist data), use processes (playing the music with fork and execvp), use signals (to handle user Ctrl+C), and use pipes (communication between main program and music player).

- Edmund: Execvp for the music player using mpg123, interactive music player
- Stella: Music player functions like looping, shuffling, sorting, etc.
- Keith: Menu function, saving files, adding files, reading files.

We will be using arrays and linked lists.

The project will need the algorithms needed for the original project (searching, sorting, etc.), a shuffling algorithm, as well as algorithms for processes and saving the library data.

# Intended pacing:

- Skeletons and organization: 1/8
- Modify project 1 to incorporate new features: 1/9
- Basic music playing capabilities and save & load library functions: 1/11
- Queue function and add library data: 1/13
- Menu layout and loop and skip functions: 1/14
- Advanced music player functions and test mp3 files from directory: 1/15
- Modify shuffle function (with fisher yates shuffle): 1/16
- Debug user functions: 1/17
- Interactive player: 1/18
- Debug and test interactive player: 1/19
- Final overview and debugging and video presentation: 1/20
