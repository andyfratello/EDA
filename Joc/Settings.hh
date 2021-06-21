#ifndef Settings_hh
#define Settings_hh


#include "Structs.hh"


/**
 * Contains a class to store all the game settings that do not change
 * during a game, except the names of the players.
 */

/**
 * Stores most of the game settings.
 */
class Settings {

public:

  /**
   * Returns a string with the game name and version.
   */
  static string version ();

  /**
   * Returns the number of players in the game.
   */
  int num_players () const;

  /**
   * Returns the number of rounds a match lasts.
   */
  int num_rounds () const;

  /**
   * Returns the number of rows of the board.
   */
  int board_rows () const;

  /**
   * Returns the number of columns of the board.
   */
  int board_cols () const;

  /**
   * Queens are allowed to move every queen_period() rounds, starting from round 0.
   */
  int queen_period () const;

  /**
   * Returns the units of carbohydrates needed for an egg of a soldier.
   */
  int soldier_carbo () const;

  /**
   * Returns the units of proteins needed for an egg of a soldier.
   */
  int soldier_prote () const;

  /**
   * Returns the units of lipids needed for an egg of a soldier.
   */
  int soldier_lipid () const;

  /**
   * Returns the units of carbohydrates needed for an egg of a worker.
   */
  int worker_carbo () const;

  /**
   * Returns the units of proteins needed for an egg of a worker.
   */
  int worker_prote () const;

  /**
   * Returns the units of lipids needed for an egg of a worker.
   */
  int worker_lipid () const;

  /**
   * Returns the units of nutrient of type n needed for an egg of type a.
   */
  int needed (AntType a, NutrientType n) const;


  /**
   * Returns the units of carbohydrates contained in a bonus of bread.
   */
  int bread_carbo () const;

  /**
   * Returns the units of proteins contained in a bonus of bread.
   */
  int bread_prote () const;

  /**
   * Returns the units of lipids contained in a bonus of bread.
   */
  int bread_lipid () const;

  /**
   * Returns the units of carbohydrates contained in a bonus of seed.
   */
  int seed_carbo () const;

  /**
   * Returns the units of proteins contained in a bonus of seed.
   */
  int seed_prote () const;

  /**
   * Returns the units of lipids contained in a bonus of seed.
   */
  int seed_lipid () const;

  /**
   * Returns the units of carbohydrates contained in a bonus of leaf.
   */
  int leaf_carbo () const;

  /**
   * Returns the units of proteins contained in a bonus of leaf.
   */
  int leaf_prote () const;

  /**
   * Returns the units of lipids contained in a bonus of leaf.
   */
  int leaf_lipid () const;

  /**
   * Returns the units of lipids contained in a bonus of leaf.
   */
  int contains(BonusType b, NutrientType n) const;

  /**
   * Returns the number of initial soldiers.
   */
  int num_ini_soldiers () const;

  /**
   * Returns the number of initial workers.
   */
  int num_ini_workers () const;

  /**
   * Returns the number of rows of a rectangle where food appears.
   */
  int bonus_rows () const;

  /**
   * Returns the number of columns of a rectangle where food appears.
   */
  int bonus_cols () const;

  /**
   * Food bonuses appear every bonus_period() rounds, starting from round 0.
   */
  int bonus_period () const;

  /**
   * Rounds after which a worker dies.
   */
  int worker_life () const;

  /**
   * Rounds after which a soldier dies.
   */
  int soldier_life () const;

  /**
   * Rounds after which a queen dies.
   */
  int queen_life () const;

  /**
   * Rounds after which an ant of type a dies.
   */
  int life (AntType a) const;

  /**
   * Returns whether pl is a valid player identifier.
   */

  bool player_ok (int pl) const;

  /**
   * Returns whether (i, j) is a position inside the board.
   */
  bool pos_ok (int i, int j) const;

  /**
   * Returns whether p is a position inside the board.
   */
  bool pos_ok (Pos p) const;


  //////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////


private:

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  int NUM_PLAYERS;
  int NUM_ROUNDS;
  int BOARD_ROWS;
  int BOARD_COLS;
  int QUEEN_PERIOD;
  int SOLDIER_CARBO;
  int SOLDIER_PROTE;
  int SOLDIER_LIPID;
  int WORKER_CARBO;
  int WORKER_PROTE;
  int WORKER_LIPID;
  int BREAD_CARBO;
  int BREAD_PROTE;
  int BREAD_LIPID;
  int SEED_CARBO;
  int SEED_PROTE;
  int SEED_LIPID;
  int LEAF_CARBO;
  int LEAF_PROTE;
  int LEAF_LIPID;
  int NUM_INI_SOLDIERS;
  int NUM_INI_WORKERS;
  int BONUS_ROWS;
  int BONUS_COLS;
  int BONUS_PERIOD;
  int WORKER_LIFE;
  int SOLDIER_LIFE;
  int QUEEN_LIFE;

