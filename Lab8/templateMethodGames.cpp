// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};


class Dice: public Game {

public:

	void initializeGame() {
		 playersCount_ = numPlayers_; // initalize players
	}

	void makeMove(int player) {

		// three rounds
		if(movesCount_ < maxMoves_) {

			//if Computer
			if(player == 0) {
				int arr[5];
				int sumComputer = 0;
			

				//if player is passing on turn
				if(holdComputer == 1) {
					cout << "Computer Rolled: passed, Computer's High Score = " << hScoreComputer << endl;
				} else {

					// 5 rolls per turn
					for(int i =0; i<rollsPerTurn; i++) {
						int roll = (rand() % 6 + 1);
						arr[i] = roll;
						sumComputer += roll;
					}
					// updates high scire
					if(sumComputer > hScoreComputer) {hScoreComputer = sumComputer;};
					// print turn results
					cout << "Computer Rolled: ";
					for(int i = 0; i<5; i++) {
						cout << arr[i] << " ";
					}
					cout << " = " << sumComputer <<  ", Computer's Highest Score = " << hScoreComputer << endl;
				}
			

				// Will computer hold?
				holdComputer = rand() % 2;
			} else {
				int arr1[5];
                                int sumPlayer = 0;

				//if player is passing on turn
                                if(holdPlayer == 1) {
                                        cout << "You Rolled: passed, Your High Score = " << hScorePlayer << endl;
                                } else {

				// 5 rolls per turn
                                for(int i =0; i<rollsPerTurn; i++) {
                                        int roll1 = (rand() % 6 + 1);
                                        arr1[i] = roll1;
                                        sumPlayer += roll1;
                                }
                                // updates high score
                                if(sumPlayer > hScorePlayer) {hScorePlayer = sumPlayer;};
				// print turn results
                                cout << "You Rolled: ";
                                for(int i = 0; i<5; i++) {
                                        cout << arr1[i] << " ";
                                }
                                cout << " = " << sumPlayer << ", Your Highest Score = " << hScorePlayer << endl;


				}


				// ask keep or pass on first two rounds
				if(movesCount_ < 2) {
					cout << "Roll Again? [y/n]" << endl;
					char c;
					std::cin >> c;
					// Determine if player wants to pass or try again
					if( c == 'y') {
						holdPlayer = 0;
					} else {
						holdPlayer = 1;
					}
				}

			}



		 } else {
			if(hScorePlayer > hScoreComputer) {
				playerWon_ = 1;
			} else {
				playerWon_ = 0;
			}
		}

		 // If both players held in the last round, end game
                if(holdPlayer == 1 && holdComputer == 1) {
                        if(hScorePlayer > hScoreComputer) {
                                playerWon_ = 1;
                        } else {
                                playerWon_ = 0;
                        }
                }


	}

	void printWinner() {
		if(playerWon_ == 0) {
			cout << "you lose" << endl;
		} else {
			cout << "you win!" << endl;
		}
		
	}


private:
	static const int numPlayers_ = 2;
	static const int maxMoves_ = 3;
	static const int rollsPerTurn = 5;
	int hScoreComputer = 0;
	int hScorePlayer = 0;
	int holdComputer = 0;
        int holdPlayer = 0;

};











// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};




int main() {
   srand(time(nullptr));
	
   Game* gp = nullptr;

   gp = new Dice;
   gp->playGame();
   delete gp;


/*
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 8 times
   for (int i = 0; i < 8; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   }

*/

}
