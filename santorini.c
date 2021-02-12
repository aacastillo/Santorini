#include <stdio.h>

// Alan Castillo  CS230 Santorini Game
// initilize global variable
char board[7][7];

//This method is for converting an integer from 0-6 to a char
char convertToChar(int i) {
  if(i == 1) {
     return '1';
  }
  if(i == 2) {
     return '2';
  }
  if(i == 3) {
     return '3';
  }
  if(i == 4) {
     return '4';
  }
  if(i == 5) {
     return '5';
  }
  if(i == 6) {
     return '6';
  }
}

//This method is for displaying the board. 
//It also includes some formatting for the board to make it more readable.
void display(char board[7][7]) {
 
  printf("\n");

  for(int i = 0; i < 7; i++) {

     for (int j = 0; j < 7; j++) {
        // adds extra indent on leftmost column to differentiate reference border from actual board
        if(j == 0) {
           // ignores corner of boarder reference - 0; prints empty string if board[0][0]
           if(i == 0 && j == 0) {
              printf("   ");
           } else {
              printf("%c  ", board[i][j]);
           }
        } else {
           printf("%c ", board[i][j]);
        }
     }
     
     // adds extra new line for first row to differentiate reference border from actual board
     if(i == 0) {
        printf("\n\n");
     } else {
        printf("\n");
     }
  }
  printf("\n");
}

//checks if input is valid and in the span of the board
char playerOutOfSpan(int userInputRow, int userInputColumn) {
   if (userInputRow > 6 || userInputRow < 1 || userInputColumn < 1 || userInputColumn > 6) {
      return 'T';
   }
   return 'F';
}

char AIoutOfSpan(int AIrow, int AIcolumn) {
   if(AIrow > 6 || AIcolumn > 6 || AIrow < 1 || AIcolumn < 1) {
      return 'T';
   } else {
      return 'F';
   }
}


//method for displaying board and prompting message of AI's move
void AIdisplay(int AIrow, int AIcolumn) {
   printf("\nThe AI moved to row: %i column: %i \n", AIrow, AIcolumn);
   display(board);
}

//method checks whether game is over and who won and returns a character value F, A, or P. False, AI, or Player wins
char gameOver() {
   int zeroCount = 0;
   int fourCount = 0;
   //counts the number of zeros and fours in the board. AI or player needs 10 to win
   for(int i = 1; i < 7; i++) {
      for(int j = 1; j < 7; j++) {
         if (board[i][j] == '0') {
            zeroCount++;
         }
         if (board[i][j] == '4') {
            fourCount++;
         }
      }
   }
   if(zeroCount >= 10) {
      return 'A';
   } else if(fourCount >= 10) {
      return 'P';
   } else {
      return 'F';
   }
}

//these methods checks for the validity of the player's and AI's move.
//checks whether the player has selected a spot that was adjacent to their original position
char adjacent(int userInputRow, int userInputColumn, int prevPlayerRow, int prevPlayerColumn) {
  if((userInputRow == (prevPlayerRow + 1) || userInputRow == (prevPlayerRow - 1) || userInputRow == prevPlayerRow)
	 && (userInputColumn == (prevPlayerColumn + 1) || userInputColumn == (prevPlayerColumn - 1) || userInputColumn == prevPlayerColumn)) {
     return 'T';
  }
  return 'F';
}

//Checks whether move is in the span/bounds of the board, whether the move is not adjacent, and whether the space is already occupied
//TOP -type of player, as in the AI 'A' or the player 'P'
char validity(int userInputRow, int userInputColumn, int prevPlayerRow, int prevPlayerColumn) {
   if(playerOutOfSpan(userInputRow, userInputColumn) == 'T') {
      printf("\nIt looks like you picked a spot that was out of bounds. Please choose another move (row column): ");
      return 'F';
   }
   if(adjacent(userInputRow, userInputColumn, prevPlayerRow, prevPlayerColumn) == 'F') {
      printf("\nIt looks like you picked a spot that is not adjacent to where you are currently located. Please try again (row column): ");
      return 'F';
   }
   if(board[userInputRow][userInputColumn] == 'A' || board[userInputRow][userInputColumn] == 'P') {
      printf("\nIt looks like you picked a spot that is already occupied. Please choose again (row column): ");
      return 'F';
   }
   return 'T';
}

