#import "vex.h"
#include <list> 

#ifndef VLIB_GUI_H
#define VLIB_GUI_H

/*-----------------------------------------------------------------------------*/
/** @file    vlib_two.h
 * @brief   VEX provides a class called "motor_group" which allows a programmer
 *          to perform actions on multiple motors together, as if they were one.
 *          This class extends that functionality with actions specific to two
 *          motors, such as turning. It also provides the foundation for something
 *          like a chaindrive. 
 *          Use of the vlib_two class allows for easy controller binding using vlib's
 *          macros (btn or axs, found below).
 *//*---------------------------------------------------------------------------*/

namespace vlib {
  enum LayoutType { grid };

class VNode {
  private:

    vex::color backgroundColor = vex::color::black;
    VNode *parent;
    LayoutType layout;
  
    std::list <VNode*> children;

    void removeChild(VNode *node) {
      children.remove(node);
    }
  
  public:
    template <typename... Args>
    VNode( LayoutType layout) {
      this->layout = layout;
    }
    VNode( vex::color backgroundColor) {
      this->backgroundColor = backgroundColor;
      this->layout = grid;
    }
    void add(VNode *node) {
      children.push_back(node);
    }

    void remove() {
      if(parent != nullptr) {
        parent->removeChild(this);
      }
    }
    void setBackground(vex::color color) {
      this->backgroundColor = color;
    }
    void render() {
      render(0,0, 480, 272);
    }
    void render(int x, int y, int width, int height) {
      vex::brain Brain;
      Brain.Screen.setFillColor(backgroundColor);
      Brain.Screen.drawRectangle(x, y, width, height);
      int nodes = children.size();
      if(nodes == 0) {
        children.front()->render(x, y, width, height);
      } else {
        auto l_front = children.begin();
        for(int i = 0; i<nodes; i++) {
          std::advance(l_front, 1);
          (*l_front)->render(i % 2 == 0 ? 0 : 240, i * 136, width/2, 136);
        }
      }
    }
    void onPress() {
      //need to write method to distribute presses to child elements
    }
    void onRelease() {

    }
};

class GUI : public VNode {
private: 
  static GUI *gui;

  GUI(LayoutType type) : VNode(type) {}
  ~GUI() {}

public:
  static GUI* instance() {
    if(gui == nullptr) {
      //initialize
      GUI newGUI = GUI(grid);
      gui = &newGUI;

      vex::brain Brain;
      Brain.Screen.pressed([] {
        gui->onPress();
      });

      Brain.Screen.released([] {
        gui->onRelease();
      });
    }
    return gui;
  }
};

} // namespace vlib

#endif // VLIB_GUI_H