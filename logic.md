# Logic

## Intro

- Perform basic checks on user input
  - Are valid amount of arguments passed
  - Is map correct file extension
  - Is map correct (Blocked exits, Blocked collectibles, No player, ...) -> Leads into the rendering process
- Initialize variables (player, map, game, data)

## Rendering

Because everything has been found to be valid, start the rendering process,
Note: To prevent garbage and all that, read the map once and retain it's information for ezpz retrieval whenever needed.

- Read the map line by line (get_next_line)
- Store each line into a linked list { str = "line"; next = NextLine } (Better for stuff because 2 dimensional)

## Movement

- MLX hook to handle key presses,
- Check if move is valid (NextPos is wall / collectible or whatever)
- Destroy previous thing and render in that specific position the new stuff
