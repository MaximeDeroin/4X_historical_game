# City rules


## Citizen
When a city is created, it has 1 citizen. This citizen works the city original tile.
Whenever a city grows, it win 1 citizen. The additional citizen can work any tile in city range.
In every turn, a citizen consumes 2 Food.

## Grow the city
Formula for next level with N the current city level:
food needed = 6 + 4*(N-1)
examples:
  * Level 1 : 6 Food to level 2
  * Level 2 : 10 Food to level 3

## City range
City range is defined as follows: 
The city original tile is of range 0.
in each of the 4 directions(up, down, left and right), the tile adjacent to the city tile is of range 1.
The adjacent tiles of a range 1 tile is of range 2.
The adjacent tiles of a range 2 tile is of range 3.

The city range can work tiles of range 0 to 3.

## Settling rules
A city can be settled on Ground tiles, at least at a range 4 of every other cities.