  /**
   * Reads the settings from a stream.
   */
  static Settings read_settings (istream& is);

};

inline string Settings::version () {
  return string(GAME_NAME) + " " + string(VERSION);
}

inline int Settings::num_players        () const { return NUM_PLAYERS      ; }
inline int Settings::num_rounds         () const { return NUM_ROUNDS       ; }
inline int Settings::board_rows         () const { return BOARD_ROWS       ; }
inline int Settings::board_cols         () const { return BOARD_COLS       ; }
inline int Settings::queen_period       () const { return QUEEN_PERIOD     ; }
inline int Settings::soldier_carbo      () const { return SOLDIER_CARBO    ; }
inline int Settings::soldier_prote      () const { return SOLDIER_PROTE    ; }
inline int Settings::soldier_lipid      () const { return SOLDIER_LIPID    ; }
inline int Settings::worker_carbo       () const { return WORKER_CARBO     ; }
inline int Settings::worker_prote       () const { return WORKER_PROTE     ; }
inline int Settings::worker_lipid       () const { return WORKER_LIPID     ; }
inline int Settings::bread_carbo        () const { return BREAD_CARBO      ; }
inline int Settings::bread_prote        () const { return BREAD_PROTE      ; }
inline int Settings::bread_lipid        () const { return BREAD_LIPID      ; }
inline int Settings::seed_carbo         () const { return SEED_CARBO       ; }
inline int Settings::seed_prote         () const { return SEED_PROTE       ; }
inline int Settings::seed_lipid         () const { return SEED_LIPID       ; }
inline int Settings::leaf_carbo         () const { return LEAF_CARBO       ; }
inline int Settings::leaf_prote         () const { return LEAF_PROTE       ; }
inline int Settings::leaf_lipid         () const { return LEAF_LIPID       ; }
inline int Settings::num_ini_soldiers   () const { return NUM_INI_SOLDIERS ; }
inline int Settings::num_ini_workers    () const { return NUM_INI_WORKERS  ; }
inline int Settings::bonus_rows         () const { return BONUS_ROWS       ; }
inline int Settings::bonus_cols         () const { return BONUS_COLS       ; }
inline int Settings::bonus_period       () const { return BONUS_PERIOD     ; }
inline int Settings::worker_life        () const { return WORKER_LIFE      ; }
inline int Settings::soldier_life       () const { return SOLDIER_LIFE     ; }
inline int Settings::queen_life         () const { return QUEEN_LIFE       ; }


inline bool Settings::player_ok (int pl) const {
  return pl >= 0 and pl < num_players();
}

inline bool Settings::pos_ok (int i, int j) const {
  return i >= 0 and i < board_rows() and j >= 0 and j < board_cols();
}

inline bool Settings::pos_ok (Pos p) const {
  return pos_ok(p.i, p.j);
}

inline int Settings::needed (AntType a, NutrientType n) const {
  if (a == Queen) {
    cerr << "warning: asked for nutrients for an egg of a queen" << endl;
    return 0;
  }
  switch(n) {
  case Carbohydrate: return (a == Soldier ? soldier_carbo() : worker_carbo());
  case Protein:      return (a == Soldier ? soldier_prote() : worker_prote());
  case Lipid:        return (a == Soldier ? soldier_lipid() : worker_lipid());
  default:           return 0;
  }
}

inline int Settings::contains(BonusType b, NutrientType n) const {

  switch(b) {
  case Bread:
    switch(n) {
    case Carbohydrate: return bread_carbo();
    case Protein:      return bread_prote();
    case Lipid:        return bread_lipid();
    default:           return 0;
    }
  case Seed:
    switch(n) {
    case Carbohydrate: return seed_carbo();
    case Protein:      return seed_prote();
    case Lipid:        return seed_lipid();
    default:           return 0;
    }
  case Leaf:
    switch(n) {
    case Carbohydrate: return leaf_carbo();
    case Protein:      return leaf_prote();
    case Lipid:        return leaf_lipid();
    default:           return 0;
    }
  default:             return 0;
  }
}

inline int Settings::life (AntType a) const {
  switch(a) {
  case Worker:    return  worker_life();
  case Soldier:   return soldier_life();
  case Queen:     return   queen_life();
  default:        return 0;
  }
}

#endif
