#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Point {
  float x;
  float y;
};

float isAtRight (Point p1, Point p2, Point p3) {
  float a, b, c;
  a = p1.y - p2.y;
  b = p2.x - p1.x;
  c = p1.x * p2.y - p2.x * p1.y;
  return a * p3.x + b * p3.y + c;
}

bool isEqual (Point p1, Point p2) {
  return (p1.x == p2.x && p1.y == p2.y);
}

float isInTriangle (Point edg1, Point edg2, Point edg3, Point p) {
  float res1, res2;

  res1 = isAtRight(edg1, edg2, p);
  res2 = isAtRight(edg2, edg3, p);
  if (res1 < 0 && res2 < 0)
    return 2; // если под дугой
  if (isEqual(edg1, p) || isEqual(edg2, p) || isEqual(edg3, p))
    return 0; // если лежит на вершине
  if (res1 == 0 || res2 == 0 )
    return 1; // если лежит на стороне
  return 3;
}

int isInRectangle (Point *rec, Point p) {
  int flag1, flag2, flag3, flag4;

  flag1 = isInTriangle(rec[3], rec[0], rec[1], p);
  flag2 = isInTriangle(rec[1], rec[2], rec[3], p);
  flag3 = isInTriangle(rec[2], rec[3], rec[0], p);
  flag4 = isInTriangle(rec[0], rec[1], rec[2], p);
  if (flag1 == 0 || flag2 == 0)
    return 0; // вершина
  if (((flag1 == 1 && flag2 == 2) || (flag2 == 1 && flag1 == 2))
      && ((flag3 == 1 && flag4 == 2) || (flag4 == 1 && flag3 == 2)))
    return 1; // сторона
  if (flag1 == 2 && flag2 == 2)
    return 2; // внутри
  return 3; // снаружи

}

int main (int argc, char **argv) {
  Point rec[4], p;
  string line, s;

  if (argc != 3)
    return 1;
  fstream recP(argv[1]);
  fstream points(argv[2]);
  if (recP.is_open()) { // чтение вершин
    for (int i = 0; getline(recP, line) && i < 4; i ++) {
        s = line.c_str();
        rec[i].x = stof(s.substr(0, s.find(" ")));
        rec[i].y = stof(s.substr(s.find(" "), strlen(s.c_str())));
    }
    recP.close();
    if (points.is_open()) { // чтение точек + проверка точки
      while (getline(points, line)) {
          string s = line.c_str();
          p.x = stof(s.substr(0, s.find(" ")));
          p.y = stof(s.substr(s.find(" "), strlen(s.c_str())));
          cout << isInRectangle(rec, p) << endl;
      }
      points.close();
    }
}
  return 0;
}
