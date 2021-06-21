#ifndef State_hh
#define State_hh


#include "Structs.hh"

/**
 * Contains a class to store the current state of a game.
 */


/**
 * Stores the game state.
 */
class State {

public:

  /**
   * Returns the current round.
   */
  int round () const;

  /**
   * Returns a copy of the cell at (i, j).
   */
  Cell cell (int i, int j) const;

  /**
   * Returns a copy of the cell at p.
   */
  Cell cell (Pos p) const;

  /**
   * Returns the ant with identifier id.
   */
  Ant ant (int id) const;

  /**
   * Returns the ids of the soldiers of a player.
   */
  vector<int> soldiers(int pl) const;

  /**
   * Returns the ids of the workers of a player.
   */
  vector<int> workers(int pl) const;

  /**
   * Returns the ids of the queens of a player.
   */
  vector<int> queens(int pl) const;

  
  /**
   * Returns the current score of a player.
   */
  int score (int pl) const;

  /**
   * Returns the percentage of cpu time used so far, in the
   * range [0.0 - 1.0] or a value lesser than 0 if the player is dead.
   */
   // NOTE: only returns a sensible value in server executions.
   // In local executions the returned value is meaningless.
  double status (int pl) const;


  //////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

private:

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  Pos top_left_corner(int pl, BonusType b) const;
  void forget();
  
  vector< vector<Cell> >   grid;
  vector< vector< Pos > >  player2bonus2tl;
  vector< vector< Pos > >  rivers;
  
  vector<int>              scr;
  vector<double>           stats; // -1 -> dead, 0..1 -> % of cpu time limit
  int                      rnd;

  map<int, Ant>            ants;
  vector< set<int> >       player2soldiers;
  vector< set<int> >       player2workers;
  vector< set<int> >       player2queens;
  
  /**
   * Returns whether id is a valid ant identifier.
   */
  inline bool ant_ok (int id) const {
    return ants.count(id);
  }
};

inline int State::round () const {
  return rnd;
}

inline Cell State::cell (int i, int j) const {
  if (i >= 0 and i < (int)grid.size() and j >= 0 and j < (int)grid[i].size())
    return grid[i][j];
  else {
    cerr << "warning: cell requested for position " << Pos(i, j) << endl;
    return Cell();
  }
}

inline Cell State::cell (Pos p) const {
  return cell(p.i, p.j);
}

inline Ant State::ant (int id) const {
  auto it = ants.find(id);
  if (it != ants.end()) {
    return it->second;
  }
  else {
    cerr << "warning: ant requested for identifier " << id << endl;
    return Ant();
  }
}

inline vector<int> State::soldiers(int pl) const {
  if (pl >= 0 and pl < (int) player2soldiers.size())
    return vector<int>(player2soldiers[pl].begin(), player2soldiers[pl].end());
  else {
    cerr << "warning: soldiers requested for player " << pl << endl;
    return vector<int>();
  }
}


inline vector<int> State::workers(int pl) const {
  if (pl >= 0 and pl < (int) player2workers.size())
    return vector<int>(player2workers[pl].begin(), player2workers[pl].end());
  else {
    cerr << "warning: workers requested for player " << pl << endl;
    return vector<int>();
  }
}


inline vector<int> State::queens(int pl) const {
  if (pl >= 0 and pl < (int) player2queens.size())
    return vector<int>(player2queens[pl].begin(), player2queens[pl].end());
  else {
    cerr << "warning: queens requested for player " << pl << endl;
    return vector<int>();
  }
}


inline int State::score (int pl) const {
  if (pl >= 0 and pl < (int) scr.size())
    return scr[pl];
  else {
    cerr << "warning: score requested for player " << pl << endl;
    return -1;
  }
}


inline double State::status (int pl) const {
  if (pl >= 0 and pl < (int)stats.size())
    return stats[pl];
  else {
    cerr << "warning: status requested for player " << pl << endl;
    return -2;
  }
}


inline Pos State::top_left_corner(int pl, BonusType f) const {
  if (pl >= 0 and pl < (int)player2bonus2tl.size()) {
    if (f >= 0 and f < (int)player2bonus2tl[pl].size()) {
      return player2bonus2tl[pl][f];
    }
  }
  cerr << "warning: invalid request" << endl;
  return Pos();
} 


inline void State::forget() {
  player2bonus2tl.clear();
}

#endif
