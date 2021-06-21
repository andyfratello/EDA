#ifndef Structs_hh
#define Structs_hh


#include "Utils.hh"


/**
 * Contains the Dir enumeration,
 * the CommandType enumeration,
 * the Pos struct,
 * the BonusType enumeration,
 * the NutrientType enumeration,
 * the CellType enumeration, the Cell struct,
 * the AntType enumeration, the Ant struct,
 * and some useful little functions.
 */


/**
 * Enum to encode directions.
 */
enum Dir {
  Down, Right, Up, Left
};

inline ostream& operator << (ostream& out, Dir d) {
  switch (d) {
  case Down:   out << "Down";  break;
  case Right:  out << "Right"; break;
  case Up:     out << "Up";    break;
  case Left:   out << "Left";  break;
  default:     out << int(d);  break;
  }
  return out;
}


/**
 * Simple struct to handle positions.
 */
struct Pos {

  int i, j;

  /**
   * Default constructor (0, 0).
   */
  Pos ();
  /**
   * Constructor with all defining fields.
   */
  Pos (int i, int j);

  /**
   * Print operator.
   */
  friend ostream& operator<< (ostream& os, const Pos& p);

  /**
   * Comparison operator.
   */
  friend bool operator== (const Pos& a, const Pos& b);

  /**
   * Comparison operator.
   */
  friend bool operator!= (const Pos& a, const Pos& b);

  /**
   * Comparison operator, mostly needed for sorting.
   */
  friend bool operator< (const Pos& a, const Pos& b);

  /**
   * Increment operator: moves a position according to a direction.
   */
  Pos& operator+= (Dir d);

  /**
   * Addition operator: Returns a position by adding a direction.
   */
  Pos operator+ (Dir d) const;

  /**
   * Increment operator: moves a position according to another position.
   */
  Pos& operator+= (Pos p);

  /**
   * Addition operator: Returns a position by adding another position.
   */
  Pos operator+ (Pos p) const;
};


/**
 * Defines kinds of bonuses.
 */
enum BonusType {
  Bread,
  Seed,
  Leaf,
  None  // No bonus.
};


inline ostream& operator << (ostream& out, BonusType b) {
  switch (b) {
  case Bread:   out << "Bread"; break;
  case Seed:    out << "Seed";  break;
  case Leaf:    out << "Leaf";  break;
  case None:    out << "None";  break;
  default:      out << int(b);  break;    
  }
  return out;
}


/**
 * Defines kinds of nutrients.
 */
enum NutrientType {
  Carbohydrate, // == 0
  Protein,      // == 1
  Lipid         // == 2
};


inline ostream& operator << (ostream& out, NutrientType n) {
  switch (n) {
  case Carbohydrate:  out << "Carbohydrate"; break;
  case Protein:       out << "Protein";      break;
  case Lipid:         out << "Lipid";        break;
  default:            out << int(n);         break;
  }
  return out;
}


/**
 * Defines kinds of cells.
 */
enum CellType {
  Soil,
  Water
};


inline ostream& operator << (ostream& out, CellType c) {
  switch (c) {
  case Soil:  out << "Soil";  break;
  case Water: out << "Water"; break;
  default:    out << int(c);  break;    
  }
  return out;
}


/**
 * Describes a cell on the board, and its contents.
 */
struct Cell {

  CellType   type; // The kind of cell.
  BonusType bonus; // The kind of bonus.
  int          id; // The id of an ant if present, or -1 otherwise.

  /**
   * Default constructor (Soil, None, -1).
   */
  Cell ();

  /**
   * Constructor with all defining fields.
   */
  Cell (CellType t, BonusType b, int i);

};


/**
 * Defines the type of the ant.
 */
enum AntType {
  Queen,
  Soldier,
  Worker 
};


inline ostream& operator << (ostream& out, AntType a) {
  switch (a) {
  case Queen:    out << "Queen";   break;
  case Soldier:  out << "Soldier"; break;
  case Worker:   out << "Worker";  break;
  default:       out << int(a);    break;    
  }
  return out;
}


/**
 * Describes an ant on the board and its properties.
 */
struct Ant {

  AntType type;  // The kind of ant.
  int id;        // The unique id of this ant during the game.
  int player;    // The player that owns this ant.
  Pos pos;       // The position on the board.  
  
  vector<int> reserve; // reserve[i] are the units of nutrient i in the reserve.
                       // reserve[i] == 0 for all i if the ant is not a queen.

  BonusType bonus; // The bonus the ant is carrying.
                   // None if the ant is not a worker.

  int life;
  
  /**
   * Default constructor (Queen, -1, -1, (0, 0), {}, None, INT_MAX).
   */
  Ant ();

