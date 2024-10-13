#include "qtkeypadbridge.h"

#include <cassert>

#include "keymap.h"
#include "core/keypad.h"
#include "qmlbridge.h"

/* Constructor that provides bindings between keyboard and a (list of) calculator action(s)
 */
QtKeypadBridge::QtKeypadBridge()
    : timer{nullptr}
{
    // Touchpad controls
    bind[Qt::Key_Left] = {touchmap::left};
    bind[Qt::Key_Right] = {touchmap::right};
    bind[Qt::Key_Down] = {touchmap::down};
    bind[Qt::Key_Up] = {touchmap::up};

    // Touchpad left buttons
    bind[Qt::Key_Escape] = {keymap::esc};
    bind[Qt::Key_End] = {keymap::pad};
    bind[Qt::Key_Tab] = {keymap::tab};

    // Touchpad right buttons
    bind[Qt::Key_Home] = {keymap::on};
    bind[Qt::Key_PageUp] = {keymap::doc};  // Qt::Key_Menu | ALT ?
    bind[Qt::Key_D | Qt::AltModifier] = {keymap::doc};   // conflict, redundant
    bind[Qt::Key_PageDown] = {keymap::menu};  // Qt::Key_Menu ?
    bind[Qt::Key_M | Qt::AltModifier] = {keymap::menu};   // conflict, redundant

    // Touchpad bottom buttons
    bind[Qt::Key_Control] = {keymap::ctrl};
    bind[Qt::Key_Shift | Qt::AltModifier] = {keymap::shift};   // ugly workaround
    bind[Qt::Key_Insert] = {keymap::var};
    bind[Qt::Key_V | Qt::AltModifier] = {keymap::var};   // conflict, redundant
    bind[Qt::Key_Backspace] = {keymap::del};
    bind[Qt::Key_Delete] = {keymap::del};

    // Alpha buttons
    bind[Qt::Key_A] = {keymap::aa};
    bind[Qt::Key_B] = {keymap::ab};
    bind[Qt::Key_C] = {keymap::ac};
    bind[Qt::Key_D] = {keymap::ad};
    bind[Qt::Key_E] = {keymap::ae};
    bind[Qt::Key_F] = {keymap::af};
    bind[Qt::Key_G] = {keymap::ag};
    bind[Qt::Key_H] = {keymap::ah};
    bind[Qt::Key_I] = {keymap::ai};
    bind[Qt::Key_J] = {keymap::aj};
    bind[Qt::Key_K] = {keymap::ak};
    bind[Qt::Key_L] = {keymap::al};
    bind[Qt::Key_M] = {keymap::am};
    bind[Qt::Key_N] = {keymap::an};
    bind[Qt::Key_O] = {keymap::ao};
    bind[Qt::Key_P] = {keymap::ap};
    bind[Qt::Key_Q] = {keymap::aq};
    bind[Qt::Key_R] = {keymap::ar};
    bind[Qt::Key_S] = {keymap::as};
    bind[Qt::Key_T] = {keymap::at};
    bind[Qt::Key_U] = {keymap::au};
    bind[Qt::Key_V] = {keymap::av};
    bind[Qt::Key_W] = {keymap::aw};
    bind[Qt::Key_X] = {keymap::ax};
    bind[Qt::Key_Y] = {keymap::ay};
    bind[Qt::Key_Z] = {keymap::az};
    bind[Qt::Key_Less] = {keymap::ee};  // conflict, redundant
    bind[Qt::Key_E | Qt::AltModifier] = {keymap::ee};
    bind[Qt::Key_Bar] = {keymap::pi};
    bind[Qt::Key_Comma] = {keymap::comma};
    bind[Qt::Key_Question] = {keymap::punct};
    bind[Qt::Key_W | Qt::AltModifier] = {keymap::punct};  // conflict, redundant
    bind[Qt::Key_Greater] = {keymap::flag};
    bind[Qt::Key_F | Qt::AltModifier] = {keymap::flag};  // conflict, redundant
    bind[Qt::Key_Space] = {keymap::space};
    bind[Qt::Key_Enter | Qt::AltModifier] = {keymap::ret};  // conflict but not redundant
    bind[Qt::Key_Return | Qt::AltModifier] = {keymap::ret};  // conflict but not redundant

    // Numpad buttons
    bind[Qt::Key_0] = {keymap::n0};
    bind[Qt::Key_1] = {keymap::n1};
    bind[Qt::Key_2] = {keymap::n2};
    bind[Qt::Key_3] = {keymap::n3};
    bind[Qt::Key_4] = {keymap::n4};
    bind[Qt::Key_5] = {keymap::n5};
    bind[Qt::Key_6] = {keymap::n6};
    bind[Qt::Key_7] = {keymap::n7};
    bind[Qt::Key_8] = {keymap::n8};
    bind[Qt::Key_9] = {keymap::n9};
    bind[Qt::Key_Period] = {keymap::dot};
    bind[Qt::Key_Minus | Qt::AltModifier] = {keymap::neg};   // conflict, but not redundant
    bind[Qt::Key_QuoteLeft] = {keymap::neg};  // conflict, redundant, on german layout: [shift]+[2] produces [^2]

    // Left buttons
    bind[Qt::Key_Equal] = {keymap::equ};  // unintuitive
    bind[Qt::Key_Q | Qt::AltModifier] = {keymap::equ};  // conflict, redundant
    bind[Qt::Key_Backslash] = {keymap::trig};  // unintuitive
    bind[Qt::Key_T | Qt::AltModifier] = {keymap::trig};  // conflict, redundant
    bind[Qt::Key_AsciiCircum] = {keymap::pow};
    bind[Qt::Key_P | Qt::AltModifier] = {keymap::pow};  // conflict, redundant
    bind[Qt::Key_At] = {keymap::squ};
    bind[Qt::Key_At | Qt::AltModifier] = {keymap::squ};  // conflict, redundant
    bind[Qt::Key_2 | Qt::AltModifier] = {keymap::squ};
    bind[Qt::Key_BracketLeft] = {keymap::exp};
    bind[Qt::Key_X | Qt::AltModifier] = {keymap::exp};  // conflict, redundant
    bind[Qt::Key_BracketRight] = {keymap::pow10};
    bind[Qt::Key_1 | Qt::AltModifier] = {keymap::pow10};  // conflict, redundant
    bind[Qt::Key_ParenLeft] = {keymap::pleft};
    bind[Qt::Key_F1] = {keymap::pleft};  // unintuitive, redundant
    bind[Qt::Key_ParenRight] = {keymap::pright};
    bind[Qt::Key_F2] = {keymap::pright};  // unintuitive, redundant
    
    // Right buttons
    bind[Qt::Key_Semicolon] = {keymap::metrix};
    bind[Qt::Key_O | Qt::AltModifier] = {keymap::metrix};  // conflict, redundant
    bind[Qt::Key_Apostrophe] = {keymap::cat};
    bind[Qt::Key_C | Qt::AltModifier] = {keymap::cat};  // conflict, redundant
    bind[Qt::Key_Asterisk] = {keymap::mult};
    bind[Qt::Key_A | Qt::AltModifier] = {keymap::mult};  // conflict, redundant
    bind[Qt::Key_Slash] = {keymap::div};
    bind[Qt::Key_F3] = {keymap::div};
    bind[Qt::Key_Plus] = {keymap::plus};
    bind[Qt::Key_Equal | Qt::AltModifier] = {keymap::plus};  // conflict, redundant... maybe because of US-layout? but [Alt]+[=] should already yield [+]
    bind[Qt::Key_Minus] = {keymap::minus};
    bind[Qt::Key_Underscore] = {keymap::minus};
    bind[Qt::Key_Enter] = {keymap::enter};
    bind[Qt::Key_Return] = {keymap::enter};

    // custom
    bind[Qt::Key_Colon] = {keymap::ctrl, keymap::metrix};
    bind[Qt::Key_Exclam] = {keymap::punct, touchmap::right, keymap::enter};
}

