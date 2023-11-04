# SwapCommand, Windows Hook application to create a new hotkey for swapping two words

# WARNING! READ THIS FIRST
This script reads all of your keyboard strokes and uses your clipboard,
theres a good chancce it will be blocked by your firewall.
This program also has no GUI, so be sure to only open one instance at a time. 
One way to prevent problems here would be to just make it a startup application 
in windows. 
Other ways of running are: Compiling and debugging the source code yourself in Visual Studio
or just starting the application once and closing it in task manager



# Download instructions
Once the project folder has been cloned, you may either run it yourself in Visual Studio or simply open .exe
to test, select a text and hit F10


# Versions 
Version one just uses spaces as delimiter, meaning the following string:
" Follow, the leader " >> "leader the Follow,"

This is a stable release...







Version 2 includes the "," delimiter, meaning for the same string:
" Follow, the leader " >> " leader, the Follow"

This version will be the prototyping space for testing new delimiters and key-sequences.

# Changes

