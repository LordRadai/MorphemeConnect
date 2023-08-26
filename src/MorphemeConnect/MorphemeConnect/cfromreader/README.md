# C++ FromSoftware Data Reader
A read only library for Souls game file formats. The scope for the library is limited to being read only, little endian, and Souls games only. It is intended for use as a layer for/like Assimp. For more fleshed out and featureful tools, check out the credits. There's read/write support, map editors, full libraries, and more. The code here wouldn't have been possible without those other tools and libraries.

## Validation
See my cfr-test repo.

## How to Use
You should be able to clone this repo onto your computer then include the cfromreader.hpp header file into your project. Note: by default you'll need the res/ folder from src/ in your binary directory for now. The res/ folder contains the file lists for hashing in order to access DVDBND data.

## Building on Linux
Check out my cfr-test repo, use a setup like that to get started.

## Buidling on Windows
See `building-on-windows.md` in `docs/setup/` for more information.

## Misc
This project currently is targetting Dark Souls PTDE due to Havok issues with the Remaster. More games/support may get added later. This code is primarily for my personal use in another project, and was initially abstracted for licensing reasons, but now its like this for organizational purposes. If you're wondering, no this code is not secure nor is it "memory safe". It's probably highly vulnerable to overflows and whatnot. Its not networked.

## Credits
JKAndarson's [SoulsTemplates](https://github.com/JKAnderson/SoulsTemplates) and [SoulsFormats](https://github.com/JKAnderson/SoulsFormats)<br/>
Katalash's [HavokLib](https://github.com/katalash/HavokLib) and [DSMapStudio](https://github.com/katalash/DSMapStudio)<br/>
Meowmaritus' [SoulsAssetPipeline](https://github.com/Meowmaritus/SoulsAssetPipeline)<br/>
HotPocketRemix's [UnpackDarkSoulsForModding](https://github.com/HotPocketRemix/UnpackDarkSoulsForModding)<br/>
?ServerName? for help with programming and advice in general<br/>
If your name is/or is not on here and you want that changed, please let me know.<br/>

## License
This code is hereby GPLv3! If you use this code, please be polite and credit the same people I did as their work was instrumental to this project and get their permission for their code if you are going to use it.