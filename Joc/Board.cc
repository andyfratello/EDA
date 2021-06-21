//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////

#include "Board.hh"
#include "Action.hh"


Pos Board::rotate(Pos p, int pl) const {
  int r = board_rows();
  int c = board_cols();
  if      (pl == 1) return Pos(        p.j, c - 1 - p.i);
  else if (pl == 2) return Pos(r - 1 - p.i, c - 1 - p.j);
  else if (pl == 3) return Pos(r - 1 - p.j,         p.i);
  return p;
}


void Board::create_new_ant(int pl, Pos p, AntType t) {

  int id = fresh_id;
  ++fresh_id;
  _my_assert(not ants.count(id), "Identifier is not fresh.");

  ants[id] = Ant(t, id, pl, p, vector<int>(3, 0), None, life(t));

  _my_assert(grid[p.i][p.j].id   == -1,   "Cell is already full.");
  _my_assert(grid[p.i][p.j].type == Soil, "Cell has water."      );

  grid[p.i][p.j].id = id;

  if      (t == Soldier) player2soldiers[pl].insert(id);
  else if (t == Worker)  player2workers [pl].insert(id);
  else                   player2queens  [pl].insert(id);
}


void Board::create_initial_ants(int pl) {
  vector<int> left = {1, num_ini_soldiers(), num_ini_workers()};
  int total = accumulate(left.begin(), left.end(), 0);
  int i = 0;
  int j = 0;
  while (total > 0) {
    int t = random(0, 2);
    if (left[t] == 0) t = (t + 1) % 3;
    if (left[t] == 0) t = (t + 1) % 3;
    _my_assert(left[t] > 0, "There must be somebody left.");

    Pos p = rotate(Pos(i,j), pl);
    while (grid[p.i][p.j].id != -1 or grid[p.i][p.j].type == Water) {
      if (i > 0) {
        --i;
        ++j;
      }
      else {
        i = j+1;
        j = 0;
      }
      p = rotate(Pos(i,j), pl);
    }
    _my_assert(pos_ok(p), "Position is not ok.");
    create_new_ant(pl, p, AntType(t));
    --left[t];
    --total;
  }
  _my_assert(int(player2soldiers[pl].size()) == num_ini_soldiers(), "Wrong no. of initial soldiers.");
  _my_assert(int(player2workers [pl].size()) == num_ini_workers (), "Wrong no. of initial workers." );
  _my_assert(int(player2queens  [pl].size()) == 1,                  "Wrong no. of initial queens."  );
}


Board::Board(istream& is, int seed) {
  set_random_seed(seed);
  *static_cast<Settings*>(this) = Settings::read_settings(is);
  read_generator_and_grid(is);
  names = vector<string>(num_players());
  scr   = vector<int>   (num_players(), 0);
  stats = vector<double>(num_players(), 0);
  rnd = 0;
  fresh_id = 0;

  player2soldiers = vector<set<int>>(num_players());
  player2workers  = vector<set<int>>(num_players());
  player2queens   = vector<set<int>>(num_players());

  for (int pl = 0; pl < num_players(); ++pl)
    create_initial_ants(pl);

  _my_assert(ok(), "Invariants are not satisfied.");
}


