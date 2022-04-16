# CSCI164SeachW-EightPuzzle

Main16PuzzleDriver and Main8PuzzleDriver are the same file, one is used for the 16 tile puzzles, and the other for 8 tile puzzles. I seperated them because
I was using a staticly allocated array to improve speed, as I did not want to use a vector. Since the main function started to get very long, I decided to split the two
to prevent the same code from being written twice in a single file.
