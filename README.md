# General
MasterMind game implementation in C Language as an exercise of an exam course to learn how to structure a (simple) project.

# Game Rules
There are two players, the encoder and the decoder. 
The encoder composes a code made up of 3 or 4 digits.
The decoder has a certain number of digits from 0 to 9 to guess the code.
The encoder, when the decoder completed his attempts, give him some hints:

- The number of right digits in the right place.
- The number of right digits in the wrong place

The encoder doesn't communicate which digits are right, only how much is right.
If the decoder can guess the code in a predetermined number of attempts, then he is the winner, otherwise, the winner is the encoder.

# How to Play
Start:
	The player inserts 1 to play. 
	Then the game asks him if he wants to load the saved game or play a new game.

Game Phase:
	The user can come back to the menu without saving, saving the game or attempting to guess the code.
	The user inserts a single digit per input. After every try, the game returns the player the result of his attempts 
	To know how many attempts the user has, he can rely on the attempt not filled on the game board

Difficulty Levels:

Beginner:                                                        
	- Code Length: 3 digits                       
	- Number of attempts: 20                                   
	- Repeated Digits: no                                                
	- Possible Digits: 0, 1, 2, 3, 4, 5             
	
Intermediate:   
	- Code Length: 4 digits                       
	- Number of attempts: 10                                   
	- Repeated Digits: no                                                
	- Possible Digits: 0, 1, 2, 3, 4, 5, 6, 7   

Advanced:                                      
	- Code Length: 4 digits                       
	- Number of attempts: 9                                  
	- Repeated Digits: no                                                
	- Possible Digits: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9    

# Run the game
First of all run
    
	git clone https://github.com/mattiacurri/mastermind-C

Then you need an IDE that supports MinGW compiler. I used Eclipse for this project
	(https://www.eclipse.org/downloads/) because it makes automatically the MakeFile configuration to link the resources.
In "saveGame.h", "rules.h", "top10.h" you need to insert respectively the path of "rules.txt", "howToPlay.txt", "match.dat", "bastop10.dat", "inttop10.dat", "advtop10.dat" according to where you are going to save this file, note that the game generates "match.dat" when you save, in savedMatch folder.
