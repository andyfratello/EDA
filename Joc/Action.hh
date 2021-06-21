#ifndef Action_hh
#define Action_hh

#include "Structs.hh"

struct Command;


/**
 * Class that stores the commands requested by a player in a round.
 */
class Action {

public:

  /**
   * The following functions add a command to the action (= list of commands).
   * They fail if a command is already present for the commanded ant.
   */

  /**
   * Commands ant with identifier id to move following direction dir.
   */
  void move(int id, Dir dir);

  /**
   * Commands worker ant with identifier id to take a bonus.
   */
  void take(int id);

  /**
   * Commands worker ant with identifier id to leave a bonus.
   */
  void leave(int id);

  /**
   * Commands queen ant with identifier id to lay an egg of type t at adjacent
   * cell following direction dir.
   */
  void lay(int id, Dir dir, AntType t);


//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////

  /**
   * Empty constructor.
   */
  Action () : q(0) { }
 
 
private:
  
  friend class Game;
  friend class SecGame;
  friend class Board;

  /**
   * Maximum number of commands allowed for a player during one round.
   */
  static const int MAX_COMMANDS = 1000;

  /**
   * Number of commands tried so far.
   */
  int q;
  
  /**
   * Set of ants that have already performed a command.
   */
  set<int> u;

  /**
   * List of commands to be performed during this round.
   */
  vector<Command> v;

  /**
   * Read/write commands to/from a stream.
   */
  Action (istream& is);
  static void print (const vector<Command>& commands, ostream& os);

  void execute(const Command& m);
  
};


/**
 * Class for commands.
 */
struct Command {

  int id;      // Identifier of the commanded ant.
  int c_type;  // Type of command.
  int dir;     // If c_type == Move, direction of movement;
  // if c_type == Lay,  direction to cell where egg is to be laid;
  // otherwise, -1.
  int a_type;  // If c_type == Lay, type of ant; otherwise, -1.

  /**
   * Constructor with all defining fields.
   */
  Command (int id, int c_type, int dir, int a_type) :
    id(id), c_type(c_type), dir(dir), a_type(a_type) { }
};


inline void Action::move(int id, Dir dir) {
  execute(Command(id, Move, int(dir), -1));
}

inline void Action::take(int id) {
  execute(Command(id, Take, -1, -1));
}

inline void Action::leave(int id) {
  execute(Command(id, Leave, -1, -1));
}

inline void Action::lay(int id, Dir dir, AntType t) {
  execute(Command(id, Lay, int(dir), int(t)));
}

inline void Action::execute(const Command& m) {

  ++q;
  _my_assert(q <= MAX_COMMANDS, "Too many commands.");  
  
  if (u.find(m.id) != u.end()) {
    cerr << "warning: command already requested for ant " << m.id << endl;
    return;
  }
  u.insert(m.id);
  v.push_back(m);
}

#endif
