#ifndef QTKEYPADBRIDGE_H
#define QTKEYPADBRIDGE_H

#include <QKeyEvent>
#include <QTimer>

#include <set>
#include <map>

#include "keymap.h"

using Actions = std::list<unsigned int>; // arrangement of emulated keypad actions

namespace padmap {
    // as continuation of the keymap, so the int can be distinguished from keymap actions
    enum {
        PAD_LEFT = keymap::ROWS * keymap::COLS + 1,
        PAD_RIGHT,
        PAD_UP,
        PAD_DOWN
    };
}


inline int sgn(int val) constexpr { return (0 < val) - (val < 0); }


/* This class is used by every Widget which wants to interact with the
 * virtual keypad. Simply call QtKeypadBridge::keyPressEvent or keyReleaseEvent
 * to relay the key events into the virtual calc. */

class QtKeypadBridge : public QObject
{
public:
    QtKeypadBridge();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    void setupTimer();
    void processQueue();

    void setTouchpad(int dx, int dy);
    void setKeypad(unsigned int keymap_id, bool state);
    void keyToKeypad(QKeyEvent *event);

    std::set<int> pressed_keys;
    std::map<int, Actions> bind;
    Actions queue;
    
    QTimer *timer;
};

extern QtKeypadBridge qt_keypad_bridge;

#endif // QTKEYPADBRIDGE_H
