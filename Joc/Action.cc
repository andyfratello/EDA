//////// STUDENTS DO NOT NEED TO READ BELOW THIS LINE ////////

#include "Action.hh"

Action::Action (istream& is) {
  u.clear();
  v.clear();

  // warning: all read operations must be checked for SecGame.
  int i;
  while (is >> i and i != -1) {
    char c, d, a;
    if (is >> c >> d >> a) {
      u.insert(i);
      v.push_back(Command(i, char2CommandType(c), char2Dir(d), char2AntType(a)));
    }
    else {
      cerr << "warning: only partially read command for ant " << i << endl;
      return;
    }
  }
}

void Action::print (const vector<Command>& commands, ostream& os) {
  for (const Command& com : commands)
    os <<                  com.id       << '\t'
       << CommandType2char(com.c_type)  << '\t'
       <<         Dir2char(com.dir   )  << '\t'
       <<     AntType2char(com.a_type)  << '\t'
       << endl;
  os << -1 << endl;
}
