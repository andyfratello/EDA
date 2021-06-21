//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

#ifndef Board_hh
#define Board_hh


#include "Info.hh"
#include "Action.hh"
#include "Random.hh"


/**
 * Contains the Board class, with all the game information,
 * plus the names of the players and a random generator.
 */


/**
 * Manages a random generator and the information of the board.
 */
class Board : public Info, public Random_generator {

  friend class Game;
  friend class SecGame;

  vector<string> names;
  int            fresh_id;

  struct Egg {
    int   player;
    Pos      pos;
    AntType type;
  };

  const vector<string> nutrients = { "carbohydrate", "protein", "lipid" };
  
  /**
   * Reads the generator method, and generates or reads the grid.
   */
  void read_generator_and_grid (istream& is) {
    string generator;
    is >> generator;
    if (generator == "FIXED") read_grid(is);
    else {
      vector<int> param;
      int x;
      while (is >> x) param.push_back(x);
      if (generator == "GENERATOR1") generator1(param);
      else _my_assert(false, "Unknown grid generator.");
    }
  }

  /**
   * Prints some information of the ant.
   */
  inline static void print_ant (Ant a, ostream& os) {
    os << AntType2char(a.type)     << '\t'
       << a.id                     << '\t'
       << a.player                 << '\t'
       << a.pos.i                  << '\t'
       << a.pos.j                  << '\t'        
       << a.reserve[0]             << '\t'
       << a.reserve[1]             << '\t'
       << a.reserve[2]             << '\t'  
       << BonusType2char(a.bonus)  << '\t'
       << a.life                   << '\t'      
       << endl;
  }

  void create_initial_ants(int pl);
  void create_new_ant(int pl, Pos p, AntType t);
  
  Pos rotate(Pos p, int pl) const;


  /**
   * Tries to apply a move. Returns true if it could.
   */
  bool execute(const Command& m, set<int>& killed, vector<Egg>& eggs);

  void kill(int id, set<int>& killed);

  void transform_into_queen(int id);

  void regenerate_bonus(Pos tl, BonusType b);

  /////////////////////// BEGIN BOARD GENERATION ///////////////////////

  static const char Undef;
  static const char River;

  // Min and max number of cells attempted when placing a river.
  static const int MIN_CELLS_RIVERS  =  5;
  static const int MAX_CELLS_RIVERS  = 15;
  
  // Min and max number of *attempts* to place rivers.
  static const int MIN_ATTEMPTS_RIVERS  = 10;
  static const int MAX_ATTEMPTS_RIVERS  = 20;
  
  static const int MIN_DISTANCE_OF_RIVERS = 2;

  // Max number of attempts before giving up placing an object.
  static const int MAX_ATTEMPTS = 100;

  
  /**
   * Generates a board.
   */
  void generator1 (const vector<int>& param);

  // S, E, N, W
  static const vector<int> DIRI4;
  static const vector<int> DIRJ4;

  // SW, S, SE, E, NE, N, NW, W
  static const vector<int> DIRI8;
  static const vector<int> DIRJ8;
  
  vector<vector<char>> m;

  // Returns the L^p distance between a and b.
  static double distance(const pair<double,double>& a, const pair<double,double>& b, double p = 2) {
    double first  = pow(abs(a.first  - b.first),  p);
    double second = pow(abs(a.second - b.second), p);
    return pow(first + second, 1/p);
  }
  
  struct My_Validator {
    Board& b;
    int i0, j0;

    // True if (i, j) is closer to (i0, j0) than (ii, jj)
    bool operator()(int i, int j, int ii, int jj) {
      double  d = distance({i0, j0}, { i,  j});
      double dd = distance({i0, j0}, {ii, jj});
      return d < dd;
    }
  };
  
  // Returns whether there is a cell in the box of radius d
  // centered at (i, j) that contains character c.
  bool neighbour_one_of(const vector<vector<char>>& t, int i, int j, int d, char c) {
    for (int ii = max(0, i-d); ii <= min(board_rows()-1, i+d); ++ii)
      for (int jj = max(0, j-d); jj <= min(board_cols()-1, j+d); ++jj)
        if (t[ii][jj] == c)
          return true;
    return false;
  }

  // Returns whether river r is too close to another existing river.
  bool river_valid(const vector<Pos>& r) {
    const int D = MIN_DISTANCE_OF_RIVERS;
    for (auto x : r)
      if (neighbour_one_of(m, x.i, x.j, D, River))
        return false;
    return true;
  }

