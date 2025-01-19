# Dev Log:

This document must be updated daily by EACH group member.
## Stella Yampolsky

### 2025-01-07 - Create files
Create the file player.c, plan out usage in the comments. Time spent writing: 2 minutes Time spent wrangling pulsar: 10 minutes

### 2025-01-08 2:47 pm - start methods
Add node + library code from old project, begin modifying on branch Start skip + shuffle_next methods in player.c

### 2025-01-09 2:47 pm - modify old code, shuffle
Modify node + library code, work on shuffle method read Edmund's code to understand how files are handled

### 2025-01-09 11:45 pm Finish shuffle, pause signals
Finished the shuffle code Did research on signals, wrote pause with sighandler method (maybe, needs further testing)

### 2025-01-10 2:50 pm
write header files read group code clean player.c (rewrite later)

### 2025-01-13 2:48 pm
Rewrite library, node, main code to be compatible, need to test

### 2025-01-14 2:49 pm shuffle skip loop queue
Rewrite shuffle + skip to be compatible with music_player
Write loop
Plan queue

### 2025-01-15 2:21 am
Fix + debug, write queue

### 2025-01-15 2:50 pm - Add header files and fix function calls
Add header files and fix function calls

### 2025-01-16 2:47 pm - Documentation
Add documentation to player.c

### 2025-01-17 2:50 - fixes + documentation
Minor fixes and documentation on node.c

## Edmund Liang

### 2025-01-07 - Add music_player files
Make the music_player .c and .h files and look into how to use mpg123.

### 2025-01-08 - Add basic music playing capabilities
Add a function to play a file using mpg123 using forking and execvp, but prints out "Can't set terminal attributes".

### 2025-01-09 - Use system instead of execvp to specify redirect
Switch to system instead of execvp to easily specify redirections, will probably later switch to execvp and redirection.

### 2025-01-10 - Add setup for communicating between program and mpg123 using pipes
Use pipes to read from and write to the player for more fine-tuned control.

### 2025-01-13, 2:36 PM - Split into multiple functions
Split the program into multiple functions so that they can be easily called from another file.

### 2025-01-13, 2:50 PM - Add pause_playback and stop_playback
Add the pause_playback and stop_playback functions that send the appropriate commands to the player.

### 2025-01-14, 2:49 PM - Added more player functions, check_frame_info not working yet
Added jump_absolute, jump_relative, set_volume functions, as well as check_frame_info which is not working yet. Also added the frame_info struct which the function uses.

### 2025-01-15, 2:27 PM - Fix read_player and check_frame_info
read_player now sets the character after the last character of what was read to NULL so that irrelevant stuff is not read when reading from the player. By removing the seconds and seconds_left parts of the frame_info, check_frame_info seems to work.

### 2025-01-15, 2:50 PM - Add seconds info, but does not work
Add back the seconds and seconds_left parts, but now it does not work (segfaults at times).

### 2025-01-16, 2:50 PM - Fix check_frame_info?
After some time debugging, check_frame_info seems to work unexpectedly - needs to be investigated.

### 2025-01-17, 2:32 PM - Fix check_frame_info
Turns out the problem was not mallocing to create the struct, so now it works.

### 2025-01-17, 2:43 PM - Use execvp and redirection instead of system
Using system takes longer to parse the arguments and is platform-dependent, so switch to using execvp and redirection.

### 2025-01-17, 7:25 PM - Fix node.h
Fix minor syntax errors in node.h.

### 2025-01-18, 2:07 PM - Start working on interactive player
Start working on an interactive player, which is a stretch goal but will make the user interface cleaner. It will accept keyboard input to control the music player, and will display the progression of the song. select is used to listen to both stdin and the player, and termios is used to make it so that key presses are not outputted and are sent one at a time instead of waiting for Enter. ANSI codes are used to redraw the output.

### 2025-01-18, 3:37 PM - Add instructions and progress bar, allow function to return int to describe how the song stopped
Add instructions for user input and a visual progress bar. The function is changed to int so that it can return END, SKIP, or QUIT to describe how the song stopped.

### 2025-01-18, 4:53 PM - Fix jump_relative, add functionality for the rest of the options
Fix jump_relative as it did not work for negative numbers, and add functionality for jumping, volume changing, skipping, and quitting.

### 2025-01-18, 5:07 PM - Add back check_frame_info
check_frame_info was removed somehow, so I added it back in.

### 2025-01-18, 5:34 PM - Remove skip function, change player and main to use interactive player instead
Remove skip function in player as skipping is now handled by the interactive player, and adapt player and main to use interactive_player instead of play_file.

### 2025-01-18, 5:49 PM - Use queueSongs in main
Call queueSongs from main for playing the songs in order.

### 2025-01-18, 7:03 PM - Remove skip function, add proper responses to q
Remove skip function (again), and make playlists stop playing when the user presses q.

### 2025-01-18, 7:15 PM - Make shuffle use interactive_player
Make the new shuffle function use interactive_player.

