# cub3D - My First RayCaster with miniLibX

This project is a simple RayCaster implemented using miniLibX, allowing you to explore a maze with textured walls. The program is designed to display different wall textures, set floor and ceiling colors, and provide smooth window management. The user can navigate through the maze using arrow keys and close the window cleanly with the ESC key or the red cross on the window frame.

## Prerequisites

- The project uses miniLibX, either the version available on the operating system or from its sources.
- The management of the window must be smooth, including changing to another window and minimizing.
- Displayed wall textures vary depending on the wall's facing side (North, South, East, West).
- Floor and ceiling colors can be set to two different ones.

## Usage

To run the program, provide a scene description file with the .cub extension as the first argument:

```bash
make && ./cub3D path/to/your_scene.cub
```
## Scene Description File

- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N, S, E, or W for the player's start position and spawning orientation.
- The map must be closed/surrounded by walls, and any misconfiguration will result in an error.
- Each type of element in the scene description file can be separated by one or more empty lines.
- Elements can be set in any order in the file, except for the map content, which must be the last.
- Each element's information can be separated by one or more spaces.
- Spaces are valid parts of the map, and the program should handle them appropriately.

## Example of a Minimal Scene Description File
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
## Error Handling
- If any misconfiguration is encountered in the file, the program will exit properly and return "Error\n" followed by an explicit error message.

## Acknowledgments
- This project is part of the curriculum at 42 Heilbronn.