void Board::print_settings (ostream& os) const {

  os <<   version()                                        << endl;
  os                                                       << endl;
  os <<  "NUM_PLAYERS"      << "\t" <<  num_players()      << endl;
  os <<  "NUM_ROUNDS"       << "\t" <<  num_rounds()       << endl;
  os <<  "BOARD_ROWS"       << "\t" <<  board_rows()       << endl;
  os <<  "BOARD_COLS"       << "\t" <<  board_cols()       << endl;
  os <<  "QUEEN_PERIOD"     << "\t" <<  queen_period()     << endl;
  os <<  "SOLDIER_CARBO"    << "\t" <<  soldier_carbo()    << endl;
  os <<  "SOLDIER_PROTE"    << "\t" <<  soldier_prote()    << endl;
  os <<  "SOLDIER_LIPID"    << "\t" <<  soldier_lipid()    << endl;
  os <<  "WORKER_CARBO"     << "\t" <<  worker_carbo()     << endl;
  os <<  "WORKER_PROTE"     << "\t" <<  worker_prote()     << endl;
  os <<  "WORKER_LIPID"     << "\t" <<  worker_lipid()     << endl;
  os <<  "BREAD_CARBO"      << "\t" <<  bread_carbo()      << endl;
  os <<  "BREAD_PROTE"      << "\t" <<  bread_prote()      << endl;
  os <<  "BREAD_LIPID"      << "\t" <<  bread_lipid()      << endl;
  os <<  "SEED_CARBO"       << "\t" <<  seed_carbo()       << endl;
  os <<  "SEED_PROTE"       << "\t" <<  seed_prote()       << endl;
  os <<  "SEED_LIPID"       << "\t" <<  seed_lipid()       << endl;
  os <<  "LEAF_CARBO"       << "\t" <<  leaf_carbo()       << endl;
  os <<  "LEAF_PROTE"       << "\t" <<  leaf_prote()       << endl;
  os <<  "LEAF_LIPID"       << "\t" <<  leaf_lipid()       << endl;
  os <<  "NUM_INI_SOLDIERS" << "\t" <<  num_ini_soldiers() << endl;
  os <<  "NUM_INI_WORKERS"  << "\t" <<  num_ini_workers()  << endl;
  os <<  "BONUS_ROWS"       << "\t" <<  bonus_rows()       << endl;
  os <<  "BONUS_COLS"       << "\t" <<  bonus_cols()       << endl;
  os <<  "BONUS_PERIOD"     << "\t" <<  bonus_period()     << endl;
  os <<  "WORKER_LIFE"      << "\t" <<  worker_life()      << endl;
  os <<  "SOLDIER_LIFE"     << "\t" <<  soldier_life()     << endl;
  os <<  "QUEEN_LIFE"       << "\t" <<  queen_life()       << endl;
}


void Board::print_names (ostream& os) const {
  os << "names         ";
  for (int pl = 0; pl < num_players(); ++pl) os << ' ' << name(pl);
  os << endl;
}


void Board::print_state (ostream& os) const {

  // Should start with the same format of Info::read_grid.
  // Then other data describing the state.

  os << endl << endl;

  os << "   ";
  for (int j = 0; j < board_cols(); ++j)
    os << j / 10;
  os << endl;

  os << "   ";
  for (int j = 0; j < board_cols(); ++j)
    os << j % 10;
  os << endl;

  for (int i = 0; i < board_rows(); ++i) {
    os << i / 10 << i % 10 << " ";
    for (int j = 0; j < board_cols(); ++j) {
      const Cell& c = grid[i][j];
      if      (c.type  == Water)  os << 'W';
      else if (c.bonus == Bread)  os << 'B';
      else if (c.bonus == Seed)   os << 'S';
      else if (c.bonus == Leaf)   os << 'L';
      else os << '.';
    }
    os << endl;
  }

  os << endl << "rivers" << endl;
  os << rivers.size() << endl;
  for (const auto& r : rivers) {
    os << '\t' << r.size() << endl;
    for (const auto& p : r) {
      os << '\t' << '\t' << p.i << '\t' << p.j << endl;
    }
  }


  vector<string> bonus = {"bread", "seed", "leaf"};
  for (int b = 0; b < int(bonus.size()); ++b) {
    os << endl << bonus[b] << endl;
    for (int pl = 0; pl < num_players(); ++pl) {
      const Pos& p = player2bonus2tl[pl][b];
      os << p.i << "\t" << p.j << endl;
    }
  }

  os << endl;

  os << "round " << rnd << endl;

  os << endl;

  os << "score";
  for (auto s : scr) os << "\t" << s;
  os << endl;

  os << endl;

  os << "status";
  for (auto s : stats) os << "\t" << s;
  os << endl;

  os << endl;

  os << "ants" << endl;
  os << ants.size() << endl;

  vector<string> labels =
    {"type", "id", "player", "i", "j", "carbo", "prote", "lipid", "bonus", "life"};
  for (string l : labels) os << l << "\t";
  os << endl;

  for (const auto& p : ants ) print_ant(p.second, os);
  os << endl;
}