/* Entry point for event handling.
 */
bool QtKeypadBridge::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);

    // make sure queue timer is running
    setupTimer();

    switch (event->type())
    {
        case QEvent::KeyPress:
            keyPressEvent(static_cast<QKeyEvent*>(event));
            return true;
        
        case QEvent::KeyRelease:
            keyReleaseEvent(static_cast<QKeyEvent*>(event));
            return true;
        
        case QEvent::FocusOut:
            focusOutEvent(static_cast<QFocusEvent*>(event));
            return false;
        
        default:
            return false;
    }
}

/* Handle key press by setting up an action queue
 */
void QtKeypadBridge::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        // auto-repeat is handled by the calculator itself
        return;
    }
    
    /// FIXME: ask Vogtinator whether using scancodes is required here
    auto host_key = event->key();
    
    /// FIXME: ask Vogtinator why this might be necessary
    if (event->modifiers() & Qt::AltModifier)
    {
        host_key |= Qt::AltModifier; // Compose alt into the unused bit of the keycode
    }

    auto iterator = bind.find(host_key);
    if (iterator == bind.end())
    {
        // nothing was bound to this key
        return;
    }

    // mark host key as being pressed
    pressed_keys.insert(host_key);

    // setup queue of related calculator keys
    queue = iterator->second;
}

