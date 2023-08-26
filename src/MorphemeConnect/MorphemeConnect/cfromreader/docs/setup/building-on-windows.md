# Building CFromReader on Windows
To build on Windows, you'll need to setup the environment a bit to ensure your system can fulfil the dependencies it requires.

You'll need to install the following dependencies to your computer:
```
CMake
Git (terminal version, not the GUI)
Visual Studio or VSCode (Visual Studio recommended)
VCPKG
ZLIB
CMEM
```

## CMake
Grab CMake from the official site. I used all defaults in the installer I think.

## Git
Grab from the gt-scm website. I used the installer with defaults, though you can probably change the editor and all to be whatever you want. I made sure to leave the commit/checkout line format as the cross platform one. It is default.

## Visual Studio
Again, more defaults. Make sure to have the following parts installed:
```
C++ core desktop features
C++ CMake tools for Windows
Windows Universal C Runtime
C++ Clang Compiler for Windows
```
I'm not sure if these are all actually needed, but I have them and they sound important.

## VSCode
Install it, then add on the suggested extensions. So CMake, C++ stuff, etc.

## VCPKG
I recommend using the instructions here: https://github.com/microsoft/vcpkg#quick-start-windows

Here's a quick rundown: 
```
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
cd vcpkg
vcpkg integrate install
```

If the commands don't work for you, try playing with the syntax a bit. Try using the `git-bash` application, just make sure you know where you're installing to. You can also try using CMD, PowerShell, or whatever other terminals you like.

You'll need to create a new system environment variable. Name it `VCPKGROOT` and set the value to where you installed install `vcpkg` to. I installed it to `C:\dev\vcpkg` so that is what I set the variable to.

Now make sure to add the package installation locations to your SYSTEM PATH environement variable. Search in the start menu for `environment variables`, then click `Environmnent Variables...` at the bottom. On the bottom are the SYSTEM variables. Select the one called `Path` and click `edit`.

Add the following four paths. Each as their own line.
```
%VCPKGROOT%\installed\x64-windows\include
%VCPKGROOT%\installed\x64-windows\lib
%VCPKGROOT%\installed\x86-windows\include
%VCPKGROOT%\installed\x86-windows\lib
```

## ZLIB
Installing is as simple as running this commmand from the location of your VCPKG install:
```
vcpkg install zlib:x64-windows
```

## CMEM
This gets too heavy into project setup. I'd recommend just cloning https://github.com/betstick/cfr-test as its own folder and looking at how it is set up. CMEM is a library dependency for cfromreader. So whatever CMake project is using cfromreader, needs to include the CMEM library prior.

## Extra Notes
Here's some stuff you can try if you run into problems.
If you have issues, try rebooting. It might help. 
Confirm your Path variables are set correctly.
Use the cfr-test repo as the base for your project.
@ me on ?ServerName? in #programming and I'll see if I can help.
Install Linux.