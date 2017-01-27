/********************************************\
 *            otHello AI System             *
 *                                          *
 * Author : bigelephant29                   *
 * https://github.com/bigelephant29/otHello *
 *                                          *
 *       Share Under LGPL-3.0 License       *
\********************************************/

#include <vector>
#include <functional>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;

enum Color { BLACK, WHITE, EMPTY, INVALID };

class Board {
protected:
  int now_color;
  int grid[8][8];
  pair<int,int> adj[8] = {
    pair<int,int>(-1,-1),
    pair<int,int>(-1,+0),
    pair<int,int>(-1,+1),
    pair<int,int>(+0,-1),
    pair<int,int>(+0,+1),
    pair<int,int>(+1,-1),
    pair<int,int>(+1,+0),
    pair<int,int>(+1,+1),
  };
  bool inBoard(int,int);
public:
  Board();                                  // Default Constructor
  Board(const Board&);                      // Copy Constructor
  Color getPlayerColor();                   // Return the color of the current player
  pair<int,int> getCount();                 // Get the number of chess of the two players
  int getScore();                           // Get the score of the current player
  vector< pair<int,int> > getValidMoves();  // Get the list of valid moves of the current player
  bool checkValidMove(int,int);             // Check if a move is valid
  bool checkValidMove(pair<int,int>);
  Color getColor(int,int);                  // Get the color of a specific location
  Color getColor(pair<int,int>);
  void getBoard(int[8][8]);                 // Get the current board with a 8 x 8 array
  bool takeMove(int,int);                   // Update the board with a new move
  bool takeMove(pair<int,int>);
};