void Board::print_results () const {
  int max_score = 0;
  vector<int> v;
  for (int pl = 0; pl < num_players(); ++pl) {

    cerr << "info: player " <<  name(pl)
         << " got score "   << score(pl) << endl;

    if      (score(pl) == max_score)  v.push_back(pl);
    else if (score(pl) >  max_score) {
      max_score = score(pl);
      v = vector<int>(1, pl);
    }
  }

  cerr << "info: player(s)";
  for (int pl : v) cerr << " " << name(pl);
  cerr << " got top score" << endl;
}


bool Board::execute(const Command&    m,
                    set<int>&         killed,
                    vector<Egg>&      eggs) {

  int         id     =             m.id;
  Dir         dir    =         Dir(m.dir);
  CommandType c_type = CommandType(m.c_type);
  AntType     a_type =     AntType(m.a_type);

  if (not command_type_ok(c_type)) {
    cerr << "warning: invalid command type in command: " << c_type << endl;
    return false;
  }

  if (killed.count(id)) return false;

  Ant&   a = ants[id];
  Pos   op = a.pos;
  Cell& oc = grid[op.i][op.j];

  if (c_type == Move) {

    if (not dir_ok(dir)) {
      cerr << "warning: invalid dir in command: " << dir << endl;
      return false;
    }

    if (a.type == Queen and round() % queen_period() != 0) {
      cerr << "warning: cannot move queen at round : " << round() << endl;
      return false;
    }

    Pos np = op + dir;
    if (not pos_ok(np)) {
      cerr << "warning: cannot move to position " << np << " out of the board" << endl;
      return false;
    }

    Cell& nc = grid[np.i][np.j];
    if (nc.type == Water) {
      cerr << "warning: cannot move to position " << np << " with water" << endl;
      return false;
    }

    if (nc.id != -1) {      // Fight!
      _my_assert(id != nc.id, "Identifiers should be different.");
      Ant& b = ants[nc.id];
      if      (a.type < b.type) kill(nc.id, killed);
      else if (a.type > b.type) kill(   id, killed);
      else {
        kill(nc.id, killed);
        kill(   id, killed);
      }
    }

    if (not killed.count(id)) {
      _my_assert(nc.id == -1, "Cell should be empty.");
      oc.id = -1;
      nc.id = id;
      a.pos = np;

      if (a.type == Queen and nc.bonus != None) {

        for (int k = 0; k < int(nutrients.size()); ++k)
          a.reserve[k] += contains(nc.bonus, NutrientType(k));

        nc.bonus = None;
      }
    }
  }

  else if (c_type == Take) {

    if (a.type != Worker) {
      cerr << "warning: only workers can take food" << endl;
      return false;
    }

    if (oc.bonus == None) {
      cerr << "warning: no food at position " << op << endl;
      return false;
    }

    if (a.bonus != None) {
      cerr << "warning: ant " << id << " is already carrying food" << endl;
      return false;
    }

    a.bonus = oc.bonus;
    oc.bonus = None;
  }

  else if (c_type == Leave) {

    if (a.type != Worker) {
      cerr << "warning: only workers can leave food" << endl;
      return false;
    }

    if (oc.bonus != None) {
      cerr << "warning: already food at position " << op << endl;
      return false;
    }

    if (a.bonus == None) {
      cerr << "warning: ant " << id << " is not carrying any bonus" << endl;
      return false;
    }

    oc.bonus = a.bonus;
    a.bonus = None;
  }

  else if (c_type == Lay) {

    if (not dir_ok(dir)) {
      cerr << "warning: invalid dir in command: " << dir << endl;
      return false;
    }

    if (a_type != Soldier and a_type != Worker) {
      cerr << "warning: invalid ant type in command: " << a_type << endl;
      return false;
    }

    if (a.type != Queen) {
      cerr << "warning: only queens can lay eggs" << endl;
      return false;
    }

    Pos np = op + dir;
    if (not pos_ok(np)) {
      cerr << "warning: cannot lay eggs at position " << np << " out of the board" << endl;
      return false;
    }

    Cell& nc = grid[np.i][np.j];
    if (nc.type == Water) {
      cerr << "warning: cannot lay eggs at position " << np << " with water" << endl;
      return false;
    }

    for (int k = 0; k < int(nutrients.size()); ++k)
      if (a.reserve[k] < needed(a_type, NutrientType(k))) {
        cerr << "warning: not enough " << nutrients[k] << "s" << endl;
        return false;
      }

    for (int k = 0; k < int(nutrients.size()); ++k)
      a.reserve[k] -= needed(a_type, NutrientType(k));

    eggs.push_back({a.player, np, a_type});
  }

  return true;
}


