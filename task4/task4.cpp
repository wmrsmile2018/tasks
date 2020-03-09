#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct intensive {
  char *max;
  char *min;
  size_t count;
};

struct visitor {
  char *chIn;
  char *chOut;
  vector<visitor> vVisitor;
  int iIn;
  int iOut;
};

//функция проверяет, пересекаются ли 2 интервала времени
bool intervalExist(visitor v1, visitor v2) {
  if (strcmp(v1.chIn, v2.chOut) < 0 && strcmp(v1.chIn, v2.chIn) <= 0
    && strcmp(v1.chOut, v2.chIn) > 0 && strcmp(v1.chOut, v2.chOut) >= 0)
    return true;
  if (strcmp(v1.chIn, v2.chOut) < 0 && strcmp(v1.chIn, v2.chIn) <= 0
    && strcmp(v1.chOut, v2.chIn) > 0 && strcmp(v1.chOut, v2.chOut) <= 0)
    return true;
  if (strcmp(v1.chIn, v2.chOut) < 0 && strcmp(v1.chIn, v2.chIn) >= 0
    && strcmp(v1.chOut, v2.chIn) > 0 && strcmp(v1.chOut, v2.chOut) >= 0)
    return true;
  if (strcmp(v1.chIn, v2.chOut) < 0 && strcmp(v1.chIn, v2.chIn) >= 0
    && strcmp(v1.chOut, v2.chIn) > 0 && strcmp(v1.chOut, v2.chOut) <= 0)
    return true;
  return false;
}

visitor solution(vector<visitor>vVisitor, size_t lenLayout) {
  char *max, *min, str[] = "12";
  size_t len, count;
  visitor test;

  test.chIn = &str[0];
  test.chIn = &str[1];

  max = new char[lenLayout + 1];
  min = new char[lenLayout + 1];
  count = 0;
  bzero(max, lenLayout + 1);
  bzero(min, lenLayout + 1);
  len = vVisitor.size();

  // for (int i = 0; i < len; i++) {
  //   cout << vVisitor[i].chIn << " " << vVisitor[i].chOut << endl;
  // }
  for (int i = 0; i < len; i++) {
    for (int t = 0; t < len; t++) {
      if(t != i)
        if (intervalExist(vVisitor[i], vVisitor[t]))
          vVisitor[i].vVisitor.push_back(vVisitor[t]);
    }
  }

  for (int i = 0; i < len; i++) {
    strcpy(max, vVisitor[i].chIn);
    strcpy(min, vVisitor[i].chOut);
    for (int t = 0; t < vVisitor[i].vVisitor.size(); t++) {
      if (strcmp(max, vVisitor[i].vVisitor[t].chIn) < 0)
        strcpy(max, vVisitor[i].vVisitor[t].chIn);
      if (strcmp(min, vVisitor[i].vVisitor[t].chOut) > 0)
        strcpy(min, vVisitor[i].vVisitor[t].chOut);
      if (strcmp(max, min) != 0) {

      }
    }
    cout << "max_in  " << max << "  min_out  " << min << endl;
  }

  return test;
}

int main(int argc, char **argv) {
  // visitor v;
  string line, s;
  char *in, *out;
  vector<visitor> vVisitor;
  char layout[] = "00:00";
  size_t lenLayout = strlen(layout);

  if (argc != 2)
    return 1;
  in = new char [lenLayout + 1];
  out = new char [lenLayout + 1];
  fstream f(argv[1]);
  if (f.is_open()) {
  while(getline(f, line)) {
        s = line.c_str();
        bzero(in, lenLayout + 1);
        bzero(out, lenLayout + 1);
        strcpy(in, s.substr(0, s.find(" ")).c_str());
        strcpy(out, s.substr(s.find(" ") + 1, strlen(s.c_str())).c_str());
        in[strchr(in, ':') - in] = '.';
        out[strchr(out, ':') - out] = '.';
        cout << in << " " << out << endl;

        // v.in = new char[lenLayout + 1];
        // v.out = new char[lenLayout + 1];
        // bzero(v.in, lenLayout + 1);
        // bzero(v.out, lenLayout + 1);
        // strcpy(v.in, s.substr(0, s.find(" ")).c_str());
        // strcpy(v.out, s.substr(s.find(" ") + 1, strlen(s.c_str())).c_str());
        // vVisitor.push_back(v);
    }
    f.close();
    // solution(vVisitor, lenLayout);
}
  // free(v.in);
  // free(v.out);
  return 0;
}