//Updates character number based on type of player (TOP)
char charUpdate(char TOP, char number) {
   if(TOP == 'P') {
      if(number == '0') {
	 return '1';
      }
      if(number == '1') {
         return '2';
      }
      if(number == '2') {
         return '3';
      }
      if(number == '3') {
         return '4';
      }
      if(number == '4') {
         return '4';
      }
   }
   if(TOP == 'A') {
      if(number == '0') {
         return '0';
      }
      if(number == '1') {
         return '0';
      }
      if(number == '2') {
         return '1';
      }
      if(number == '3') {
         return '2';
      }
      if(number == '4') {
         return '3';
      }      
   }
}

//buildHV methods "builds" the horizontal and vertical lines and accounts for edges cases where the player is litteraly at the edge of the board and
//also when they are blocked by the other player
void buildHV(char TOP, int row, int column) {
   if(TOP == 'P') {
      //player horizontal
      if(column == 1) {
	 for(int i = 2; i < 7; i++) {
	    char number = board[row][i];
	    if(number == 'A') {
	       break;
	    }
	    board[row][i] = charUpdate('P', number);
	 }
      } else if(column == 6) {
         for(int i = 5; i > 0; i--) {
            char number = board[row][i];
            if(number == 'A') {
               break;
            }
            board[row][i] = charUpdate('P', number);
	 }
      } else {
	 for(int i = column-1; i > 0; i--) {
            char number = board[row][i];
            if(number == 'A') {
               break;
            }
            board[row][i] = charUpdate('P', number);	    
	 }
	 for(int i = column+1; i < 7; i++) {
            char number = board[row][i];
            if(number == 'A') {
               break;
            }
            board[row][i] = charUpdate('P', number);
	 }
      }
      //player vertical
      if(row == 1) {
         for(int i = 2; i < 7; i++) {
            char number = board[i][column];
            if(number == 'A') {
               break;
            }
            board[i][column] = charUpdate('P', number);
         }
      } else if(row == 6) {
         for(int i = 5; i > 0; i--) {
            char number = board[i][column];
            if(number == 'A') {
               break;
            }
            board[i][column] = charUpdate('P', number);
         }
      } else {
         for(int i = row-1; i > 0; i--) {
            char number = board[i][column];
            if(number == 'A') {
               break;
            }
            board[i][column] = charUpdate('P', number);
         }
         for(int i = row+1; i < 7; i++) {
            char number = board[i][column];
            if(number == 'A') {
               break;
            }
            board[i][column] = charUpdate('P', number);
         }
      } 
   }

   if(TOP == 'A') {
      //AI horizontal
      if(column == 1) {
         for(int i = 2; i < 7; i++) {
            char number = board[row][i];
            if(number == 'P') {
               break;
            }
            board[row][i] = charUpdate('A', number);
         }
      } else if(column == 6) {
         for(int i = 5; i > 0; i--) {
            char number = board[row][i];
            if(number == 'P') {
               break;
            }
            board[row][i] = charUpdate('A', number);
	 }
      } else {
         for(int i = column-1; i > 0; i--) {
            char number = board[row][i];
            if(number == 'P') {
               break;
            }
            board[row][i] = charUpdate('A', number);
         }
         for(int i = column+1; i < 7; i++) {
            char number = board[row][i];
            if(number == 'P') {
               break;
            }
            board[row][i] = charUpdate('A', number);
         }   
      }
      //AI vertical
      if(row == 1) {
         for(int i = 2; i < 7; i++) {
            char number = board[i][column];
            if(number == 'P') {
               break;
            }
            board[i][column] = charUpdate('A', number);
         }
      } else if(row == 6) {
         for(int i = 5; i > 0; i--) {
            char number = board[i][column];
            if(number == 'P') {
               break;
            }
            board[i][column] = charUpdate('A', number);
         }
      } else {
         for(int i = row-1; i > 0; i--) {
            char number = board[i][column];
            if(number == 'P') {   
               break;
            }
            board[i][column] = charUpdate('A', number);
         }
         for(int i = row+1; i < 7; i++) {
            char number = board[i][column];
            if(number == 'P') {
               break;
            }    
            board[i][column] = charUpdate('A', number);
         }
      }           
   }
}

