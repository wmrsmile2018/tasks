#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

float percentile (vector<float> seq, float percent) {
  int k;
  float n, d;
  size_t len = seq.size();

  sort(seq.begin(), seq.end());
  n = (len - 1) * percent + 1;
  if (n == (double)1)
    return seq[0];
  if (n == len)
    return seq[len - 1];
  k = (int)n;
  d = n - k;
  return (seq[k - 1] + d * (seq[k] - seq[k -1]));
}

double maxValue (vector<float> seq) {
  return *max_element(seq.begin(), seq.end());
}

double minValue (vector<float> seq) {
  return *min_element(seq.begin(), seq.end());
}

double avarageValue (vector<float> seq) {
  size_t len;

  len = seq.size();
  return accumulate(seq.begin(), seq.end(), 0.0) / len;
}

float medianValue (vector<float> seq) {
  return percentile (seq, 0.5);
}

int main (int argc, char **argv) {
  string s, line;
  vector<float> seq;

  if (argc != 2)
    return 1;
  fstream f(argv[1]);
  if (f.is_open()) {
    while(getline(f, line)) {
        s = line.c_str();
        seq.push_back(stof(s));
    }
    f.close();
    if(seq.size() == 0)
      return 1;
    printf("%.2f\n", percentile(seq, 0.9));
    printf("%.2f\n", medianValue(seq));
    printf("%.2f\n", maxValue(seq));
    printf("%.2f\n", minValue(seq) );
    printf("%.2f\n", avarageValue(seq));
  }
  return 0;
}
