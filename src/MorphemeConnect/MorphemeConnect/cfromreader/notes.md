# Notes
this file is for general scrawlings and information i've gathered from the games, people, and code relating to souls structures.

| Format | Ext  | DS | DSR | DS2 | DS3 |
|--------|------|----|-----|-----|-----|
| BDF3   | bdt  |    |     |     |     |
| BDF4   | bdt  |    |     |     |     |
|xxxxxxxx|xxxxxx|xxxx|xxxxx|xxxxx|xxxxx|
| BHD5_1 | bhd5 |    |     |     |     |
| BHD5_2 | bhd5 |    |     |     |     |
| BHF3   | bhd  |    |     |     |     |
| BHF4   | bhd  |    |     |     |     |
|xxxxxxxx|xxxxxx|xxxx|xxxxx|xxxxx|xxxxx|
| BND3   | bnd  |    |     |     |     |
| BND4   | bnd  |    |     |     |     |


bhd are headers, bdt are data in the format the header specifies.
headers can essentially be considred "maps" or trees of the files.
load these into ram since they're small and easy to work with.

bnd files are the containers for the files. groups of mesh/animation/textures for a complete "thing" like an NPC or an enemy. example:
the c2320 object has an anibnd, chrbnd, and a chrtpfbdt.
chr is mesh, ani is animation, and tpf is texture pack format?

bdt's are sometimes refered to as DVDBNDs. 

bhf3 and bhf4 are pre DS2 split archive headers

chrtpfbdt files have their header located in the corresponding chrbnd files. if no chrtpfbdt is specified, the tpf files will be in the chrbnd file.

sometimes the textures for certain "things" are located in OTHER things.

enemies do not have weapons. unless its a human character. or dark souls 2.
the "weapon" you see is a part of their model

game has a texture pool and anything can pull from anything
wyvern boss has no texture in its chrbnd. it pulls one that was loaded by the map.
this is "wrong" but can totally be done. extremely cursed.

the structure *generally* goes (bdt+bhd)/bnd/(textures/meshes/animations)
as mentioned before, this isn't always the case. sometimes From gets freaky.

need to add in a failure for if trying to compile on big endian systems. i will not support them.


the structures needed for DSR characters are as follows:
dcx->bnd->tae,flver,hkx,hkpwv
bdt->tpf->dds

on initialization, DCX files must load their entire contents into memory. wether they release the memory after creating their file map is up to the progammer/application.

DCX files can have their file maps checked for data. if the data is found, the dcx can be loaded into memory again and the files needed will be taken. the DCX MUST be closed manually after each intial open. this way one file can be requested and multiple can be pulled at a time. this should work well given DCX files typically contain a single character or npc and thus all files would be needed at once. also don't wanna have too many open at once since the data is non trivial when you add it all up and it cannot be loaded piecemeal.

open DCX to a block of memory -> take the sections needed and put them into a cache -> mark the files as being loaded in the asset manager

things hiding in DCX files:
bnd
emeld
emedf
emevd
drb
flver
tpf

mostly flver and bnd

might need node based system to keep track of chains

file vs container: 
flver is file, dcx and bnd are containers

files have parent containers or are orphans. containers too.
eg:
struct node
{
	parent:
	child:
	data:
}

worst case: bnd -> dcx -> bnd -> lots of data files

honestly load whatever is in the DCX if one is found. cache its headers and be done with it. find some way to store a chain of vnodes to get the actual files if they are needed?


ways to open files:
directly opening the raw file from its actual path
knowing the character id you want?
idk.

there's two conflicting systems. the base filesystem, and the fact that some binders are a blob.
they cannot have individual files taken out. its all or nothing. so for those specific binders,
it'd make sense to just load the entire file into memory and leave it.