//buildD builds the lines diagnally. Starting in the northeast, southeast, southwest, and northwest respectively. Accounts for getting blocked by
//another player
void buildD(char TOP, int row, int column) {
   if(TOP == 'P') {
      //Northeast
      int nerow = row;
      int necolumn = column;
      while(nerow != 1 && necolumn != 6) {
         nerow--;
	 necolumn++;
	 char number = board[nerow][necolumn];
	 if(number == 'A') {
	    break;
	 }
         board[nerow][necolumn] = charUpdate('P', number);
      }
     
      //Southeast
      int serow = row;
      int secolumn = column;
      while(serow != 6 && secolumn != 6) {
         serow++;
         secolumn++;
         char number = board[serow][secolumn];
         if(number == 'A') {
            break;
         }
         board[serow][secolumn] = charUpdate('P', number);
      }     
    
      //Southwest
      int swrow = row;
      int swcolumn = column;
      while(swrow != 6 && swcolumn != 1) {
         swrow++;
         swcolumn--;
         char number = board[swrow][swcolumn];
         if(number == 'A') {
            break;
         }
         board[swrow][swcolumn] = charUpdate('P', number);
      }
 
      //Northwest
      int nwrow = row;
      int nwcolumn = column;
      while(nwrow != 1 && nwcolumn != 1) {
         nwrow--;
         nwcolumn--;
         char number = board[nwrow][nwcolumn];
         if(number == 'A') {
            break;
         }
         board[nwrow][nwcolumn] = charUpdate('P', number);
      }
   }
   //AI
   if(TOP == 'A') {
      //Northeast
      int nerow = row;
      int necolumn = column;
      while(nerow != 1 && necolumn != 6) {
         nerow--;
         necolumn++;
         char number = board[nerow][necolumn];
         if(number == 'P') {
            break;
         }
         board[nerow][necolumn] = charUpdate('A', number);
      }

      //Southeast
      int serow = row;
      int secolumn = column;
      while(serow != 6 && secolumn != 6) {
         serow++;
         secolumn++;
         char number = board[serow][secolumn];
         if(number == 'P') {
            break;
         }
         board[serow][secolumn] = charUpdate('A', number);
      }
      //Southwest
      int swrow = row;
      int swcolumn = column;
      while(swrow != 6 && swcolumn != 1) {
         swrow++;
         swcolumn--;
         char number = board[swrow][swcolumn];
         if(number == 'P') {
            break;
         }
         board[swrow][swcolumn] = charUpdate('A', number);
      }
      //Northwest
      int nwrow = row;
      int nwcolumn = column;
      while(nwrow != 1 && nwcolumn != 1) {
         nwrow--;
         nwcolumn--;
         char number = board[nwrow][nwcolumn];
         if(number == 'P') {
            break;
         }
         board[nwrow][nwcolumn] = charUpdate('A', number);
      }
   }
}

//----------------------------------------------------------------METHODS DONE--------------------------------------------------------------------

