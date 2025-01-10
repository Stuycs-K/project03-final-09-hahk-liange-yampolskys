# Dev Log:

This document must be updated daily by EACH group member.
## Stella Yampolsky

### 2025-01-07 - Create files
Create the file player.c, plan out usage in the comments. Time spent writing: 2 minutes Time spent wrangling pulsar: 10 minutes

### 2025-01-08 1:47 pm - start methods
Add node + library code from old project, begin modifying on branch Start skip + shuffle_next methods in player.c

### 2025-01-09 1:47 pm - modify old code, shuffle
Modify node + library code, work on shuffle method read Edmund's code to understand how files are handled

### 2025-01-09 11:45 pm Finish shuffle, pause signals
Finished the shuffle code Did research on signals, wrote pause with sighandler method (maybe, needs further testing)

## Edmund Liang

### 2025-01-07 - Add music_player files
Make the music_player .c and .h files and look into how to use mpg123.

### 2025-01-08 - Add basic music playing capabilities
Add a function to play a file using mpg123 using forking and execvp, but prints out "Can't set terminal attributes".

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