### 2025-01-18, 7:39 PM, 7:51 PM - Fix random characters appearing in progress bar
Fix the random characters appearing at the end of the progress bar, which was due to not ending the string with NULL.

### 2025-01-18, 10:30 PM - Fix write_player, add check_error, fix skipping twice
Fix write_player by writing only the number of bytes according to the string length, add error checking, and fix how songs are skipped twice whenever e is pressed.

### 2025-01-18, 10:38 PM - Remove get_ functions
Remove the get_to_player, get_from_player, and get_buff functions as they aren't called.

### 2025-01-18, 10:50 PM - Make player_setup a void and combine it with connect_player
player_setup was originally an int and returned whether it was the main program or not, but it is now a void since the mpg123 fork will not return. player_setup is combined with connect_player as connect_player is only called by player_setup.

### 2025-01-18, 11:24 PM - Switch to unnamed pipes, add redirection error messages
Use unnamed pipes instead of named ones so that multiple instances of the program can run at the same time without interfering, and add proper error messages for the redirection.

### 2025-01-18, 11:36 PM - Remove check for player in main.c
Remove check for player in main.c (as player_setup is now a void).

### 2025-01-19, 10：53 AM - Make lowercase artists still go in alpabetical categories
Make artists starting with lowercase letters go into the alphabetical buckets instead of the symbols one.

### 2025-01-19, 11:11 AM - Use perror for mpg123 error
Use perror to print the mpg123 errors and start them with "Error: ".

## Keith Hah

### 2025-01-02 - Brief description
Expanded description including how much time was spent on task.

### 2025-01-07, 2:50 PM - Merged teams and planned functionality
Revised proposal to accurately reflect new updated team and included new features like skip and looping songs. Discussed how to divide groupwork, and each member was then assigned a role.

### -01-08, 2:48 PM - Started save and load functions
Created file.c and started working on save_library and load_library.

### 2025-01-09, 12:00 AM - Worked on save and load functions
Used the library.c and node.c from old project as reference and created makefile and main.c. Finished up save_library

### 2025-01-09, 1:30 AM - Worked on save and load functions
Finished up load_library and went over save_library. Wrote data to txt file in main.c. Encountered segfault when loading library, will fix later.

### 2025-01-09, 2:46 P.M. - Debugged save_library
Fixed segfault caused by reset function. Fixed the format of the songs that were saved to the text file.

### 2025-01-10, 12:42 A.M - Debugged library functions
Fixed txt file format using strlen, error with loading the library correctly. Installed mpg123, not sure if it works or not.

### 2025-01-10, 2:48 P.M - Started add library function
Temporarily ignoring load_library error, started on adding songs function.

### 2025-01-13, 2:47 P.M - Located bug in load_library
Found reason for the bug, which was due to the size of bytes occupied by the additional write statements. Also noticed different output when using sizeof vs strlen. Now it loads all the songs, but doesn't sort them properly.

### 2025-01-14, 12:43 A.M - Recoded load_library
Decided to make a menu for loading, adding, saving, etc. Changed main.c to print the menu out and use fgets for user input. Changed load_library to use buffer to handle file input. Also added add_library. Next steps will be to finish main.c and other library functions.

### 2025-01-14, 2:48 P.M - Worked on user functions in main.c
Added new functions to work on like playing specific songs or making new playlists. Finished the add song, save playlist, and view playlist. Almost done with looking up a song.

### 2025-01-15, 2:48 P.M - Coded more user functions in main.c
Debugged save_library and completed search artist function. Also played around with the formatting of the menu. Creating new playlist is in progress, working on creating new txt files for each playlist.

### 2025-01-16, 2:45 P.M - Worked on playlist editing in main.c
Encountered a practical issue on how to allow user to name and make multiple playlists, and to save to the playlist of their choice. Worked on creating new playlist and edited save playlist function.

### 2025-01-17, 2:47 P.M - Added more functions in main.c
Added functions like loop, skip, delete playlist. Finished delete song and working on delete playlist.

### 2025-01-17, 10:47 P.M - Worked on more functions in main.c and debugged other c files
Completed loop, shuffle, create playlist, delete playlist, play song, and skip song. Also fixed sighandle error (control c leads to unkilled child processes) and multiple definition error (searched up extern). 

### 2025-01-18, 12:56 A.M - Finished main.c
Tested the functions for additional bugs and made improvements to load and view playlist and player.c. Will continue reviewing tomorrow.

### 2025-01-18, 3:45 P.M - Edited main.c for filename field
Modified main.c to include filename parameter. Also removed skip function in main and reorganized order.

### 2025-01-18, 5:07 P.M - Fixed errors with saving and loading 
Fixed save and load playlist function and changed node.c remove node function. Also changed save library and load library so now title artist and filename are properly read.

### 2025-01-18, 7:16 P.M - Fixed errors with empty playlist and deleting 
Modified main.c so user has to create playlist first. Added errors if any input was left blank and tested it.
 
