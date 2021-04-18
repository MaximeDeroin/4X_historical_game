#Gameplay rules

## General
The game is turn-based. Every player plays in order.

## New turn events
When a new turn begins, the following events occur:
  * For each city, the Food and Prod are applied
    * if the city reaches its food threshold, it grow by 1 citizen
    * if the city finishes its production, the building or unit produced is added to the city. 
    A created unit spawns in the city, or closest available tile in the city range.
    If there is no room in the city range, the unit is not created, but the next identical unit will cost 0 Prod.

## Turn actions
During its turn, the player can:
  * Move its units
  * For each city, choose a production, among the available units and buildings
  * Create a new city with a settler
  * For each city that has grown, choose which tile to work with the new citizen  

## Victory conditions
The first player to finish a Statue wins the game.