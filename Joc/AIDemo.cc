#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Demo

// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.

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

  const vector<NutrientType> nutrients = { Carbohydrate, Protein, Lipid };


  // Default direction to be used during all match.
  Dir default_dir;
  

  // Returns true if winning.
  bool winning() {
    for (int pl = 0; pl < num_players(); ++pl)
      if (pl != me() and score(me()) <= score(pl))
        return false;
    return true;
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

    // Take a random direction as default direction.
    if (round() == 0) {
      default_dir = Dir(random(0, 3));
    }
    
    // If more than halfway through, do nothing.
    if (round() > num_rounds()/2) return;

    // If winning, do nothing.
    if (winning()) return;

    // If nearly out of time, do nothing.
    double st = status(me());
    if (st >= 0.9) return;

    // Write debugging messages, e.g., info related to queen of player 1 (if it exists).
    vector<int> queen1_ids = queens(1);
    if (not queen1_ids.empty()) {
      Ant queen1 = ant(queen1_ids[0]);
      cerr << "Data of queen of player 1"    << endl;
      cerr << "Type     : " << queen1.type   << endl; // This should print 'Queen'!
      cerr << "Id       : " << queen1.id     << endl;
      cerr << "Player   : " << queen1.player << endl; // This should print '1'!
      cerr << "Position : " << queen1.pos    << endl;
      cerr << "Bonus    : " << queen1.bonus  << endl; // This should print 'None'!
      for (NutrientType n : nutrients)
        cerr << "Reserve of " << n << ": " << queen1.reserve[n] << endl;
    }

    // Write debugging messages, e.g., the matrix of id's.
    for (int i = 0; i < board_rows(); ++i) {
      for (int j = 0; j < board_cols(); ++j) {
        cerr << cell(i, j).id <<  "\t";
      }
      cerr << endl;
    }

    if (random(0, 3)) { // Do the following with probability 0.75
      vector<int> my_soldier_ids = soldiers(me());
      if (not my_soldier_ids.empty()) {
        int soldier_id = my_soldier_ids[random(0, my_soldier_ids.size()-1)]; // Take a random soldier of mine.
        move(soldier_id, default_dir);                                       // Move soldier along default direction.
      }
    }

    // Command my workers in random order.
    vector<int> my_worker_ids = workers(me());
    vector<int> perm = random_permutation(my_worker_ids.size());
    for (int k = 0; k < int(perm.size()); ++k) {
      int worker_id = my_worker_ids[perm[k]];
      Ant worker = ant(worker_id);
      Pos p = worker.pos;
      Cell c = cell(p);
      if           (c.bonus != None)  take(worker_id);     // More checks should be done here...
      else if (worker.bonus != None) leave(worker_id);     // More checks should be done here...
      else {
        Pos q = p + Up;
        if (pos_ok(q) and cell(q).type != Water and cell(q).id == -1)
          move(worker_id, Up); // Move up if not water and no ant is there.
      }
    }

    vector<int> my_queen_ids = queens(me());
    if (not my_queen_ids.empty()) {
      int queen_id = my_queen_ids[0];
      if (random(0, 1)) lay(queen_id, Right, Soldier);  // Try to lay an egg of a soldier on the cell on the right.
      else              lay(queen_id,  Left,  Worker);  // Try to lay an egg of a worker  on the cell on the left.
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
