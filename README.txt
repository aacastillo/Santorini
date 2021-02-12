Alan Castillo
Video: https://youtu.be/OXpK0iNkXMM
Note: Put the playback speed to a comfortable speed, I talk slow in this video.

Hi! 

So the main data strucuture used in my program was the
multidimensional array. There was a lot of algorithms and functions
used to make the game functions properly. I used functions to display
the board matrix for both the player and the AI for each move they
made, functions that checked the validity of the player's input, and
functions that updated the board in congruence with the
(de)construction nature of each type of players (TOP) move (Delivery
a. and f.).

	Just P.S. I use the TOP acronym a lot in my function
	arguments and in my comments. There will reminders of what it stands
	for throughout the code comments.

In the initial set up of the game. The players is prompted to choose
a position and told to put their input as (row column), the same
format for inut is consistent throughout the game and the program
checks for edge cases where there code is invalid such as not picking
an adjacent space, picking an occupied space, or picking a space that
is out of bounds. The player will always be reprompted being told the
error and asking for new input (Delivery b. and c.).

After each move from the AI or player, the program checks if the game
is over.  If the function gameOver() returns 'P' then the loop is broken
 and the player wins and is congratulated. If the player does not win then it
is the AI's turn, then gameOver() is checked and if it returns 'A'
then the AI wins and the loop is broken and the player is prompted
that AI has won. If the AI does not win then the loop starts all over
again asking the player to move (Delivery d.).

An AI exists in the game and mainly tries to stay in the center of
the board unless it's new chosen positions are already occupied by
the player. In which case it will only move horizontally or
vertically, but not both (delivery e.).

Outside of the scanf, printf, and main functions, the program uses 10
functions to be fully operational (design a.).

The display functions take the multidimensional array called "board",
which is the only global variable, as an argument. The display
functions is called many times throughout the program to show each
move of the Type of Player (Design b. and f.).

Iteration is used many times to traverse the board. First iteration
is used to set up the board matrix and in the construction functions
(Design c.).

-------------------------------------------------------------------

	Implentation specifics for construction function

		Implementing the (de)construction nature of each type
		of player was going to be a massive function. So I
		just split it up into two functions. buildRC() that 
		builds the horizontal and vertical paths from
		the current position, and buildD() that builds the
		diagonal paths from the current position.

		both methods took the Type of Player as an argument
		to decide whether to construct or deconstruct a path.
		They both also had several helper methods such as
		charUpdate to help update the board values, such as
		'3' to '4' for the player and '4' to '3' for the AI.

		buildRC() handles the edge cases where the Type of
		Player (TOP) is located near the edge of the board.	
		and if the other type of player is blocking their
		path.

		buildD() builds first in the order as follows:
		northeast, southeast, southwest, and then
		northwest. The northeast direction for
		example increases by column but decreases by
		row. If the current position were
		(row: 3 column: 3) then the northeast direction
		would follow (2 4) and (1 5), decreasing by row
		and increasing by column.

		Here is a visual representation with the same
		example.

			  1 2 3 4 5 6
			1 2 2 2 2 2 2
			2 2 2 2 2 2 2 
			3 2 2(P)2 2 2
			4 2 2 2 2 2 2
			5 2 2 2 2 2 2	

		first construction from (3 3) will be (2 4)	

                          1 2 3 4 5 6
                        1 2 2 2 2 2 2
                        2 2 2 2(3)2 2
                        3 2 2(P)2 2 2
                        4 2 2 2 2 2 2
                        5 2 2 2 2 2 2

		Next and final construction will be (1 5)

                          1 2 3 4 5 6
                        1 2 2 2 2(3)2
                        2 2 2 2(3)2 2
                        3 2 2(P)2 2 2
                        4 2 2 2 2 2 2
                        5 2 2 2 2 2 2
