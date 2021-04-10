#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/defines.h"

#define GRID 14

using namespace std;

void generateRand(string fname) {
  ofstream file("../examples/" + fname + ".csv");

  for(int i = 0; i < GRID; i++) {
    for(int j = 0; j < GRID; j++) {
      int num = rand() % 6;
      file << num << ",";
    }
    file << "\n";
  }
  file.close();
}

void generateUser(string fname) {
  ofstream file("../examples/" + fname + ".csv");

  for(int i = 0; i < GRID; i++) {
    for(int j = 0; j < GRID; j++) {
      int num;
      cin >> num;
      file << num << ",";
    }
    file << "\n";
  }
  file.close();
}


int main(int argc, char* argv[]) {
  if(argc < 3) {
    return 0;
  }

  srand(time(NULL));

  if(!string(argv[1]).compare("r")) {
    generateRand(argv[2]);
  } else {
    generateUser(argv[2]);
  }
  return 0;
}