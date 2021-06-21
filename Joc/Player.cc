//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////

#include "Player.hh"

void Player::reset (ifstream& is) {

  // Should read what Board::print_state() prints.
  // Should fill the same data structures as
  // Board::Board (istream& is, int seed), except for settings and names.
  // THESE DATA STRUCTURES MUST BE RESET: maps WITH clear(), etc.

  *(Action*)this = Action();

  read_grid(is);

  string s;
  is >> s >> rnd;
  _my_assert(s == "round", "Expected 'round' while parsing.");
  _my_assert(rnd >= 0 and rnd < num_rounds(), "Round is not ok.");

  is >> s;
  _my_assert(s == "score", "Expected 'score' while parsing.");
  scr = vector<int>(num_players());
  for (auto& s : scr) {
    is >> s;
    _my_assert(s >= 0, "Score cannot be negative.");
  }

  is >> s;
  _my_assert(s == "status", "Expected 'status' while parsing.");
  stats = vector<double>(num_players());
  for (auto& st : stats) {
    is >> st;
    _my_assert(st == -1 or (st >= 0 and st <= 1), "Status is not ok.");
  }

  is >> s;
  _my_assert(s == "ants", "Expected 'ants' while parsing.");

  ants           .clear();
  player2soldiers.clear();
  player2workers .clear();
  player2queens  .clear();

  player2soldiers = vector<set<int>>(num_players());
  player2workers  = vector<set<int>>(num_players());
  player2queens   = vector<set<int>>(num_players());

  int num_ants;
  is >> num_ants;

  vector<string> labels =
    {"type", "id", "player", "i", "j", "carbo", "prote", "lipid", "bonus", "life"};
  for (string l : labels) {
    is >> s; _my_assert(s == l, "Expected '" + l + "' while parsing.");
  }

  for (int k = 0; k < num_ants; ++k) {
    char c_atype, c_btype;
    int id, pl, i, j, r0, r1, r2, life;
    is >> c_atype >> id >> pl >> i >> j >> r0 >> r1 >> r2 >> c_btype >> life;
    AntType atype = AntType(char2AntType(c_atype));
    _my_assert(atype == Queen or atype == Soldier or atype == Worker,
               "Wrong ant type.");

    _my_assert(not ants.count(id), "Identifier already used.");
    _my_assert(player_ok(pl), "Wrong player.");
    Pos p(i, j);
    _my_assert(pos_ok(p), "Wrong position.");
    _my_assert(r0 >= 0, "Should be non-negative.");
    _my_assert(r1 >= 0, "Should be non-negative.");
    _my_assert(r2 >= 0, "Should be non-negative.");
    BonusType btype = BonusType(char2BonusType(c_btype));
    _my_assert(btype == Bread or btype == Seed or btype == Leaf or btype == None,
               "Wrong bonus type.");
    _my_assert(life >= 1, "Should be positive.");
    ants[id] = Ant(atype, id, pl, p, vector<int>{r0, r1, r2}, btype, life);
    grid[i][j].id = id;
    if      (atype == Soldier) player2soldiers[pl].insert(id);
    else if (atype == Worker)  player2workers [pl].insert(id);
    else                       player2queens  [pl].insert(id);
  }

  _my_assert(ok(), "Invariants are not satisfied.");

  forget();
}
