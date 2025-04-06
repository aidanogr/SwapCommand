# SwapCommand, Windows Hook application to create a new hotkey for swapping two words

# WARNING! READ THIS FIRST
This script reads all of your keyboard strokes and uses your clipboard,
theres a good chance it will be blocked by your firewall.
This program also has no GUI, so be sure to only open one instance at a time. 
One way to prevent problems here would be to just make it a startup application 
in windows. 
Other ways of running are: Compiling and debugging the source code yourself in Visual Studio
or just starting the application once and closing it in task manager

<br />

# Download instructions
Once the project folder has been cloned, you may either run it yourself in Visual Studio or simply open .exe
to test, select a text and hit F10

<br />

If you want to run this program in the background and not mess with it, put the .exe in the following
directory: C:\Users\[YOUR USERNAME]\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup

<br />

# Video example 

https://youtu.be/GQaCv8Di9gQ

<br />

# Versions 
ONLY VERSION IS NOW 'Swap.exe', but the following still applies

Version 2 includes the "," delimiter, meaning for the same string:
" Follow, the leader " >> " leader, the Follow"

This version will be the prototyping space for testing new delimiters and key-sequences.
<br />
# Changes

