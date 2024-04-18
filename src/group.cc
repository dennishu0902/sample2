#include "group.hpp"

#include <iostream>

#include "volunteer.hpp"

void Group::AddVolunteer(const Volunteer& vol) { myList_.push_back(vol); }

double Group::GetAvgBuildingExp() const {
  double avgexp = 0.0;
  double total = 0.0;
  if (myList_.empty()) return avgexp;

  for (auto const& vol : myList_) {
    total += vol.GetBuildingExperience();
  }
  avgexp = total / static_cast<double>(myList_.size());
  ;
  return avgexp;
}

int Group::GetReturningMembers() const {
  int cnt = 0;
  for (auto const& vol : myList_) {
    if (vol.IsReturning()) cnt += 1;
  }
  return cnt;
}

double Group::GetAvgStamina() const {
  double avgsta = 0.0;
  double total = 0.0;

  if (myList_.empty()) return avgsta;

  for (auto const& vol : myList_) {
    total += vol.GetPhysicalStamina();
  }
  avgsta = total / static_cast<double>(myList_.size());
  return avgsta;
}

Volunteer& Group::GetRandomVolunteer() {
  int i = 0;
  int size = 0;
  i = rand();
  size = myList_.size();
  i = i % size;
  return myList_.at(i);
}