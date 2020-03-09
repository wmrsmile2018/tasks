#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
using namespace std;

bool isExistSlash(char *dir){
  int len;

  len = strlen(dir);
  if (dir[len - 1] == '/')
    return true;
  return false;
}

int maxCongestion(char *dir, char *file) {
  string line, s;
  float val, pos, max = -1, i = 0;

  if (!isExistSlash(dir))
    strcat(dir, "/");
  fstream f(strcat(dir, file));
  if (f.is_open()) {
    while(getline(f, line)) {
      val = stof(line.c_str());
      if (++i && val > max && (pos = i))
        max = val;
    }
    f.close();
  }
    return pos;
}

int main(int argc, char **argv) {
  int input;
  DIR *dir;
  char *file, *path;
  struct dirent *ent;
  const char *files[] = {"Cash1.txt", "Cash2.txt", "Cash3.txt", "Cash4.txt", "Cash5.txt"};
  const char file1[] = "Cash1.txt", file2[] = "Cash2.txt",
    file3[] = "Cash3.txt", file4[] = "Cash4.txt", file5[] = "Cash5.txt";

  if (argc != 2)
    return 1;
  dir  = opendir(argv[1]);
  if(dir) {
    file = new char[strlen("Cash0.txt") + 1];
    path = new char[strlen("Cash0.txt") + strlen(argv[1]) + 1];
      while((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, file1) || !strcmp(ent->d_name, file2)
        || !strcmp(ent->d_name, file3) || !strcmp(ent->d_name, file3)
        || !strcmp(ent->d_name, file4) || !strcmp(ent->d_name, file5)) {
          input = strcmp(ent->d_name, "Cash0.txt");
          bzero(file, strlen("Cash0.txt"));
          bzero(path, strlen("Cash0.txt") + strlen(argv[1]));
          strcpy(path, argv[1]);
          strcpy(file, files[input - 1]);
          cout << maxCongestion(path, file) << endl;
         }
      }
      free(file);
      free(path);
  } else {
      fprintf(stderr, "Error opening directory\n");
  }
    return 0;
}