void Board::kill(int id, set<int>& killed) {

  _my_assert(not killed.count(id), "Already killed");

  auto it = ants.find(id);
  _my_assert(it != ants.end(), "Could not find ant to be killed");

  Ant&  a = it->second;
  int  pl = a.player;

  grid[a.pos.i][a.pos.j].id = -1;

  if (a.type == Soldier) {
    _my_assert(player2soldiers[pl].count(id), "Soldier to kill is not registered.");
    player2soldiers[pl].erase(id);
  }
  else if (a.type == Worker) {
    _my_assert(player2workers[pl].count(id),   "Worker to kill is not registered.");
    player2workers[pl].erase(id);
  }
  else if (a.type == Queen) {
    _my_assert(player2queens[pl].count(id),     "Queen to kill is not registered.");
    player2queens[pl].erase(id);
  }

  ants.erase(it);
  killed.insert(id);
}


void Board::transform_into_queen(int id) {

  Ant& a = ants[id];
  int pl = a.player;

  _my_assert(a.type == Soldier or a.type == Worker, "Should be a soldier or worker.");
  if (a.type == Soldier) player2soldiers[pl].erase(id);
  else                   player2workers [pl].erase(id);

  _my_assert(player2queens[pl].empty(), "Expected no queen.");
  player2queens[pl].insert(id);

  for (int k = 0; k < int(nutrients.size()); ++k)
    _my_assert(a.reserve[k] == 0, "Expected no " + nutrients[k] + "s.");

  a.type = Queen;
  a.life = queen_life();

  Cell& c = grid[a.pos.i][a.pos.j];
  if (c.bonus != None) {

    for (int k = 0; k < int(nutrients.size()); ++k)
      a.reserve[k] += contains(c.bonus, NutrientType(k));

    c.bonus = None;
  }

  if (a.bonus != None) {

    for (int k = 0; k < int(nutrients.size()); ++k)    
      a.reserve[k] += contains(a.bonus, NutrientType(k));

    a.bonus = None;
  }
}


void Board::regenerate_bonus(Pos tl, BonusType b) {
  _my_assert(b != None, "Expected a bonus.");
  vector<Pos> cands;
  for (int di = 0; di < bonus_rows(); ++di)
    for (int dj = 0; dj < bonus_cols(); ++dj) {
      Pos p = tl;
      p.i += di;
      p.j += dj;
      if (pos_ok(p)) {
        const Cell& c = cell(p);
        if (c.type == Soil and c.id == -1 and c.bonus == None)
          cands.push_back(p);
      }
    }
  if (not cands.empty()) {
    int k = random(0, cands.size() - 1);
    Pos p = cands[k];
    Cell& c = grid[p.i][p.j];
    c.bonus = b;
  }
}


