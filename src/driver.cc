#include <ctime>
#include <fstream>
#include <iostream>

#include "constants.hpp"
#include "group.hpp"

/*Write your main driver in this file! Remember to seperate
out things into functions to help with readability and reusability.

See specifications for how to get started and
go to office hours if you need help!*/

// const int kSizeGroups = 5;
// const unsigned int kMaxIterations = 1000000;

// const double kMinAvgBuildingExp = 5;
// const int kMinReturning = 1;
// const double kMinAvgStamina = 5;

std::vector<string> Split(string strin) {
  std::vector<string> words;
  std::string str1;
  std::string sname;
  unsigned long i = 0;
  while (i < strin.size()) {
    if (strin.at(i) != ' ') {
      str1.push_back(strin.at(i));
      i++;
    } else {
      i++;
      if (str1.empty()) continue;
      words.push_back(str1);
      str1.clear();
    }
  }
  if (!str1.empty()) words.push_back(str1);
  return words;
}
int IsNumber(string strin) {
  unsigned long i = 0;
  int isnum = 1;
  while (i < strin.size()) {
    if (strin.at(i) < '0' || strin.at(i) > '9') {
      isnum = 0;
      break;
    }
    i++;
  }
  return isnum;
}
const int kReadlinesize=100;
void Readvolfromfile(std::fstream &ifs, std::vector<Volunteer> &vols,std::vector<Group> &grps,int total)
{
  char*   title = new char[kReadlinesize];
  std::string s1;
  std::vector<string> s_volin;
  std::string sname;
  int build_experience = 0;
  int physical_stamina = 0;
  int cnt = 0,cnt1=0;
  bool returning = false;
  do {
    ifs.getline(title, 100);
    s1 = title;
    cnt = s1.size();
    if (cnt != 0) {
      s_volin = Split(s1);
      sname = s_volin[0];
      build_experience = stoi(s_volin[1]);
      physical_stamina = stoi(s_volin[2]);
      if (stoi(s_volin[3]) != 0) {
        returning = true;
      } else {
        returning = false;
      }
      Volunteer *pvol =
          new Volunteer(sname, build_experience, physical_stamina, returning);
      vols.push_back(*pvol);
      cnt1++;
    }
  } while ((cnt != 0) && (cnt1 < total));
  for (int i = 0; i < total / kSizeGroups; i++) {
    Group *pgrp1 = new Group();
    for (int j = 0; j < kSizeGroups; j++) {
      pgrp1->AddVolunteer(vols.back());
      vols.pop_back();
    }
    grps.push_back(*pgrp1);
  }
}
void Adjustgroup(std::vector<Group> &grps)
{
  unsigned int icnt = 0;
  while (icnt++ < kMaxIterations) {
    // find Group pair
    unsigned long index1 = rand() % grps.size();
    unsigned long index2 = rand() % grps.size();
    while (index1 == index2) index2 = rand() % grps.size();
    swap(grps.at(index1).GetRandomVolunteer(),
         grps.at(index2).GetRandomVolunteer());
    bool allfine = true;
    for (auto const& grp : grps) {
      if ((grp.GetAvgBuildingExp() < kMinAvgBuildingExp) ||
          (grp.GetAvgStamina() < kMinAvgStamina) ||
          (grp.GetReturningMembers() < kMinReturning)) {
        allfine = false;
        break;
      }
    }
    if (allfine) break;
  }
}
int main(int argc, char* argv[]) {
  // DO NOT EDIT THIS LINE or add another srand call.
  srand(time(nullptr));
  std::fstream ifs, fsout;
  std::vector<Volunteer> vols;
  int total = 0;
  std::vector<Group> grps;
  std::vector<Group> grpsw;
  if (argc != 4) {
    std::cout << "please input 3 parameters" << std::endl;
    return -1; 
  }
  std::string str1 = argv[2];
  if (IsNumber(str1) == 0) {
    return -1;
  }
  total = stoi(str1);
  ifs.open(argv[1], std::fstream::in);
  if (!ifs.is_open()) return -1;
  Readvolfromfile(ifs,vols,grps,total);
  Adjustgroup(grps);
  for (auto const& grp : grps) {
    if ((grp.GetAvgBuildingExp() >= kMinAvgBuildingExp) &&
        (grp.GetAvgStamina() >= kMinAvgStamina) &&
        (grp.GetReturningMembers() >= kMinReturning)) {
      grpsw.push_back(grp);
    }
  }
  if (!grpsw.empty()) {
    fsout.open(argv[3], std::fstream::out);
    for (auto iter = grps.begin(); iter != grps.end(); iter++) {
      fsout << *iter;
    }
    fsout.close();
  } else
    cout << "No groups founf after maximum iterations." << std::endl;
  ifs.close();
  return 0;
}