  // Returns a vector of positions representing a curve starting at (i0, j0).
  template <class Validator>
  vector<Pos> curve_from(int i0, int j0, Validator valid, bool allow_diags = true) {

    const vector<int>& diri = allow_diags ? DIRI8 : DIRI4;
    const vector<int>& dirj = allow_diags ? DIRJ8 : DIRJ4;
    const int D = diri.size();

    vector<Pos> curve;
    vector<vector<bool>> mkd(board_rows(), vector<bool>(board_cols(), false));
    int i = i0;
    int j = j0;
    int k = random(0, D-1);
    int n_steps = random(MIN_CELLS_RIVERS, MAX_CELLS_RIVERS);
    for (int steps = 0; steps < n_steps; ++steps) {
      curve.push_back({i, j});
      mkd[i][j] = true;
      int s, ii, jj, kk;
      for (s = -2; s <= 1; ++s) {
        if (s < -1) kk = k + random(-1, 1); // First try random
        else        kk = k + s;             // then try exhaustively.
        // -1 <= kk - k <= 1 to get a smooth shape.
        kk = (D + kk) % D;
        _my_assert(0 <= kk and kk < D, "In curve generation.");
        ii = i + diri[kk];
        jj = j + dirj[kk];
        if (pos_ok(ii, jj) and not mkd[ii][jj] and valid(i, j, ii, jj)) break;
      }
      if (s <= 1) { // Found a new point for the curve.
        i = ii;
        j = jj;
        k = kk;
      }
      else break; // Could not continue the curve, so stop.
    }
    return curve;
  }
  
  // Places one river starting at position (i0, j0).
  void place_river(int i0, int j0) {
    bool found = false;
    vector<Pos> r;
    for (int k = 0; k < MAX_ATTEMPTS and not found; ++k) {
      r = curve_from(i0, j0, My_Validator{*this, i0, j0});
      found = river_valid(r);
    }
    if (found) {
      rivers.push_back(r);
      for (auto x : r)            
        m[x.i][x.j] = River;
    }
  }
  
  void place_rivers() {
    const int D = MIN_DISTANCE_OF_RIVERS;
    int n_rivers = random(MIN_ATTEMPTS_RIVERS, MAX_ATTEMPTS_RIVERS);
    for (int k = 0; k < n_rivers; ++k) {
      int i = random(0, board_rows()-1);
      int j = random(0, board_cols()-1);
      if (not neighbour_one_of(m, i, j, D, River))
        place_river(i, j);
    }
  }

  // Mark all cells reachable from (i, j).
  void traversal(int i, int j, vector<vector<bool>>& mkd) {
    if (not mkd[i][j]) {
      mkd[i][j] = true;
      for (int k = 0; k < 4; ++k) {
        int ii = i + DIRI4[k];
        int jj = j + DIRJ4[k];
        if (pos_ok(ii, jj) and m[ii][jj] != River)
          traversal(ii, jj, mkd);
      }
    }
  }
  
  // Returns all cells without river can be reached.
  bool is_connected() {
    vector<vector<bool>> mkd(board_rows(), vector<bool>(board_cols(), false));

    bool found = false;
    int i0, j0;
    i0 = j0 = 0;
    for (int i = 0; not found and i < board_rows(); ++i)
      for (int j = 0; not found and j < board_cols(); ++j)
        if (m[i][j] != River) {
          i0 = i;
          j0 = j;
          found = true;
        }
    if (found) {
      traversal(i0, j0, mkd);

      for (int i = 0; i < board_rows(); ++i)
        for (int j = 0; j < board_cols(); ++j)
          if (m[i][j] != River and not mkd[i][j])
            return false;
    }

    return true;
  }

  /////////////////////// END BOARD GENERATION ///////////////////////  
  
public:

  /**
   * Construct a board by reading information from a stream.
   */
  Board (istream& is, int seed);

  /**
   * Returns the name of a player.
   */
  inline string name (int pl) const {
    _my_assert(player_ok(pl), "Player is not ok.");
    return names[pl];
  }

  /**
   * Prints the board settings to a stream.
   */
  void print_settings (ostream& os) const;

  /**
   * Prints the name players to a stream.
   */
  void print_names (ostream& os) const;

  /**
   * Prints the state of the board to a stream.
   */
  void print_state (ostream& os) const;

  /**
   * Prints the results and the names of the winning players.
   */
  void print_results () const;

  /**
   * Computes the next board aplying the given actions to the current board.
   * It also prints to os the actual actions performed.
   */
  void next (const vector<Action>& act, ostream& os);

};

#endif
