#ifndef GROUP_HPP
#define GROUP_HPP
#include <ostream>
#include <vector>

#include "volunteer.hpp"
using namespace std;
class Group {
public:
  void AddVolunteer(const Volunteer& vol);

  double GetAvgBuildingExp() const;

  int GetReturningMembers() const;

  double GetAvgStamina() const;

  friend std::ostream& operator<<(std::ostream& os, const Group& g_in) {
    os << "Group:";
    os << " AvgBuildingExp ";
    os << g_in.GetAvgBuildingExp();
    os << " GetAvgStamina ";
    os << g_in.GetAvgStamina();
    os << std::endl;
    for (auto vol : g_in.myList_) {
      os << vol.GetName() << std::endl;
    }
    os << std::endl;
    return os;
  }

  Volunteer& GetRandomVolunteer();

private:
  // TODO create private member variable(s)
  std::vector<Volunteer> myList_;
};

#endif
