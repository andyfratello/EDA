//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

#include "Settings.hh"

Settings Settings::read_settings (istream& is) {
  Settings r;
  string s, v;

  // Version, compared part by part.
  istringstream vs(version());
  while (!vs.eof()) {
    is >> s;
    vs >> v;
    _my_assert(s == v, "Problems when reading.");
  };

  is >> s >> r.NUM_PLAYERS;
  _my_assert(s == "NUM_PLAYERS", "Expected 'NUM_PLAYERS' while parsing.");
  _my_assert(r.NUM_PLAYERS == 4, "Wrong number of players.");

  is >> s >> r.NUM_ROUNDS;
  _my_assert(s == "NUM_ROUNDS", "Expected 'NUM_ROUNDS' while parsing.");
  _my_assert(r.NUM_ROUNDS >= 1, "Wrong number of rounds.");

  is >> s >> r.BOARD_ROWS;
  _my_assert(s == "BOARD_ROWS", "Expected 'BOARD_ROWS' while parsing.");
  _my_assert(r.BOARD_ROWS >= 20, "Wrong number of rows.");

  is >> s >> r.BOARD_COLS;
  _my_assert(s == "BOARD_COLS", "Expected 'BOARD_COLS' while parsing.");
  _my_assert(r.BOARD_COLS >= 20, "Wrong number of columns.");

  is >> s >> r.QUEEN_PERIOD;
  _my_assert(s == "QUEEN_PERIOD", "Expected 'QUEEN_PERIOD' while parsing.");
  _my_assert(r.QUEEN_PERIOD >= 1, "Wrong value of period.");

  is >> s >> r.SOLDIER_CARBO;
  _my_assert(s == "SOLDIER_CARBO", "Expected 'SOLDIER_CARBO' while parsing.");
  _my_assert(r.SOLDIER_CARBO >= 0, "Value should be non-negative.");

  is >> s >> r.SOLDIER_PROTE;
  _my_assert(s == "SOLDIER_PROTE", "Expected 'SOLDIER_PROTE' while parsing.");
  _my_assert(r.SOLDIER_PROTE >= 0, "Value should be non-negative.");

  is >> s >> r.SOLDIER_LIPID;
  _my_assert(s == "SOLDIER_LIPID", "Expected 'SOLDIER_LIPID' while parsing.");
  _my_assert(r.SOLDIER_LIPID >= 0, "Value should be non-negative.");

  is >> s >> r.WORKER_CARBO;
  _my_assert(s == "WORKER_CARBO", "Expected 'WORKER_CARBO' while parsing.");
  _my_assert(r.WORKER_CARBO >= 0, "Value should be non-negative.");

  is >> s >> r.WORKER_PROTE;
  _my_assert(s == "WORKER_PROTE", "Expected 'WORKER_PROTE' while parsing.");
  _my_assert(r.WORKER_PROTE >= 0, "Value should be non-negative.");

  is >> s >> r.WORKER_LIPID;
  _my_assert(s == "WORKER_LIPID", "Expected 'WORKER_LIPID' while parsing.");
  _my_assert(r.WORKER_LIPID >= 0, "Value should be non-negative.");

  is >> s >> r.BREAD_CARBO;
  _my_assert(s == "BREAD_CARBO", "Expected 'BREAD_CARBO' while parsing.");
  _my_assert(r.BREAD_CARBO >= 0, "Value should be non-negative.");

  is >> s >> r.BREAD_PROTE;
  _my_assert(s == "BREAD_PROTE", "Expected 'BREAD_PROTE' while parsing.");
  _my_assert(r.BREAD_PROTE >= 0, "Value should be non-negative.");

  is >> s >> r.BREAD_LIPID;
  _my_assert(s == "BREAD_LIPID", "Expected 'BREAD_LIPID' while parsing.");
  _my_assert(r.BREAD_LIPID >= 0, "Value should be non-negative.");

  is >> s >> r.SEED_CARBO;
  _my_assert(s == "SEED_CARBO", "Expected 'SEED_CARBO' while parsing.");
  _my_assert(r.SEED_CARBO >= 0, "Value should be non-negative.");

  is >> s >> r.SEED_PROTE;
  _my_assert(s == "SEED_PROTE", "Expected 'SEED_PROTE' while parsing.");
  _my_assert(r.SEED_PROTE >= 0, "Value should be non-negative.");

  is >> s >> r.SEED_LIPID;
  _my_assert(s == "SEED_LIPID", "Expected 'SEED_LIPID' while parsing.");
  _my_assert(r.SEED_LIPID >= 0, "Value should be non-negative.");

  is >> s >> r.LEAF_CARBO;
  _my_assert(s == "LEAF_CARBO", "Expected 'LEAF_CARBO' while parsing.");
  _my_assert(r.LEAF_CARBO >= 0, "Value should be non-negative.");

  is >> s >> r.LEAF_PROTE;
  _my_assert(s == "LEAF_PROTE", "Expected 'LEAF_PROTE' while parsing.");
  _my_assert(r.LEAF_PROTE >= 0, "Value should be non-negative.");

  is >> s >> r.LEAF_LIPID;
  _my_assert(s == "LEAF_LIPID", "Expected 'LEAF_LIPID' while parsing.");
  _my_assert(r.LEAF_LIPID >= 0, "Value should be non-negative.");

  is >> s >> r.NUM_INI_SOLDIERS;
  _my_assert(s == "NUM_INI_SOLDIERS", "Expected 'NUM_INI_SOLDIERS' while parsing.");
  _my_assert(r.NUM_INI_SOLDIERS >= 0, "Value should be non-negative.");

  is >> s >> r.NUM_INI_WORKERS;
  _my_assert(s == "NUM_INI_WORKERS", "Expected 'NUM_INI_WORKERS' while parsing.");
  _my_assert(r.NUM_INI_WORKERS >= 0, "Value should be non-negative.");

  is >> s >> r.BONUS_ROWS;
  _my_assert(s == "BONUS_ROWS", "Expected 'BONUS_ROWS' while parsing.");
  _my_assert(r.BONUS_ROWS >= 0, "Wrong number of rows.");

  is >> s >> r.BONUS_COLS;
  _my_assert(s == "BONUS_COLS", "Expected 'BONUS_COLS' while parsing.");
  _my_assert(r.BONUS_COLS >= 0, "Wrong number of columns.");

  is >> s >> r.BONUS_PERIOD;
  _my_assert(s == "BONUS_PERIOD", "Expected 'BONUS_PERIOD' while parsing.");
  _my_assert(r.BONUS_PERIOD >= 0, "Wrong value of period.");
  
  is >> s >> r.WORKER_LIFE;
  _my_assert(s == "WORKER_LIFE", "Expected 'WORKER_LIFE' while parsing.");
  _my_assert(r.WORKER_LIFE >= 1, "Wrong value of life.");

  is >> s >> r.SOLDIER_LIFE;
  _my_assert(s == "SOLDIER_LIFE", "Expected 'SOLDIER_LIFE' while parsing.");
  _my_assert(r.SOLDIER_LIFE >= 1, "Wrong value of life.");

  is >> s >> r.QUEEN_LIFE;
  _my_assert(s == "QUEEN_LIFE", "Expected 'QUEEN_LIFE' while parsing.");
  _my_assert(r.QUEEN_LIFE >= 1, "Wrong value of life.");

  return r;
}
