#import "vex.h"
#include <cstddef>
#include <vector> 
#include <iostream>
#include <algorithm>

#ifndef VEXT_GUI_H
#define VEXT_GUI_H

/*-----------------------------------------------------------------------------*/
/** @file    v5_gui.h
 * @brief   
 *
 *//*---------------------------------------------------------------------------*/

namespace vlib {
  enum LayoutType { grid };

class VNode {
  private:
    int lastX, lastY, lastWidth, lastHeight, drawn = false;
    vex::color backgroundColor = vex::color::black;
    VNode *parent;
    LayoutType layout;
  
    std::vector <VNode> children = {};

    void removeChild(VNode node) {
      for(std::vector<VNode>::iterator it = children.begin(); it<children.end();it++) {
        if(&*it == &node) {
         children.erase(it);
        }
      }
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
    bool bounded(int touchX, int touchY, int x, int y, int width, int height) {
      return (touchX >= x && touchY >= y && touchX <= x+width && touchY <= y+height);
    }
    VNode elementAt(int x, int y) {
      vex::brain Brain;
      for(int i = 0; i<children.size();i++) {
        auto it = children[i];
        if(it.drawn && bounded(x, y, it.lastX, it.lastY, it.lastWidth, it.lastHeight)) {
          return children[i];
        }
      }
      return VNode(grid);
    }
    void onPress(int x, int y) {
        vex::brain Brain = vex::brain();
        auto found = elementAt(x, y);
        found.onPress(x,y);
    }
    void onRelease(int x, int y) {
        vex::brain Brain;
        auto found = elementAt(x, y);
        found.onRelease(x,y);
    }
    void render() {
     draw(0,0, 480, 240);
    }
    void draw(int x, int y, int width, int height) {
      vex::brain Brain;

      lastX = x;
      lastY = y;
      lastWidth = width;
      lastHeight = height;
      drawn = true;
      Brain.Screen.setFillColor(backgroundColor);
      Brain.Screen.drawRectangle(x, y, width, height);
      if(children.size() == 1) {
        children.front().draw(x, y, width, height);
      } else {
        int numRows = std::ceil(children.size()/2.0);
        int x = 0;
        int y = 0;
        for(std::vector<VNode>::iterator it = children.begin(); it<children.end();it++) {
          it->draw(x % 2 == 0 ? 0 : 240, y, width/2, 240/numRows);
          if(x%2 == 1) {
            y+=120;
          }
          x++;
        }
      }
    }
  public:
    void add(VNode node) {
      children.push_back(node);
    }

    void remove() {
      if(parent != nullptr) {
        parent->removeChild(*this);
      }
    }
    void setBackground(vex::color color) {
      this->backgroundColor = color;
    }
};
class Button : public VNode {
  protected:
  void onPress(int x, int y) {
    vex::brain Brain;
    Brain.Screen.clearScreen();
    Brain.Screen.print("Button pressed");
    
    VNode::onPress(x, y);
    //do custom action;
    //set background color darker
  }
  void onRelease(int x, int y) {
    VNode::onRelease(x, y);
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

static int redraw() {
  vex::brain Brain;
  Brain.Screen.clearScreen();
  instance().render();
  return 1;
}

public:
  static GUI& instance() {
    static GUI gui;
    return gui;
  }
  static void init() {
    static vex::brain Brain;
    Brain.Screen.pressed([] {
       instance().onPress(Brain.Screen.xPosition(), Brain.Screen.yPosition());
    });

    Brain.Screen.released([] {
      instance().onRelease(Brain.Screen.xPosition(), Brain.Screen.yPosition());
    });
  }
  static void update() {
    static vex::task rendering(redraw);
  }
};

} // namespace vlib

#endif // VLIB_GUI_H