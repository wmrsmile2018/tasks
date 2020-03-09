#include "iostream"
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

double Percentile(vector<float> seq, double excelPercentile) {
  size_t len;
  double n, d;
  int k;

  sort(seq.begin(), seq.end());
  len = seq.size();
  n = (len - 1) * excelPercentile + 1;
  if (n == (double)1)
    return seq[0];
  if (n == len)
    return seq[len - 1];
  k = (int)n;
  d = n - k;
  return (seq[k - 1] + d * (seq[k] - seq[k -1]));
}

double max_v (vector<float> seq) {
  return *max_element(seq.begin(), seq.end());
}

double min_v (vector<float> seq) {
  return *min_element(seq.begin(), seq.end());
}

double avarage_v (vector<float> seq) {
  size_t len;

  len = seq.size();
  return accumulate(seq.begin(), seq.end(), 0.0) / len;
}

double median_v (vector<float> seq) {
  return Percentile (seq, 0.5);
}

int main(int argc, char **argv) {
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
    cout << Percentile(seq, 0.9) << endl;
    cout << median_v(seq);
    cout << max_v(seq) << endl;
    cout << min_v(seq) << endl;
    cout << avarage_v(seq) << endl;
}

  return 0;
}