void Board::next (const vector<Action>& act, ostream& os) {

  _my_assert(ok(), "Invariants are not satisfied.");

  int npl = num_players();
  _my_assert(int(act.size()) == npl, "Size should be number of players.");

  // Chooses (at most) one command per ant.
  set<int> seen;
  vector<Command> v;
  for (int pl = 0; pl < npl; ++pl)
    for (const Command& m : act[pl].v) {
      int id     = m.id;
      int c_type = m.c_type;
      int dir    = m.dir;
      int a_type = m.a_type;

      auto it = ants.find(id);

      if (it == ants.end())
        cerr << "warning: invalid id : " << id << endl;

      else if (it->second.player != pl)
        cerr << "warning: ant " << id << " of player " << it->second.player
             << " not owned by " << pl << endl;
      else {
        // Here an assert as repetitions should have already been filtered out.
        _my_assert(not seen.count(id), "More than one command for the same ant.");
        seen.insert(id);

        v.push_back(Command(id, c_type, dir, a_type));
      }
    }

  // Runs all commands using a random order.
  int num = v.size();
  vector<int> perm = random_permutation(num);
  set<int> killed;
  vector<Command> commands_done;
  vector<Egg> eggs;
  for (int i = 0; i < num; ++i) {
    const Command& m = v[perm[i]];
    if (execute(m, killed, eggs))
      commands_done.push_back(m);
  }
  os << "commands" << endl;
  Action::print(commands_done, os);

  // Kill ants whose life is exhausted.
  vector<int> to_kill;
  for (auto& p : ants) {
    Ant& a = p.second;
    --a.life;
    if (a.life == 0) to_kill.push_back(a.id);
  }
  for (int id : to_kill) {
    kill(id, killed);
  }

  // Eggs hatch.
  perm = random_permutation(eggs.size());
  for (int k = 0; k < int(perm.size()); ++k) {

    const Egg& e = eggs[perm[k]];

    _my_assert(   pos_ok(e.pos   ), "Position should be ok.");
    _my_assert(player_ok(e.player),   "Player should be ok.");
    _my_assert(e.type == Soldier or e.type == Worker,
               "Ant type should be soldier or worker.");

    Pos p = e.pos;

    _my_assert(grid[p.i][p.j].type == Soil, "Cell should be soil.");

    if (grid[p.i][p.j].id == -1)
      create_new_ant(e.player, p, e.type);
  }

  // Ants become queens if needed and if possible.
  for (int pl = 0; pl < npl; ++pl) {
    if (player2queens[pl].size() == 0) {
      vector<int> soldiers_and_workers;
      for (int id : player2soldiers[pl]) soldiers_and_workers.push_back(id);
      for (int id : player2workers [pl]) soldiers_and_workers.push_back(id);
      if (not soldiers_and_workers.empty()) {
        int pos = random(0, soldiers_and_workers.size()-1);
        transform_into_queen(soldiers_and_workers[pos]);
      }
    }
  }

  // Regenerate food bonus.
  if (rnd % bonus_period() == 0)
    for (int pl = 0; pl < npl; ++pl) {
      const vector<Pos>& bonus2tl = player2bonus2tl[pl];
      for (int b = 0; b != int(None); ++b)
        regenerate_bonus(bonus2tl[b], BonusType(b));
    }

  // Update scores.
  for (int pl = 0; pl < npl; ++pl) {
    scr[pl] +=
      player2soldiers[pl].size() +
      player2workers [pl].size() +
      player2queens  [pl].size();
  }

  ++rnd;

  _my_assert(ok(), "Invariants are not satisfied.");
}


// ***************************************************************************

const char Board::Undef = '.';
const char Board::River = 'R';

// S, E, N, W
const vector<int> Board::DIRI4 = { 1,  0, -1,  0};
const vector<int> Board::DIRJ4 = { 0,  1,  0, -1};

// SW, S, SE, E, NE, N, NW, W
const vector<int> Board::DIRI8 = {  1,  1,  1,  0, -1, -1, -1,  0};
const vector<int> Board::DIRJ8 = { -1,  0,  1,  1,  1,  0, -1, -1};


void Board::generator1 (const vector<int>& param) {

  int br = board_rows();
  int bc = board_cols();

  m = vector<vector<char>>(br, vector<char>(bc, Undef));
  rivers.clear();
  bool found = false;
  for (int k = 0; not found and k < MAX_ATTEMPTS; ++k) {
    place_rivers();
    if (is_connected()) found = true;
    else {
      m = vector<vector<char>>(br, vector<char>(bc, Undef));
      rivers.clear();
    }
  }

  grid = vector< vector<Cell> >(br, vector<Cell>(bc));
  for (int i = 0; i < br; ++i)
    for (int j = 0; j < bc; ++j)
      grid[i][j].type = (m[i][j] == Undef ? Soil : Water);


  int fr = bonus_rows();
  int fc = bonus_cols();

  player2bonus2tl = vector< vector<Pos> >(num_players(), vector<Pos>(3));

  for (int pl = 0; pl < num_players(); ++pl)
    for (int b = 0; b < 3; ++b) {
      int i, j;
      if (pl == 0 or pl == 1) i = random(0,    br/2 - fr);
      else                    i = random(br/2, br   - fr);
      if (pl == 0 or pl == 3) j = random(0,    bc/2 - fc);
      else                    j = random(bc/2, bc   - fc);
      player2bonus2tl[pl][b] = Pos(i, j);
    }
}
