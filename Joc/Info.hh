//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

#ifndef Info_hh
#define Info_hh


#include "Settings.hh"
#include "State.hh"


/**
 * Contains a class to store most of the information of the game.
 */


/**
 * Stores all the information of the game,
 * except the vector of names and the random generator of the board.
 */
class Info : public Settings, public State {

  friend class Game;
  friend class SecGame;

public:

  /**
   * Returns the cell defined by the char c.
   */
  inline static Cell char2Cell (char c) {
    Cell cell; // (Soil, None, -1) by default
    switch (c) {
      case '.':
        break; // empty cell
      case 'W':
        cell.type = Water;
        break;
      case 'B':
        cell.bonus = Bread;
        break;
      case 'S':
        cell.bonus = Seed;
        break;
      case 'L':
        cell.bonus = Leaf;
        break;
      default:
        _my_assert(false, string(1, c) + " in grid definition.");
    }
    return cell;
  }

  /**
   * Reads the grid of the board.
   * Should fill the same data structures as a board generator.
   */
  void read_grid (istream& is) {

    string l;
    is >> l; // Read 1st line of column labels.
    is >> l; // Read 2nd line of column labels.
    grid = vector< vector<Cell> >(board_rows(), vector<Cell>(board_cols()));
    for (int i = 0; i < board_rows(); ++i) {
      string s;
      is >> l >> s;
      // Read row label in l and row in s.
      _my_assert((int)s.size() == board_cols(),
                 "The read map has a line with incorrect lenght.");
      for (int j = 0; j < board_cols(); ++j)
        grid[i][j] = char2Cell(s[j]);
    }

    is >> l;
    _my_assert(l == "rivers", "Expected 'rivers'.");
    int n_rivers;
    is >> n_rivers;
    rivers = vector<vector<Pos>>(n_rivers);
    for (auto& r : rivers) {
      int sz;
      is >> sz;
      r = vector<Pos>(sz);
      for (auto& p : r) 
        is >> p.i >> p.j;
    }
    
    vector<string> bonus = {"bread", "seed", "leaf"};
    player2bonus2tl = vector< vector<Pos> >(num_players(), vector<Pos>(bonus.size()));
    for (int b = 0; b < int(bonus.size()); ++b) {
      is >> l;
      _my_assert(l == bonus[b], "Expected '" + bonus[b] + "'.");
      for (int pl = 0; pl < num_players(); ++pl) {
        Pos& p = player2bonus2tl[pl][b];
        is >> p.i >> p.j;
      }
    }
  }

  /**
   * Checks invariants are preserved.
   */
  bool ok() const;
};


#endif
