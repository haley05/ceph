#ifndef __MDS_TYPES_H
#define __MDS_TYPES_H

#include <sys/types.h>
#include <ext/hash_map>
#include <string>
#include <set>
#include <iostream>
using namespace std;



// -- stl crap --

namespace __gnu_cxx {
  template<> struct hash<unsigned long long> {
	size_t operator()(unsigned long long __x) const { return __x; }
  };
  
  template<> struct hash< std::string >
  {
    size_t operator()( const std::string& x ) const
    {
      return hash< char >()( (x.c_str())[0] );
    }
  };
}


// -- raw inode --

typedef __uint64_t inodeno_t;   // ino

typedef __uint64_t mdloc_t;     // dir locator?

struct inode_t {
  inodeno_t ino;   // NOTE: this must come first

  __uint32_t touched;
  __uint64_t size;
  __uint32_t mode;
  uid_t uid;
  gid_t gid;
  time_t atime, mtime, ctime;
  char isdir; // normal = 1, hashed = 2, file = 0
};

#define INODE_DIR_NORMAL 1
#define INODE_DIR_HASHED 2


typedef __uint64_t object_t;


// -- load balancing stuff --

// popularity
#define MDS_POP_ANY     0
#define MDS_POP_SOFTRD  1
#define MDS_POP_SOFTWR  2
#define MDS_POP_HARDRD  3
#define MDS_POP_HARDWR  4
#define MDS_NPOP        5

class mds_load_t {
 public:
  double root_pop;
  double req_rate, rd_rate, wr_rate;
  double cache_hit_rate;
  
  mds_load_t() : 
	root_pop(0), req_rate(0), rd_rate(0), wr_rate(0), cache_hit_rate(0) { }
	
};



// -- io helpers --

inline ostream& operator<<(ostream& out, set<int>& iset) {
  for (set<int>::iterator it = iset.begin();
	   it != iset.end();
	   it++) {
	if (it != iset.begin()) out << ",";
	out << *it;
  }
  return out;
}

inline ostream& operator<<(ostream& out, multiset<int>& iset) {
  for (multiset<int>::iterator it = iset.begin();
	   it != iset.end();
	   it++) {
	if (it != iset.begin()) out << ",";
	out << *it;
  }
  return out;
}

#endif
