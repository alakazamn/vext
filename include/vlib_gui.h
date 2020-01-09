#import "vex.h"
#include <cstddef>
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
    int lastX, lastY, lastWidth, lastHeight;
    vex::color backgroundColor = vex::color::black;
    VNode *parent;
    LayoutType layout;
  
    std::list <VNode*> children;

    void removeChild(VNode *node) {
      children.remove(node);
    }
  protected:
    template <typename... Args>
    VNode( LayoutType layout) {
      this->layout = layout;
    }
    VNode( vex::color backgroundColor) {
      this->backgroundColor = backgroundColor;
      this->layout = grid;
    }
    bool bounded(int touchX, int touchY, int x, int y, int height, int width) {
      return (touchX >= x && touchY >= y && touchX <= x+width && touchY <= x+height);
    }
    VNode* elementAt(int x, int y) {
      int nodes = children.size();
      auto l_front = children.begin();
      for(int i = 0; i<nodes; i++) {
        std::advance(l_front, 1);
        auto elem = (*l_front);
        if(bounded(x, y, elem->lastX, elem->lastY, elem->lastHeight, elem->lastWidth)) {
          return elem;
        }
      }
      return nullptr;
    }
    void onPress() {
        vex::brain Brain;
        int xPos = Brain.Screen.xPosition();
        int yPos = Brain.Screen.yPosition();
        auto found = elementAt(xPos, yPos);
        if(found != nullptr) {
          found->onPress();
        }
    }
    void onRelease() {
        vex::brain Brain;
        int xPos = Brain.Screen.xPosition();
        int yPos = Brain.Screen.yPosition();
        auto found = elementAt(xPos, yPos);
        if(found != nullptr) {
          found->onRelease();
        }
    }
  public:
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
      lastX = x;
      lastY = y;
      lastWidth = width;
      lastHeight = height;
      vex::brain Brain;
      Brain.Screen.setFillColor(backgroundColor);
      Brain.Screen.drawRectangle(x, y, width, height);
      int nodes = children.size();
      if(nodes == 1) {
        children.front()->render(x, y, width, height);
      } else {
        auto l_front = children.begin();
        for(int i = 0; i<nodes; i++) {
          std::advance(l_front, 1);
          (*l_front)->render(i % 2 == 0 ? 0 : 240, i * 136, width/2, 136);
        }
      }
    }
};
class Button : public VNode {
  protected:
  void onPress() {
    VNode::onPress();
    //do custom action;
    //set background color darker
  }
  void onRelease() {
    VNode::onRelease();
    //do custom action
    //set background color darker
  }
  public:
    template <typename... Args>
    Button(LayoutType layout) : VNode( layout) {

    }
    Button (vex::color backgroundColor) : VNode(backgroundColor) {

    }
};

//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289

class GUI : public VNode {
private: 
  GUI() : VNode(grid) {}

  GUI(LayoutType type) : VNode(type) {}
  ~GUI() {}

  static int renderLoop() {
    while(true) {
      vex::brain Brain;
      Brain.Screen.clearScreen();
      instance().render();
      vex::task::sleep(15);
    }
  }
public:
  static GUI& instance() {
    static GUI gui;
    return gui;
  }
  static vex::task init() {
    vex::brain Brain;
    Brain.Screen.pressed([] {
      instance().onPress();
    });

    Brain.Screen.released([] {
      instance().onRelease();
    });
    static vex::task rendering(renderLoop);
    return rendering;
  }
};

} // namespace vlib

#endif // VLIB_GUI_H