void QtKeypadBridge::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        // auto-repeat is handled by the calculator itself
        return;
    }

    /// FIXME: ask Vogtinator whether using scancodes is required here
    auto host_key = event->key();

    auto iterator = pressed_keys.find(host_key);
    if (iterator == pressed_keys.end())
    {
        // nothing to release
        return;
    }

    // trigger release of all calculator keys that are part of that binding
    setTouchpad(0, 0);
    for (auto action: bind[host_key])
    {
        setKeypad(action, false);
    }
 
    // reset queue and mark host key as not being pressed
    queue.clear();
    pressed_keys.erase(iterator);
}

/* Stops all touchpad and keypad actions when losing window focus
 */
void QtKeypadBridge::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);

    setTouchpad(0, 0);
    for (auto host_key: pressed_keys)
    {
        setKeypad(host_key, false);
    }
    pressed_keys.clear();
    queue.clear();
}

/* Handles changing touchpad state where +1 is max, -1 is min and 0 is center position.
 */
void QtKeypadBridge::setTouchpad(int dx, int dy) {
    assert(abs(dx) <= 1);
    assert(abs(dy) <= 1);

    if (sgn(keypad.touchpad_x) == sgn(dx) && sgn(keypad.touchpad_y) == sgn(dy))
    {
        // nothing to change
        return;
    }

    // translate value
    keypad.touchpad_x = TOUCHPAD_X_MAX / 2 + dx * TOUCHPAD_X_MAX / 2;
    keypad.touchpad_y = TOUCHPAD_Y_MAX / 2 + dy * TOUCHPAD_Y_MAX / 2;

    // flag touchpad as changed
    keypad.touchpad_contact = keypad.touchpad_down = dx != 0 || dy != 0;
    the_qml_bridge->touchpadStateChanged();
    keypad.kpc.gpio_int_active |= 0x800;
    keypad_int_check();
}

/* Handles changing keypad state for a keymap_id and a state (pressed if true)
 */
void QtKeypadBridge::setKeypad(unsigned int keymap_id, bool state)
{
    int col = keymap_id % KEYPAD_COLS, row = keymap_id / KEYPAD_COLS;
    assert(row < KEYPAD_ROWS);
    //assert(col < KEYPAD_COLS); Not needed.

    ::keypad_set_key(row, col, state);
    the_qml_bridge->notifyButtonStateChanged(row, col, state);
}

/* Ensures the timer to be set up once. The timer causes the queue to be processed
 */
void QtKeypadBridge::setupTimer()
{
    if (timer == nullptr) {
        // create and connect timer
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &QtKeypadBridge::processQueue);
    }

    if (timer->isActive()) {
        // already running
        return;
    }
    
    timer->start(16); // 16ms = ~60fps
}

/* Processes the next element of the queue, if present. A keypad or touchpad press is triggered.
 */
void QtKeypadBridge::processQueue()
{
    if (queue.empty())
    {
        // nothing to process
        return;
    }

    // dequeue next action
    auto action = queue.front();
    queue.pop_front();

    // handle touchpad movement if specified
    if (touchmap::matches(action))
    {
        if (action == touchmap::left)  { setTouchpad(-1,  0); }
        if (action == touchmap::right) { setTouchpad( 1,  0); }
        if (action == touchmap::down)  { setTouchpad( 0, -1); }
        if (action == touchmap::up)    { setTouchpad( 0,  1); }
        
        // done for now
        return;
    }
    
    // release touchpad
    setTouchpad(0, 0);
    
    // trigger keypad actionisTouch
    setKeypad(action, true);
}

QtKeypadBridge qt_keypad_bridge;
