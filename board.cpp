/********************************************\
 *            otHello AI System             *
 *                                          *
 * Author : bigelephant29                   *
 * https://github.com/bigelephant29/otHello *
 *                                          *
 *       Share Under LGPL-3.0 License       *
\********************************************/

#include "Board.h"

Board::Board() :
  now_color(1),
  grid {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,2,1,0,0,0},
    {0,0,0,1,2,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
  } {}

bool Board::inBoard(int x, int y) {
  return 0 <= x && x <= 7 &&
         0 <= y && y <= 7;
}

Board::Board(const Board &A) {
  for(int i = 0 ; i < 8 ; i++) {
    for(int j = 0 ; j < 8 ; j++) {
      grid[i][j] = A.grid[i][j];
    }
  }
  now_color = A.now_color;
}

Color Board::getPlayerColor() {
  if(now_color == 1) {
    return BLACK;
  } else if(now_color == 2){
    return WHITE;
  }
  return EMPTY;
} 

pair<int,int> Board::getCount() {
  int my_point = 0, op_point = 0;
  for(int i = 0 ; i < 8 ; i++) {
    for(int j = 0 ; j < 8 ; j++) {
      if(grid[i][j] == now_color) {
        my_point++;
      } else if(grid[i][j] == 3 - now_color) {
        op_point++;
      }
    }
  }
  return make_pair(my_point, op_point);
}

int Board::getScore() {
  pair<int,int> now_count = getCount();
  return now_count.first - now_count.second;
}

vector< pair<int,int> > Board::getValidMoves() {
  vector< pair<int,int> > return_value;
  for(int i = 0 ; i < 8 ; i++) {
    for(int j = 0 ; j < 8 ; j++) {
      if(grid[i][j] == 0) {
        for(int dir = 0 ; dir < 8 ; dir++) {
          int nxti = i + adj[dir].first;
          int nxtj = j + adj[dir].second;
          if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == 3 - now_color) {
            // if adj grid contains the opponent's color
            do {
              nxti += adj[dir].first;
              nxtj += adj[dir].second;
            } while (inBoard(nxti, nxtj) &&
                     grid[nxti][nxtj] == 3 - now_color);
            if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == now_color) {
              return_value.push_back(make_pair(nxti, nxtj));
            }
          }
        }
      }
    }
  }
  return return_value;
}

bool Board::checkValidMove(int x, int y) {
  if(x == -1 && y == -1) {
    vector< pair<int,int> > valid_moves = getValidMoves();
    if(valid_moves.size() == 0) return true;
    else return false;
  }
  if(!inBoard(x,y)) return false;
  if(grid[x][y] != 0) return false;
  for(int dir = 0 ; dir < 8 ; dir++) {
    int nxti = x + adj[dir].first;
    int nxtj = y + adj[dir].second;
    if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == 3 - now_color) {
      do {
        nxti += adj[dir].first;
        nxtj += adj[dir].second;
      } while (inBoard(nxti, nxtj) &&
               grid[nxti][nxtj] == 3 - now_color);
      if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == now_color) {
        return true;
      }
    }
  }
  return false;
}

bool Board::checkValidMove(pair<int,int> move) {
  return checkValidMove(move.first, move.second);
}

Color Board::getColor(int x, int y) {
  if(!inBoard(x,y)) return INVALID;
  switch(grid[x][y]) {
    case 0:
      return EMPTY;
    break;
    case 1:
      return BLACK;
    break;
    case 2:
      return WHITE;
    break;
  }
  return EMPTY;
}

Color Board::getColor(pair<int,int> pos) {
  return getColor(pos.first, pos.second);
}

void Board::getBoard(int T[8][8]) {
  for(int i = 0 ; i < 8 ; i++) {
    for(int j = 0 ; j < 8 ; j++) {
      T[i][j] = grid[i][j];
    }
  }
}

bool Board::takeMove(int x, int y) {
  if(!inBoard(x,y) && (x != -1 || y != -1)) return false;
  if((x != -1 && y != -1) && grid[x][y] != 0) return false;
  vector< pair<int,int> > valid_moves = getValidMoves();
  if(x == -1 && y == -1) {
    if(valid_moves.size() == 0) {
      now_color = 3 - now_color;
      return true;
    } else {
      return false;
    }
  }
  bool is_valid_move = false; 
  for(int dir = 0 ; dir < 8 ; dir++) {
    int nxti = x + adj[dir].first;
    int nxtj = y + adj[dir].second;
    if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == 3 - now_color) {
      do {
        nxti += adj[dir].first;
        nxtj += adj[dir].second;
      } while(inBoard(nxti, nxtj) && grid[nxti][nxtj] == 3 - now_color);
      if(inBoard(nxti, nxtj) && grid[nxti][nxtj] == now_color) {
        is_valid_move = true;
        for(int nx = x + adj[dir].first, ny = y + adj[dir].second ;
            nx != nxti && ny != nxtj ;
            nx += adj[dir].first, ny += adj[dir].second) {
          grid[nx][ny] = now_color;
        }
      }
    }
  }
  if(is_valid_move) {
    now_color = 3 - now_color;
  }
  return is_valid_move;
}

bool Board::takeMove(pair<int,int> move) {
  return takeMove(move.first, move.second);
}
