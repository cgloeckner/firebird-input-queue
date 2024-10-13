#ifndef QTKEYPADBRIDGE_H
#define QTKEYPADBRIDGE_H

#include <QKeyEvent>
#include <QTimer>

#include <set>
#include <map>

#include "keymap.h"

using ActionList = std::list<unsigned int>; // list of calculator actions (touchpad or keypad)


/* This class is used by every Widget which wants to interact with the
 * virtual keypad. Simply call QtKeypadBridge::keyPressEvent or keyReleaseEvent
 * to relay the key events into the virtual calc. */

class QtKeypadBridge : public QObject
{
public:
    QtKeypadBridge();
    
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    // event handling
    void onKeyPress(QKeyEvent *event);
    void onKeyRelease(QKeyEvent *event);
    void onFocusOut();

    // interfacing with calculator
    void setTouchpad(int dx, int dy);
    void setKeypad(unsigned int keymap_id, bool state);
    
    // queue implementation
    void setupTimer();
    void processQueue();
    
    std::set<int> pressed_keys;
    std::map<int, ActionList> bind;
    ActionList queue;
    
    QTimer *timer;
};


/* Returns the signum (+1 for positive, -1 for negative, 0 for zero) of a number
 */
inline int sgn(int val) { return (0 < val) - (val < 0); }


namespace touchmap {

// as continuation of the keymap, so the int can be distinguished from keymap actions
enum {
    left = keymap::ROWS * keymap::COLS + 1,
    right,
    down,
    up
};

/* Returns true if the given id is realted to touchmap directions rather than keymap stuff.
 */
inline bool matches(int id) { return id >= left; }

}

extern QtKeypadBridge qt_keypad_bridge;

#endif // QTKEYPADBRIDGE_H
