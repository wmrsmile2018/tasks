#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
using namespace std;

bool isExistSlash(char *dir) {
  int len = strlen(dir);

  return (dir[len - 1] == '/');
}

int maxCongestion(char *dir, char **files, int count, int interval) {
  string line;
  char *s;
  char *filePath = new char[strlen(dir) + 1];
  float avarageQueue[16] = {0};
  float val, pos, max = -1;

  for(int i = 0; i < count; i++) {
    bzero(filePath, strlen(dir) + 1);
    strcpy(filePath, dir);
    fstream f(strcat(filePath, files[i]));
    if (f.is_open()) {
      for(int t = 0; t < interval && getline(f, line); t++) {
        s = new char[line.length() + 1];
        bzero(s, line.length() + 1);
        line.copy(s, line.length(), 0);
        val = stof(s);
        avarageQueue[t] += val;
      }
      f.close();
    }
    for(int t = 0; t < interval; t++) {
      val = avarageQueue[t];
      if (val > max) {
        max = val;
        pos = t + 1;
      }
    }
  }
  free(filePath);
  free(s);
  return pos;
}

int main (int argc, char **argv) {
  DIR *dir;
  size_t lenLayout = strlen("Cash0.txt");
  int input, count = 0;
  char **files, *path = new char[lenLayout + strlen(argv[1]) + 1];
  const char *nameFiles[5] = {"Cash1.txt", "Cash2.txt", "Cash3.txt", "Cash4.txt", "Cash5.txt"};
  struct dirent *ent;

  if (argc != 2)
    return 1;
  dir  = opendir(argv[1]);
  if(dir) {
    files = new char*[5];
    bzero(path, lenLayout + strlen(argv[1]) + 1);
    strcpy(path, argv[1]);
    if (!isExistSlash(path))
      strcat(path, "/");
   // данный цикл необходим для поиска всех файлов типа Cash1.txt ...
   // при этой ожидается, что в папке могут быть и другие файлы
    while((ent = readdir(dir)) != NULL) {
      if (!strcmp(ent->d_name, nameFiles[0]) || !strcmp(ent->d_name, nameFiles[1])
          || !strcmp(ent->d_name, nameFiles[2]) || !strcmp(ent->d_name, nameFiles[3])
          || !strcmp(ent->d_name, nameFiles[4])) {
            input = strcmp(ent->d_name, "Cash0.txt");
            files[input - 1] = new char [lenLayout];
            bzero(files[input - 1], lenLayout);
            strcpy(files[input - 1], ent->d_name);
            count++;
          }
        }
      if (count)
        cout << maxCongestion(path, files, count, 16) << endl;
      free(path);
  } else {
      fprintf(stderr, "Error opening directory\n");
  }
    return 0;
}
