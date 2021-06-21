//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////  

#include "Info.hh"

bool Info::ok() const {

  if (int(grid.size()) != board_rows()) {
    cerr << "error: mismatch in number of rows" << endl;
    return false;
  }

  if (int(grid[0].size()) != board_cols()) {
    cerr << "error: mismatch in number of columns" << endl;
    return false;
  }

  for (int i = 0; i < board_rows(); ++i) {
    for (int j = 0; j < board_cols(); ++j) {
      const Cell& c = grid[i][j];
      if (c.type == Water) {
        if (c.bonus != None) {
          cerr << "error: water cells cannot have bonus" << endl;
          return false;
        }
        if (c.id != -1) {
          cerr << "error: water cells cannot have ants" << endl;
          return false;
        }
      }
      else if (c.type == Soil) {
        if (c.id != -1) {
          auto it = ants.find(c.id);
          if (it == ants.end()) {
            cerr << "error: could not find ant identifier" << endl;
            return false;
          }
          const Ant& a = it->second;
          if (a.pos != Pos(i, j)) {
            cerr << "error: mismatch in idenfiers in the grid" << endl;
            return false;
          }
          if (a.type == Queen and c.bonus != None) {
            cerr << "error: queen should eat the bonus" << endl;
            return false;
          }
        }
        if (c.bonus < Bread or c.bonus > None) {
          cerr << "error: unknown bonus" << endl;
          return false;
        }
      }
      else {
        cerr << "error: cells should be of water or soil" << endl;
        return false;
      }
    }
  }
  
  if (not (rnd >= 0 and rnd <= num_rounds())) {
    cerr << "error: wrong number of rounds" << endl;
    return false;
  }

  for (int pl = 0; pl < num_players(); ++pl) {
    double st = stats[pl];
    if (st != -1 and not (0 <= st and st <= 1)) {
      cerr << "error: status should be -1 or within [0, 1]" << endl;
      return false;
    }
  }

  vector<vector<int>> player2ants(num_players(), vector<int>(3));
  for (const auto& p : ants) {
    int id = p.first;
    const auto& a = p.second;

    if (a.id != id) {
      cerr << "error: mismatch in identifiers" << endl;
      return false;
    }

    if (not (player_ok(a.player))) {
      cerr << "error: wrong player identifier" << endl;
      return false;
    }

    if (not (pos_ok(a.pos))) {
      cerr << "error: wrong position" << endl;
      return false;
    }

    if (a.reserve.size() != 3) {
      cerr << "error: reserve has wrong size" << endl;
      return false;
    }
    
    if (a.type == Queen) {
      for (int r : a.reserve) {
        if (r < 0) {
          cerr << "error: queen has a negative reserve" << endl;
          return false;
        }
      }
      if (a.bonus != None) {
        cerr << "error: queen is carrying a bonus" << endl;
        return false;
      }
    }
    else if (a.type == Worker) {
      for (int r : a.reserve) {
        if (r != 0) {
          cerr << "error: worker has a non-null reserve" << endl;
          return false;
        }
      }
    }
    else if (a.type == Soldier) {
      for (int r : a.reserve) {
        if (r != 0) {
          cerr << "error: soldier has a non-null reserve" << endl;
          return false;
        }
      }
      if (a.bonus != None) {
        cerr << "error: soldier is carrying a bonus" << endl;
        return false;
      }
    }
    else {
      cerr << "error: wrong type of ant" << endl;
      return false;
    }

    if (a.life <= 0) {
      cerr << "error: ant should have positive life" << endl;
      return false;
    }
    else if (a.life > life(a.type)) {
      cerr << "error: ant has too large a life" << endl;
      return false;
    }

    ++player2ants[a.player][a.type];
  }

  if (int(player2soldiers.size()) != num_players()) {
    cerr << "error: size of player2soldiers should be number of players" << endl;
    return false;
  }

  if (int(player2workers.size()) != num_players()) {
    cerr << "error: size of player2workers should be number of players" << endl;
    return false;
  }

  if (int(player2queens.size()) != num_players()) {
    cerr << "error: size of player2queens should be number of players" << endl;
    return false;
  }
  
  for (int pl = 0; pl < num_players(); ++pl) {

    const auto& soldiers = player2soldiers[pl];
    for (int id : soldiers) {
      auto it = ants.find(id);
      if (it == ants.end()) {
        cerr << "error: could not find identifier of soldier" << endl;
        return false;
      }
      const Ant& a = it->second;
      if (a.type != Soldier) {
        cerr << "error: mismatch in type of soldier" << endl;
        return false;
      }
      if (a.player != pl) {
        cerr << "error: mismatch in player of soldier" << endl;
        return false;
      }
    }

    if (player2ants[pl][Soldier] != int(soldiers.size())) {
      cerr << "error: mismatch in number of ants" << endl;
      return false;
    }


    const auto& workers = player2workers[pl];
    for (int id : workers) {
      auto it = ants.find(id);
      if (it == ants.end()) {
        cerr << "error: could not find identifier of worker" << endl;
        return false;
      }
      const Ant& a = it->second;
      if (a.type != Worker) {
        cerr << "error: mismatch in type of worker" << endl;
        return false;
      }
      if (a.player != pl) {
        cerr << "error: mismatch in player of worker" << endl;
        return false;
      }
    }

    if (player2ants[pl][Worker] != int(workers.size())) {
      cerr << "error: mismatch in number of ants" << endl;
      return false;
    }

    
    const auto& queens = player2queens[pl];
    for (int id : queens) {
      auto it = ants.find(id);
      if (it == ants.end()) {
        cerr << "error: could not find identifier of queen" << endl;
        return false;
      }
      const Ant& a = it->second;
      if (a.type != Queen) {
        cerr << "error: mismatch in type of queen" << endl;
        return false;
      }
      if (a.player != pl) {
        cerr << "error: mismatch in player of queen" << endl;
        return false;
      }
    }

    if (player2ants[pl][Queen] != int(queens.size())) {
      cerr << "error: mismatch in number of ants" << endl;
      return false;
    }

    if (queens.size() >= 2) {
      cerr << "error: there can only be at most one queen" << endl;
      return false;
    }
    
    if (queens.empty() and not (soldiers.empty() and workers.empty())) {
      cerr << "error: the queen is the last to die" << endl;
      return false;
    }

    for (int b = 0; b < 3; ++b) {

      Pos tl = player2bonus2tl[pl][b];
      if (not pos_ok(tl)) {
        cerr << "error: invalid position top left" << endl;
        return false;
      }

      Pos br = tl + Pos(bonus_rows()-1, bonus_cols()-1);
      if (not pos_ok(br)) {
        cerr << "error: invalid position bottom right" << endl;
        return false;
      }
      
      if (pl == 0 and not (br.i <  board_rows()/2 and br.j <  board_cols()/2)) {
        cerr << "error: rectangle should be within the quadrant" << endl;
        return false;
      }
      if (pl == 1 and not (br.i <  board_rows()/2 and tl.j >= board_cols()/2)) {
        cerr << "error: rectangle should be within the quadrant" << endl;
        return false;
      }
      if (pl == 2 and not (tl.i >= board_rows()/2 and tl.j >= board_cols()/2)) {
        cerr << "error: rectangle should be within the quadrant" << endl;
        return false;
      }
      if (pl == 3 and not (tl.i >= board_rows()/2 and br.j <  board_cols()/2)) {
        cerr << "error: rectangle should be within the quadrant" << endl;
        return false;
      }
    }
  }
  
  return true;
}