void main()
{
   //THE SET UP
   int userInputRow;
   int userInputColumn;
   int AIrow;
   int AIcolumn;

//these variables are to store the previous positions of the player for reference to see if there next move is adjacent
   int prevPlayerRow;
   int prevPlayerColumn;
   int prevAIrow;
   int prevAIcolumn;   
   //this sets the inside of the matrix board all equal to two
   for (int i = 1; i < 7; i++)
   {
      for (int j = 1; j < 7; j++)
      {
         board[i][j] = '2';
      }
   }

   //now we set up the reference borders for the player and display the board
     //the column reference
   for(int i = 1; i < 7; i++) 
   {
      board[0][i] = convertToChar(i);
   }
     //the row reference
   for(int i = 1; i <7; i++)
   {
      board[i][0] = convertToChar(i);
   }
   display(board);
   
   //prompts player and takes player input to select a starting position and makes sure its in bounds of board.
   printf("Welcome to Santorini-230 ver.\nPlease pick your starting position with denotation (""row"" ""column""): ");
   scanf("%i %i", &userInputRow, &userInputColumn);

   while(playerOutOfSpan(userInputRow, userInputColumn) == 'T') {
      printf("please enter a starting position within the span of the board: ");
      scanf("%i %i", &userInputRow, &userInputColumn);
   }
   
   //places player on the board and displays board
   board[userInputRow][userInputColumn] = 'P';
   display(board);
   
   //AI Placement, makes sure AI is adjacent to the player and the  in span of board
   AIrow = userInputRow;
   AIcolumn = userInputColumn + 1;
   if (AIoutOfSpan(AIrow, AIcolumn) == 'T') {
      AIcolumn -= 2;
   }
   //Places AI and displays board
   board[AIrow][AIcolumn] = 'A';
   AIdisplay(AIrow, AIcolumn);
   //------------------------------------------------------------------SET UP COMPLETE-----------------------------------------------------------------   
   //this variable stores the value of the position that the player is moving into, so that when they move again, we can return that value.
   //It is equal to nine because it can never be reached in the game and will be used as the starting point of the loopp
   char pogPosition = '9';
   char aogPosition = '9';
   // this while loop is the meat of the game, The player and AI will take turns until the game is over
   while(gameOver() == 'F') {
      prevPlayerRow = userInputRow;
      prevPlayerColumn = userInputColumn;

      printf("Its your turn! where would like to move? Please pick a space ajacent to your player (row column): ");
      scanf("%i %i", &userInputRow, &userInputColumn);
     
      while (validity(userInputRow, userInputColumn, prevPlayerRow, prevPlayerColumn) == 'F') {
	 scanf("%i %i", &userInputRow, &userInputColumn);
      }
      
      //stores original position value before moving to new location
      if(pogPosition == '9') {
         board[prevPlayerRow][prevPlayerColumn] = '2';
      } else {
	 board[prevPlayerRow][prevPlayerColumn] = pogPosition;
      }
      pogPosition = board[userInputRow][userInputColumn];
      board[userInputRow][userInputColumn] = 'P';

      //updates matrix (de)constructs
      buildHV('P', userInputRow, userInputColumn);
      buildD('P', userInputRow, userInputColumn);

      display(board);

      if(gameOver() == 'P') {
	 break;
      }

      //AIs turn
      prevAIrow = AIrow;
      prevAIcolumn = AIcolumn;   
 
      //this will try and keep the AI near the center of the board to deconstruct as much as possible on the board. accounts for player blocking.
      if(AIrow >= 3) {
	 if(board[AIrow-1][AIcolumn] != 'P') {
	    AIrow--;
	 }
      } else {
         if(board[AIrow+1][AIcolumn] != 'P') {
            AIrow++;
         }
      }

      if(AIcolumn >= 3) {
         if(board[AIrow][AIcolumn-1] != 'P') {
            AIcolumn--;
         }
      } else {
         if(board[AIrow][AIcolumn+1] != 'P') {
            AIcolumn++;
         }
      }

      //stores AI's original position
      if(aogPosition == '9') {
         board[prevAIrow][prevAIcolumn] = '2';
      } else {
	 board[prevAIrow][prevAIcolumn] = aogPosition;
      }
      aogPosition = board[AIrow][AIcolumn];
      board[AIrow][AIcolumn] = 'A';

      //updates matrix (de)constructs and displays
      buildHV('A', AIrow, AIcolumn);
      buildD('A', AIrow, AIcolumn);

      AIdisplay(AIrow, AIcolumn);

      if(gameOver() == 'A') {
	 break;
      }
   }

   //--------------------------------------------------------------MEAT OF GAME COMPLETE--------------------------------------------------------------
   //This determines the winner of the game
   if(gameOver() == 'P') {
      printf("\nCONGRATULATIONS! You have won the game by getting 10 building levels to 4 and now this project works!\n");
   } else if (gameOver() == 'A') {
      printf("\nGame Over. The AI has won by deconstructing 10 building levels to 0.\nBetter luck next time!\n");
   } else {
      printf("\n Oops! looks like theres a bug :(\n");
   }
}
