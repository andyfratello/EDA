#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Gambino


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef vector<int> Vec;
  typedef set<Pos> SetPos;
  typedef vector<vector<Dir>> Board;
  typedef vector<vector<bool>> Vis;
  
  const vector<Dir> Direc = {Down, Right, Up, Left};
  const vector<Dir> Direc2 = {Left, Down, Right, Up};
  const vector<Dir> Direc3 = {Up, Left, Down, Right};

  //const int X[4] = {-1, 0, 1, 0};
  //const int Y[4] = {0, -1, 0, 1};

  ////////////// Funcions útils //////////////
  bool winning() {
    for (int pl = 0; pl < num_players(); ++pl)
      if (pl != me() and score(me()) <= score(pl))
        return false;
    return true;
  }

  void iniPosProhibidas(SetPos& prohibido, Vec& W, Vec& S, Vec& Q) {
    // Afegim pos. inicial workers
    for (int k = 0; k < int(W.size()); ++k) {
      Ant worker = ant(W[k]); // Treballador
      prohibido.insert(worker.pos);
    }
    // Afegim pos. inicial soldiers
    for (int k = 0; k < int(S.size()); ++k) {
      Ant soldier = ant(S[k]); // Soldat
      prohibido.insert(soldier.pos);
    }
    // Afegim pos. inicial queen
    Ant queen = ant(Q[0]); // Reina
    prohibido.insert(queen.pos);
  }

  // Diu si un worker o soldier es troben al costat de la reina
  bool royalArea(Pos p, Pos pQ) {
    for (int k = 0; k < 4; ++k) {
      if (pos_ok(pQ + Direc[k]) and p == pQ + Direc[k]) return true;
      for (int j = 0; j < 4; ++j) {
        if (pos_ok((pQ + Direc[k]) + Direc2[j]) and p == pQ + Direc[k] + Direc2[j]) return true;
      }
    }
    return false;
  }

  bool closeToQueen(Pos p, Pos pQ) {
    for (int k = 0; k < 4; ++k) {
      if (pos_ok(pQ + Direc[k]) and p == pQ + Direc[k]) return true;
      for (int j = 0; j < 4; ++j) {
        if (pos_ok((pQ + Direc[k]) + Direc2[j]) and p == pQ + Direc[k] + Direc2[j]) return true;
        for (int w = 0; w < 4; ++w) {
          if (pos_ok((pQ + Direc[k]) + Direc2[j] + Direc3[w]) and p == pQ + Direc[k] + Direc2[j] + Direc3[w]) return true;
        }
      }
    }
    return false;
  }

  // Indica si l'id d'una formiga és un treballador del teu jugador o no
  bool notMyTeam(int id, Vec& W) {
    return ant(id).player != me();
  }

  // BFS per a què el worker trobi la posició del bonus més proper
  Pos searchBonus(Ant a, Pos pQ, Vis& V, Board& B, SetPos& prohibido) {
    Pos ini = a.pos;
    queue<Pos> q;
    q.push(a.pos);
    V[ini.i][ini.j] = true;
    while (not q.empty()) {
      Pos p = q.front();
      q.pop();
      for (int k = 0; k < 4; ++k) {
        Pos xy = p + Direc[k];
        if (pos_ok(xy)) {
          if (cell(xy).type != Water and cell(xy).id == -1 and not V[xy.i][xy.j] and prohibido.find(xy) == prohibido.end()) {
              q.push(xy);
              V[xy.i][xy.j] = true;
              B[xy.i][xy.j] = Direc[k];
              if (cell(xy).bonus != None and not royalArea(xy, pQ)) return xy;
          }
        }
      }
    }
    return a.pos; // es queda quieta
  }

  // BFS per a què la reina trobi bonus més proper
  Pos searchBonusQueen(Ant a, Vis& V, Board& B, SetPos& prohibido) {
    Pos ini = a.pos;
    queue<Pos> q;
    q.push(a.pos);
    V[ini.i][ini.j] = true;
    while (not q.empty()) {
      Pos p = q.front();
      q.pop();
      for (int k = 0; k < 4; ++k) {
        Pos xy = p + Direc[k];
        if (pos_ok(xy)) {
          if (cell(xy).type != Water and cell(xy).id == -1 and not V[xy.i][xy.j] and prohibido.find(xy) == prohibido.end()) {
            q.push(xy);
            V[xy.i][xy.j] = true;
            B[xy.i][xy.j] = Direc[k];
            if (cell(xy).bonus != None) return xy;
          }
        }
      }
    }
    return a.pos; // es queda quieta
  }

  // BFS per trobar la posició proper a reina i saber el camí
  Pos searchQueen(Pos pW, Pos pQ, Vis& V, Board& B, SetPos& prohibido) {
    queue<Pos> q;
    q.push(pW);
    V[pW.i][pW.j] = true;
    while (not q.empty()) {
      Pos p = q.front();
      q.pop();
      for (int k = 0; k < 4; ++k) {
        Pos xy = p + Direc[k];
        if (pos_ok(xy)) {
          if (cell(xy).type != Water and cell(xy).id == -1 and not V[xy.i][xy.j] and prohibido.find(xy) == prohibido.end()) {
            q.push(xy);
            V[xy.i][xy.j] = true;
            B[xy.i][xy.j] = Direc[k];
            if (cell(xy).bonus == None and royalArea(xy, pQ)) return xy;
          }
        }
      }
    }
    return pW; // es queda quieta
  }

  // BFS per trobar la posició dels treballadors enemics
  Pos searchEnemy(Pos pS, Vis& V, Board& B, SetPos& prohibido, Vec& W) {
    queue<Pos> q;
    q.push(pS);
    V[pS.i][pS.j] = true;
    while (not q.empty()) {
      Pos p = q.front();
      q.pop();
      for (int k = 0; k < 4; ++k) {
        Pos xy = p + Direc[k];
        if (pos_ok(xy)) {
          Cell c = cell(xy);
          if (c.type != Water and not V[xy.i][xy.j] and prohibido.find(xy) == prohibido.end()) {
           if(c.id == -1) {
              q.push(xy);
              V[xy.i][xy.j] = true;
              B[xy.i][xy.j] = Direc[k];
            }
            if (c.id != -1 and ant(c.id).type == Worker and notMyTeam(c.id, W)) {
              B[xy.i][xy.j] = Direc[k];
              return xy;
            }
          }
        }
      }
    }
    return pS; // es queda quieta
  }


  Dir revers(Dir d) {
    if (d == Up) return Down;
    else if (d == Down) return Up;
    else if (d == Left) return Right;
    return Left;
  }

  Dir goTo(Pos orig, Pos dest, const Board& B) { // orig --> Origen // dest --> Dest
    if (orig + B[dest.i][dest.j] == dest) {
      return B[dest.i][dest.j];
    } else {
        Dir contr = revers(B[dest.i][dest.j]);
        return goTo(orig, dest + contr, B);
    }
  }

  //////////////////////////////////////////////////// WORKER ////////////////////////////////////////////////////
  void moveOneWorker(int idW, int idQ, SetPos& prohibido) {
    Ant worker = ant(idW); // Treballador
    Pos pW = worker.pos;
    Ant queen = ant(idQ); // Reina
    Pos pQ = queen.pos;
    //cerr << "abans if" << endl;
    if (worker.life < 2 and closeToQueen(pW, pQ)) {
        leave(idW);
        //cerr << "despres if" << endl;
    }
    else if (worker.bonus == None and cell(pW).bonus != None and not royalArea(pW, pQ)) { // No carregat a pos. bonus --> agafar
      take(idW);
    }
    else if (worker.bonus == None) { //} and (cell(pW).bonus == None or royalArea(pW, pQ))) { // No carregat a pos. buida --> anar a pBonus
      Vis V(board_rows(), vector<bool>(board_cols(), false));
      Board B(board_rows(), vector<Dir>(board_cols()));
      Pos pBonus = searchBonus(worker, pQ, V, B, prohibido);
      //cerr << "-----------------------------  Bonus " << pBonus << " Ant " << pW << endl;
      if (pBonus != pW) {
        Dir direction = goTo(pW, pBonus, B);
        if (prohibido.find(pW + direction) == prohibido.end()) {
          prohibido.insert(pW + direction);
          move(idW, direction);
        }
      }
    }
    else if (worker.bonus != None and not royalArea(pW, pQ)) { // Carregat a pos. ara buida --> anar a pQ
      Vis V(board_rows(), vector<bool>(board_cols(), false));
      Board B(board_rows(), vector<Dir>(board_cols()));
      Pos pRoyalArea = searchQueen(pW, pQ, V, B, prohibido);
      if (pRoyalArea != pW) {
        Dir direction = goTo(pW, pRoyalArea, B);
        if (prohibido.find(pW + direction) == prohibido.end()) {
          prohibido.insert(pW + direction);
          move(idW, direction);
        }
      }
    } 
    else if (worker.bonus != None and royalArea(pW, pQ)) { // Carregat a pos. zona reial --> deixar bonus
      leave(idW);
      prohibido.insert(pW);
    }
  }

  void moveWorkers(Vec& W, Vec& Q, SetPos& prohibido) {
    //cerr << "XXXXXXX" << endl;
    //if (Q.empty()) cerr << "empty" << endl;
    //else cerr << "full" << endl;
    int idQ = 0;
    if (not Q.empty()) idQ = Q[0]; // només hi ha 1 reina

    for (int i = 0; i < int(W.size()); ++i) {
      int idW = W[i];
      //cerr << "YYYYYY" << endl;
      moveOneWorker(idW, idQ, prohibido);
    }
  }

  //////////////////////////////////////////////////// SOLDIER ////////////////////////////////////////////////////
  void moveOneSoldier(int idS, SetPos& prohibido, Vec& W) {
    Ant soldier = ant(idS);
    Pos pS = soldier.pos;

    Vis V(board_rows(), vector<bool>(board_cols(), false));
    Board B(board_rows(), vector<Dir>(board_cols()));
    Pos pEnemy = searchEnemy(pS, V, B, prohibido, W);
    //cerr << "-----------------------------  Bonus " << pEnemy << " Soldier " << pS << endl;
    if (pEnemy != pS) {
      Dir direction = goTo(pS, pEnemy, B);
      if (prohibido.find(pS + direction) == prohibido.end()) {
        prohibido.insert(pS + direction);
        move(idS, direction);
      }
    }
  }

  void moveSoldiers(Vec& W, Vec& S, SetPos& prohibido) {
    for (int i = 0; i < int(S.size()); ++i) {
      int idS = S[i];
      moveOneSoldier(idS, prohibido, W);
    }
  }

  //////////////////////////////////////////////////// QUEEN ////////////////////////////////////////////////////
  bool layWhat(Vec& W, Vec& S) { // true -> lay worker
    if (W.size() <= 3) return true;
    else if (S.size() < 2) return false;
    return true;
  }

  void moveQueen(Vec& Q, Vec& W, Vec& S, SetPos& prohibido) {
    int idQ = Q[0];
    Ant queen = ant(idQ);
    Pos p = queen.pos;
    bool layWorker = layWhat(W, S);
    // Ou de treballador
    if (layWorker and queen.reserve[Carbohydrate] >= worker_carbo() and queen.reserve[Protein] >= worker_prote() and queen.reserve[Lipid] >= worker_lipid()) {
      for (int k = 0; k < 4; ++k) {
        if (pos_ok(p + Direc[k])) {
          Cell c = cell(p + Direc[k]);
          if (c.type != Water and c.id == -1 and c.bonus == None) {
            lay(idQ, Direc[k], Worker);
          }
        }
      }
    }
    // Ou de soldat
    else if (not layWorker and queen.reserve[Carbohydrate] >= soldier_carbo() and queen.reserve[Protein] >= soldier_prote() and queen.reserve[Lipid] >= soldier_lipid()) {
      for (int k = 0; k < 4; ++k) {
        if (pos_ok(p + Direc[k])) {
          Cell c = cell(p + Direc[k]);
          if (c.type != Water and c.id == -1 and c.bonus == None) {
            lay(idQ, Direc[k], Soldier);
          }
        }
      }
    }
    // Buscar bonus
    else if (round() % queen_period() == 0){
      bool found = false;
      for (int k = 0; k < 4; ++k) {
        if (pos_ok(p + Direc[k])) {
          Cell c = cell(p + Direc[k]);
          if (c.id != -1 and ant(c.id).player != me()) {
            prohibido.insert(p + Direc[k]);
            move(idQ, Direc[k]);
            found = true;
          }
        }
      }
      if (not found) {
        Vis V(board_rows(), vector<bool>(board_cols(), false));
        Board B(board_rows(), vector<Dir>(board_cols()));
        Pos pBonus = searchBonusQueen(queen, V, B, prohibido);
        //cerr << "-----------------------------  Bonus " << pBonus << " Ant " << p << endl;
        if (pBonus != p) {
          Dir direction = goTo(p, pBonus, B);
          if (prohibido.find(p + direction) == prohibido.end()) {
            prohibido.insert(p + direction);
            move(idQ, direction);
          }
        }
      }
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    int idMe = me();
    Vec W = workers(idMe);
    Vec S = soldiers(idMe);
    Vec Q = queens(idMe);
    SetPos prohibido; // Posicions on les formigues no poden passar perquè ja n'hi ha una altra
    //iniPosProhibidas(prohibido, W, S, Q);
    moveWorkers(W, Q, prohibido);
    //cerr << 'W' << endl;
    moveSoldiers(W, S, prohibido);
    //cerr << 'S' << endl;
    if (not Q.empty()) moveQueen(Q, W, S, prohibido);
    //cerr << 'Q' << endl;
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
