# MorphemeConnect
This program lets you open and edit DS2 Morpheme binaries alongside TimeAct files.
It can be used in the following ways:
1) Open an NMB file. The program will search for the Game folder in the parent path of the opened file, if it finds it it will then look for /timeact/chr and search for all the TimeAct files that share the NMB's character ID in the name and ask the user if they'd like to open one of them.
2) Open a TimeAct file. The program will parse the opened file and add the TimeAct list to the TimeAct tab in the Asset window.

# Preview Window
When opening an NMB, the program will attempt to find the character model in the parent path. If it finds one and it has valid vertex data in it, it will show the model in the Preview window. Note that c0001 do not have a model, player equipments are not supported yet.

![Immagine 2023-08-30 195652](https://github.com/LordRadai/MorphemeConnect/assets/22768664/9a817015-9e15-4b84-ae6d-bd7d6c5dfadb)

# Requirements
* DirectXTK
* ICU in your System Path folder
* ZLIB in your System Patch folder
