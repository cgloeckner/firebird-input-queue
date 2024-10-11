#ifndef QTKEYPADBRIDGE_H
#define QTKEYPADBRIDGE_H

#include <QKeyEvent>
#include <QHash>

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
    void setKeypad(unsigned int keymap_id, bool state);
    void keyToKeypad(QKeyEvent *event);

    QHash<int, int> const keymap;
    QHash<int, int> pressed_keys;
};

extern QtKeypadBridge qt_keypad_bridge;

#endif // QTKEYPADBRIDGE_H
