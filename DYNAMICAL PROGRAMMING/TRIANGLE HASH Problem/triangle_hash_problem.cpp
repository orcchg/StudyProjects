#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <stdio.h>
using std::vector;
using std::list;
using std::sort;

//-----------------------------------------------------------------------------
class CTriangle {
  public:
    CTriangle() {
      sides.resize(3, 0);
    }
    CTriangle(const CTriangle& rhs):sides(rhs.sides) {}
    void canonize();
    vector<int> sides;
 
    bool operator == (const CTriangle& rhs) const {
      return (sides == rhs.sides);
    }
    bool operator != (const CTriangle& rhs) const {
      return (sides != rhs.sides);
    }

  private:
    int gcd();
    int gcd(int m_value, int n_value) const;
    void sorting();
};

int CTriangle::gcd(int m_value, int n_value) const {
  int m_changeable = m_value;
  int n_changeable = n_value;
  while (m_changeable > 0 && n_changeable > 0) {
    if (m_changeable >= n_changeable) {
      m_changeable %= n_changeable;
    } else {
      n_changeable %= m_changeable;
    }
  }
  if (m_changeable == 0) {
    return n_changeable;
  }
  if (n_changeable == 0) { 
    return m_changeable;
  }
}

void CTriangle::sorting() {
  sort(this->sides.begin(), this->sides.end());
}

int CTriangle::gcd() {
  sorting();
  return gcd(gcd(sides.at(0), sides.at(1)), sides.at(2));
}

void CTriangle::canonize() {
  int HOD = gcd();
  for (int index = 0; index < 3; ++index) {
    sides.at(index) /= HOD;
  }
}

//-----------------------------------------------------------------------------
void input(int& length, vector<CTriangle>* triangles) {
  scanf("%ld", &length);
  triangles->resize(length);
  for (int index = 0; index < length; ++index) {
    scanf("%ld %ld %ld", &triangles->at(index).sides.at(0),
        &triangles->at(index).sides.at(1),
        &triangles->at(index).sides.at(2));
    triangles->at(index).canonize();
  }
}

//-----------------------------------------------------------------------------
bool is_absent(const list<CTriangle>& chains, CTriangle item) {
  for (list<CTriangle>::const_iterator it = chains.begin();
       it != chains.end();
       ++it) {
    if (*it == item) {
      return false;
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
int hashTableCreation(int length, const vector<CTriangle>& triangles) {
  const int PRIME_NUMBER = 27644437;
  const int hash_size = 50007;
  int result = 0;
  int random_value = static_cast<int>(
      static_cast<double>(rand()) / RAND_MAX * (PRIME_NUMBER - 1) + 1);
  vector<int> bucket_counter(hash_size, 0);
  vector<list<CTriangle> > chains(hash_size);
  for (int bucket = 0; bucket < triangles.size(); ++bucket) {
    int hash_value = (abs(
        triangles[bucket].sides[0] % PRIME_NUMBER +
        triangles[bucket].sides[1] * random_value % PRIME_NUMBER + 
        triangles[bucket].sides[2] * random_value % PRIME_NUMBER * random_value % PRIME_NUMBER)
        ) % hash_size;
    if (is_absent(chains[hash_value], triangles[bucket])) { 
      chains[hash_value].push_back(triangles[bucket]);
      ++result;
    }
  }
  return result;
}

//-----------------------------------------------------------------------------
int main() {
  srand(239);
  int length;
  vector<CTriangle> triangles;
  input(length, &triangles);
  printf("%d", hashTableCreation(length, triangles));
  return 0;
}


