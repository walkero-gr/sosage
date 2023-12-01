# Sosage (Superfluous Open Source Adventure Game Engine)

***Note:** this repository is just a mirror of [the official
repository on Framagit](https://framagit.org/Gee/sosage), which should
be considered as the most up-to-date and reliable source for Sosage.*

## Dependencies

 - SDL2 (>= 2.0.14)
 - SDL2_ttf
 - SDL2-Mixer-X <https://github.com/WohlSoft/SDL-Mixer-X>
 - libyaml
 - liblz4 (only for _packaged_ version)
 - SDL2_image (only for _unpackaged_ version)

## Game Data

This repository only contains the source code of the Sosage engine:
game data are provided separately. To compile the game, you need to
specify the folder containing game data through the cmake variable
`SOSAGE_DATA_FOLDER`. That folder must contain the provided
`config.cmake` file.

Depending on whether you are using packaged game data (with few files
like `general.data`) or unpackaged game data (with a full tree and
files likes `images/interface/cursor.png`), Sosage will either require
`liblz4` or `SDL2_image`.

**Warning:** compiling the unpackaged version should only be done when
in the process of creating/modifying a game: for sharing a released
game, compiling the packaged version is strongly advised, as disk
usage and loading times become significantly reduced, providing a much
better experience of users.

## Compilation (GNU/Linux)

After installing dependencies:

1. `$ mkdir build && cd build`
2. `$ cmake .. -DCMAKE_BUILD_TYPE=Release -DSOSAGE_DATA_FOLDER=[where_the_data_is]`
3. `$ make`

For other platforms (Android, Emscripten, etc.), please refer to the
`README.md` files in the subfolders of `platform`.

## Packaging and unpackaging game data

The _Sosage Compressed Asset Packager_ (SCAP) is a tool provided in
`tools/SCAP`. It can be used both to compress game data (in order to
share a game with the best performances in terms of disk usage and
loading times) and to decompress game data (to access, study and
modify the raw images, sounds and documents of a shared packaged
game).

SCAP depends on `SDL2`, `SDL2_image`, `SDL2_ttf`, `liblz4` and `tbb`.

You can build SCAP by simply going to `tools/SCAP` and doing

1. `$ mkdir build && cd build`
2. `$ cmake .. -DCMAKE_BUILD_TYPE=Release`
3. `$ make`

To compress unpackaged game data located in `[input_folder]` and put
the packaged version in `[output_folder]`, call:

`$ ./SCAP [input_folder] [output_folder]`

To decompress packaged game data located in `[input_folder]` and put
the unpackaged version if `[output_folder]`, call:

`$ ./SCAP [input_folder] [output_folder] -d`
