#include  "../vex.h"
#ifndef VLIB_AL
#define VLIB_AL

namespace vext {

class AutonType {
  public:
  enum Value : uint8_t
  {
    ONE, FIVE, SETUP, SKILLS, BYPASS
  };

  AutonType() = default;
  constexpr AutonType(Value aA) : value(aA) { }

  operator Value() const { return value; }  // Allow switch and comparisons.
                                            // note: Putting constexpr here causes
                                            // clang to stop warning on incomplete
                                            // case handling.
  explicit operator bool() = delete;        // Prevent usage: if(fruit)

  std::string toString() const { 
    switch(value) {
      case ONE:
        return "1pt";
      case FIVE:
        return "5pt";
      case SETUP:
        return "Setup Auton";
      case SKILLS:
        return "Skills";
      case BYPASS:
        return "Bypassing Auton";
    } 
  }

private:
  Value value;
};

class alliance
{
public:
  enum Value : uint8_t
  {
   RED, BLUE
  };

  alliance() = default;
  constexpr alliance(Value aA) : value(aA) { }

  operator Value() const { return value; }  // Allow switch and comparisons.
                                            // note: Putting constexpr here causes
                                            // clang to stop warning on incomplete
                                            // case handling.
  explicit operator bool() = delete;        // Prevent usage: if(fruit)

  std::string toString() const { return value == RED ? "Red" : "Blue"; }

private:
  Value value;
};
}
#endif