  /**
   * Constructor with all defining fields.
   */
  Ant (AntType t, int i, int pl,  Pos p, const vector<int>& r, BonusType b, int l);

};


//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////


/**
 * Enum to encode commands.
 */
enum CommandType {
  Move,
  Take,
  Leave,
  Lay
};


inline ostream& operator << (ostream& out, CommandType c) {
  switch (c) {
  case Move:   out << "Move";  break;
  case Take:   out << "Take";  break;
  case Leave:  out << "Leave"; break;
  case Lay:    out << "Lay";   break;
  default:     out << int(c);  break;
  }
  return out;
}


inline bool dir_ok (Dir dir) {
  return dir >= Down and dir <= Left;
}

inline Pos::Pos (            ) : i(0), j(0) { }
inline Pos::Pos (int i, int j) : i(i), j(j) { }

inline ostream& operator<< (ostream& os, const Pos& p) {
  return os << "(" << p.i << ", " << p.j << ")";
}

inline bool operator== (const Pos& a, const Pos& b) {
  return a.i == b.i and a.j == b.j;
}

inline bool operator!= (const Pos& a, const Pos& b) {
  return not (a == b);
}

inline bool operator< (const Pos& a, const Pos& b) {
  if (a.i != b.i) return a.i < b.i;
  return a.j < b.j;
}

inline Pos& Pos::operator+= (Dir d) {
  switch (d) {
  case Down:   ++i;  break;
  case Right:  ++j;  break;
  case Up:     --i;  break;
  case Left:   --j;  break;
  default: ; // do nothing
  }
  return *this;
}

inline Pos Pos::operator+ (Dir d) const {
  Pos p = *this;
  p += d;
  return p;
}

inline Pos& Pos::operator+= (Pos p) {
    this->i += p.i;
    this->j += p.j;
    return *this;
  }

inline Pos Pos::operator+ (Pos p) const {
    Pos p2 = *this;
    p2 += p;
    return p2;
  }


inline Cell::Cell (                              ) : type(Soil), bonus(None), id(-1) { }
inline Cell::Cell (CellType t, BonusType b, int i) : type(t),    bonus(b),    id(i)  { }


inline bool command_type_ok (CommandType c_type) {
  return c_type >= Move and c_type <= Lay;
}


/**
 * Conversion from command type to char.
 */
inline char CommandType2char (int t) {
  switch (t) {
  case Move:  return 'm';
  case Take:  return 't';
  case Leave: return 'l';
  case Lay:   return 'y';
  default:    return '_';
  }
}


/**
 * Conversion from char to command type.
 */
inline int char2CommandType (char c) {
  switch (c) {
  case 'm': return Move;
  case 't': return Take;
  case 'l': return Leave;
  case 'y': return Lay;
  }
  return -1; // Can't abort: if data were corrupted, master would fail.
}


/**
 * Conversion from direction to char.
 */
inline char Dir2char (int d) {
  switch (d) {
  case Down:   return 'd';
  case Right:  return 'r';
  case Up:     return 'u';
  case Left:   return 'l';
  default:     return '_';
  }
}


/**
 * Conversion from char to direction.
 */
inline int char2Dir (char c) {
  switch (c) {
  case 'd': return Down;
  case 'r': return Right;
  case 'u': return Up;
  case 'l': return Left;
  }
  return -1; // Can't abort: if data is corrupted, master will fail.
}


/**
 * Conversion from bonus to char.
 */
inline char BonusType2char (int f) {
  switch (f) {
  case Bread: return 'b';
  case Seed : return 's';
  case Leaf:  return 'l';
  default:    return 'n';
  }
}


/**
 * Conversion from char to bonus.
 */
inline int char2BonusType (char c) {
  switch (c) {
  case 'b': return Bread;
  case 's': return Seed;
  case 'l': return Leaf;
  case 'n': return None;
  }
  return -1; // Can't abort: if data is corrupted, master will fail.
}


/**
 * Conversion from ant type to char.
 */
inline char AntType2char (int t) {
  switch (t) {
  case Queen:    return 'q';
  case Soldier:  return 's';
  case Worker:   return 'w';
  default:       return '_';
  }
}


/**
 * Conversion from char to ant type.
 */
inline int char2AntType (char c) {
  switch (c) {
  case 'q': return Queen;
  case 's': return Soldier;
  case 'w': return Worker;
  }
  return -1; // Can't abort: if data is corrupted, master will fail.
}


inline Ant::Ant ()
  : type(Queen), id(-1), player(-1), pos(0, 0), reserve(),  bonus(None), life(INT_MAX) { }

inline Ant::Ant (AntType t, int id, int pl, Pos p, const vector<int>& r, BonusType b, int l)
  : type(t),     id(id), player(pl), pos(p),    reserve(r), bonus(b), life(l)    { }


#endif
