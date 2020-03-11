#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct interval {
  float fIntervalIn;
  float fIntervalOut;
};

struct visitor {
  vector<visitor> vVisitor;
  float fVisitorIn;
  float fVisitorOut;
};

size_t maxCount(vector<visitor>vVisitor, float time1, float time2) {
  size_t count = 0;
  for (int i =0; i < vVisitor.size(); i++)
    if (vVisitor[i].fVisitorIn <= time1 && vVisitor[i].fVisitorOut >= time2)
      count++;
  return count;
}

vector<interval> solution(vector<visitor>vVisitor, vector<float> times) {
  size_t tmp, max = 0;
  float timeTmp;
  interval inter;
  vector<interval> interval, ret;

  for (int i = 1; i < times.size(); i ++) {
    tmp = maxCount(vVisitor, times[i - 1], times[i]);
    if (max <= tmp) {
      if (max < tmp) {
        max = tmp;
        interval.clear();
      }
      inter.fIntervalIn = times[i - 1];
      inter.fIntervalOut = times[i];
      interval.push_back(inter);
    }
  }
  inter.fIntervalIn = interval[0].fIntervalIn;
  inter.fIntervalOut = interval[0].fIntervalOut;
  for (int i = 0; i < interval.size(); i++) {
    if (interval[i].fIntervalOut == interval[i + 1].fIntervalIn) {
      inter.fIntervalOut = interval[i + 1].fIntervalOut;
    } else {
      // cout << inter.fIntervalIn << " " << inter.fIntervalOut << endl;
      ret.push_back(inter);
      interval[i].fIntervalOut = interval[i + 1].fIntervalOut;
      interval[i].fIntervalIn = interval[i + 1].fIntervalIn;
      inter.fIntervalIn = interval[i + 1].fIntervalIn;
      inter.fIntervalOut = interval[i + 1].fIntervalOut;
    }
  }
  return ret;
}

int main(int argc, char **argv) {
  visitor v;
  string line, s, inTmp, outTmp;
  char *in, *out;
  vector<visitor> vVisitor;
  vector<interval> interval;
  vector<float> times;
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
        // bzero(in, lenLayout + 1);
        // bzero(out, lenLayout + 1);
        memset(in, 0, lenLayout + 1);
        memset(out,0, lenLayout + 1);
        strcpy(in, s.substr(0, s.find(" ")).c_str());
        strcpy(out, s.substr(s.find(" ") + 1, strlen(s.c_str())).c_str());
        in[strchr(in, ':') - in] = '.';
        out[strchr(out, ':') - out] = '.';
        v.fVisitorIn = atof(in);
        v.fVisitorOut = atof(out);
        times.push_back(v.fVisitorIn);
        times.push_back(v.fVisitorOut);

        vVisitor.push_back(v);
    }
    f.close();
    sort(times.begin(), times.end());
    // times.erase(unique(times.begin(), times.end()), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());
    interval = solution(vVisitor, times);
    for (int i = 0; i < interval.size(); i++) {
      inTmp = to_string(interval[i].fIntervalIn);
      outTmp = to_string(interval[i].fIntervalOut);
      outTmp.replace(1, outTmp.find("."), ":");
      inTmp.replace(1, inTmp.find("."), ":");
      cout << inTmp.substr(0, inTmp.find(":")+3) << " "
        << outTmp.substr(0, outTmp.find(":")+3) << endl;
    }
  }
  return 0;
}
