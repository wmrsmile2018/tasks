#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct intensive {
  char *max;
  char *min;
};

struct visitor {
  char *in;
  char *out;
  vector<visitor> vV;
};

//функция проверяет, пересекаются ли 2 интервала времени
bool intervalExist(visitor v1, visitor v2) {
  if (strcmp(v1.in, v2.out) < 0 && strcmp(v1.in, v2.in) <= 0
    && strcmp(v1.out, v2.in) > 0 && strcmp(v1.out, v2.out) >= 0)
    return true;
  if (strcmp(v1.in, v2.out) < 0 && strcmp(v1.in, v2.in) <= 0
    && strcmp(v1.out, v2.in) > 0 && strcmp(v1.out, v2.out) <= 0)
    return true;
  if (strcmp(v1.in, v2.out) < 0 && strcmp(v1.in, v2.in) >= 0
    && strcmp(v1.out, v2.in) > 0 && strcmp(v1.out, v2.out) >= 0)
    return true;
  if (strcmp(v1.in, v2.out) < 0 && strcmp(v1.in, v2.in) >= 0
    && strcmp(v1.out, v2.in) > 0 && strcmp(v1.out, v2.out) <= 0)
    return true;
  return false;
}

visitor solution(vector<visitor>vV, size_t lenLayout) {
  char *max, *min, str[] = "12";
  size_t len, count;

  visitor test;

  test.in = &str[0];
  test.in = &str[1];

  max = new char[lenLayout + 1];
  min = new char[lenLayout + 1];
  count = 0;
  bzero(max, lenLayout + 1);
  bzero(min, lenLayout + 1);
  len = vV.size();

  // for (int i = 0; i < len; i++) {
  //   cout << vV[i].in << " " << vV[i].out << endl;
  // }
  for (int i = 0; i < len; i++) {
    for (int t = 0; t < len; t++) {
      if(t != i)
        if (intervalExist(vV[i], vV[t]))
          vV[i].vV.push_back(vV[t]);
    }
  }

return test;
}


int main(int argc, char **argv) {
  visitor v;
  string line, s;
  vector<visitor> vV;
  size_t lenLayout;
  char layout[] = "00:00";

  if (argc != 2)
    return 1;
  lenLayout = strlen(layout);

  fstream f(argv[1]);
  if (f.is_open()) {
  while(getline(f, line)) {
        s = line.c_str();
        v.in = new char[lenLayout + 1];
        v.out = new char[lenLayout + 1];
        bzero(v.in, lenLayout + 1);
        bzero(v.out, lenLayout + 1);
        strcpy(v.in, s.substr(0, s.find(" ")).c_str());
        strcpy(v.out, s.substr(s.find(" ") + 1, strlen(s.c_str())).c_str());
        vV.push_back(v);
    }
    f.close();
    solution(vV, lenLayout);
}
  free(v.in);
  free(v.out);
  return 0;
}
