# CSCI164SeachW-EightPuzzle

Main16PuzzleDriver and Main8PuzzleDriver are the same file, one is used for the 16=5 tile puzzles, and the other for 8 tile puzzles. I seperated them because
I was using a staticly allocated array to improve speed, as I did not want to use a vector. Since the main function started to get very long, I decided to split the two
to prevent the same code from being written twice in a single file.

To run program, choose which main driver you would like (8 tile or 15 tile) and put it in your compiler. Then grab the GraphTraversalPlusHelperFunctions.cpp (where all
the traversing functions and graph structure is) then you can run it. Just be sure that both files are placed in the same file, so they can run together.
