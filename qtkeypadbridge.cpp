#include "qtkeypadbridge.h"

#include <iostream>
#include <cassert>
#include "keymap.h"
#include "core/keypad.h"
#include "qmlbridge.h"

QtKeypadBridge::QtKeypadBridge()
{
    bind[Qt::Key_Escape] = {keymap::esc};
    bind[Qt::Key_End] = {keymap::pad};
    bind[Qt::Key_Tab] = {keymap::tab};

    bind[Qt::Key_Home] = {keymap::on};
    bind[Qt::Key_PageUp] = {keymap::doc};
    bind[Qt::Key_D | Qt::AltModifier] = {keymap::doc};
    bind[Qt::Key_PageDown] = {keymap::menu};
    bind[Qt::Key_M | Qt::AltModifier] = {keymap::menu};

    bind[Qt::Key_Control] = {keymap::ctrl};
    bind[Qt::Key_Shift | Qt::AltModifier] = {keymap::shift};
    bind[Qt::Key_Insert] = {keymap::var};
    bind[Qt::Key_V | Qt::AltModifier] = {keymap::var};
    bind[Qt::Key_Backspace] = {keymap::del};
    bind[Qt::Key_Delete] = {keymap::del};

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
    bind[Qt::Key_Less] = {keymap::ee};
    bind[Qt::Key_E | Qt::AltModifier] = {keymap::ee};
    bind[Qt::Key_Bar] = {keymap::pi};
    bind[Qt::Key_Comma] = {keymap::comma};
    bind[Qt::Key_Question] = {keymap::punct};
    bind[Qt::Key_W | Qt::AltModifier] = {keymap::punct};
    bind[Qt::Key_Greater] = {keymap::flag};
    bind[Qt::Key_F | Qt::AltModifier] = {keymap::flag};
    bind[Qt::Key_Space] = {keymap::space};
    bind[Qt::Key_Enter | Qt::AltModifier] = {keymap::ret};
    bind[Qt::Key_Return | Qt::AltModifier] = {keymap::ret};

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
    bind[Qt::Key_Minus | Qt::AltModifier] = {keymap::neg};
    bind[Qt::Key_QuoteLeft] = {keymap::neg};

    bind[Qt::Key_Equal] = {keymap::equ};
    bind[Qt::Key_Q | Qt::AltModifier] = {keymap::equ};
    bind[Qt::Key_Backslash] = {keymap::trig};
    bind[Qt::Key_T | Qt::AltModifier] = {keymap::trig};
    bind[Qt::Key_AsciiCircum] = {keymap::pow};
    bind[Qt::Key_P | Qt::AltModifier] = {keymap::pow};
    bind[Qt::Key_At] = {keymap::squ};
    bind[Qt::Key_At | Qt::AltModifier] = {keymap::squ};
    bind[Qt::Key_2 | Qt::AltModifier] = {keymap::squ};
    bind[Qt::Key_BracketLeft] = {keymap::exp};
    bind[Qt::Key_X | Qt::AltModifier] = {keymap::exp};
    bind[Qt::Key_BracketRight] = {keymap::pow10};
    bind[Qt::Key_1 | Qt::AltModifier] = {keymap::pow10};
    bind[Qt::Key_ParenLeft] = {keymap::pleft};
    bind[Qt::Key_F1] = {keymap::pleft};
    bind[Qt::Key_ParenRight] = {keymap::pright};
    bind[Qt::Key_F2] = {keymap::pright};
    
    bind[Qt::Key_Semicolon] = {keymap::metrix};
    bind[Qt::Key_O | Qt::AltModifier] = {keymap::metrix};
    bind[Qt::Key_Apostrophe] = {keymap::cat};
    bind[Qt::Key_C | Qt::AltModifier] = {keymap::cat};
    bind[Qt::Key_Asterisk] = {keymap::mult};
    bind[Qt::Key_A | Qt::AltModifier] = {keymap::mult};
    bind[Qt::Key_Slash] = {keymap::div};
    bind[Qt::Key_F3] = {keymap::div};
    bind[Qt::Key_Plus] = {keymap::plus};
    bind[Qt::Key_Equal | Qt::AltModifier] = {keymap::plus};
    bind[Qt::Key_Minus] = {keymap::minus};
    bind[Qt::Key_Underscore] = {keymap::minus};
    bind[Qt::Key_Enter] = {keymap::enter};
    bind[Qt::Key_Return] = {keymap::enter};

/*
    : keymap{
            // Touchpad left buttons
        {Qt::Key_Escape, keymap::esc}
        ,{Qt::Key_End, keymap::pad}
        ,{Qt::Key_Tab, keymap::tab}

            // Touchpad right buttons
        ,{Qt::Key_Home, keymap::on}
        ,{Qt::Key_PageUp, keymap::doc}  // Qt::Key_Menu | ALT ?
        ,{Qt::Key_D | Qt::AltModifier, keymap::doc}   // conflict, redundant
        ,{Qt::Key_PageDown, keymap::menu}  // Qt::Key_Menu ?
        ,{Qt::Key_M | Qt::AltModifier, keymap::menu}   // conflict, redundant

            // Touchpad bottom buttons
        ,{Qt::Key_Control, keymap::ctrl}
        ,{Qt::Key_Shift | Qt::AltModifier, keymap::shift}   // ugly workaround
        ,{Qt::Key_Insert, keymap::var}
        ,{Qt::Key_V | Qt::AltModifier, keymap::var}   // conflict, redundant
        ,{Qt::Key_Backspace, keymap::del}
        ,{Qt::Key_Delete, keymap::del}

            // Alpha buttons
        ,{Qt::Key_A, keymap::aa}
        ,{Qt::Key_B, keymap::ab}
        ,{Qt::Key_C, keymap::ac}
        ,{Qt::Key_D, keymap::ad}
        ,{Qt::Key_E, keymap::ae}
        ,{Qt::Key_F, keymap::af}
        ,{Qt::Key_G, keymap::ag}
        ,{Qt::Key_H, keymap::ah}
        ,{Qt::Key_I, keymap::ai}
        ,{Qt::Key_J, keymap::aj}
        ,{Qt::Key_K, keymap::ak}
        ,{Qt::Key_L, keymap::al}
        ,{Qt::Key_M, keymap::am}
        ,{Qt::Key_N, keymap::an}
        ,{Qt::Key_O, keymap::ao}
        ,{Qt::Key_P, keymap::ap}
        ,{Qt::Key_Q, keymap::aq}
        ,{Qt::Key_R, keymap::ar}
        ,{Qt::Key_S, keymap::as}
        ,{Qt::Key_T, keymap::at}
        ,{Qt::Key_U, keymap::au}
        ,{Qt::Key_V, keymap::av}
        ,{Qt::Key_W, keymap::aw}
        ,{Qt::Key_X, keymap::ax}
        ,{Qt::Key_Y, keymap::ay}
        ,{Qt::Key_Z, keymap::az}
        ,{Qt::Key_Less, keymap::ee}
        ,{Qt::Key_E | Qt::AltModifier, keymap::ee}  // conflict, redundant
        ,{Qt::Key_Bar, keymap::pi}
        ,{Qt::Key_Comma, keymap::comma}
        ,{Qt::Key_Question, keymap::punct}
        ,{Qt::Key_W | Qt::AltModifier, keymap::punct}  // conflict, redundant
        ,{Qt::Key_Greater, keymap::flag}
        ,{Qt::Key_F | Qt::AltModifier, keymap::flag}  // conflict, redundant
        ,{Qt::Key_Space, keymap::space}
        ,{Qt::Key_Enter | Qt::AltModifier, keymap::ret}  // conflict but not redundant
        ,{Qt::Key_Return | Qt::AltModifier, keymap::ret}  // conflict but not redundant

            // Numpad buttons
        ,{Qt::Key_0, keymap::n0}
        ,{Qt::Key_1, keymap::n1}
        ,{Qt::Key_2, keymap::n2}
        ,{Qt::Key_3, keymap::n3}
        ,{Qt::Key_4, keymap::n4}
        ,{Qt::Key_5, keymap::n5}
        ,{Qt::Key_6, keymap::n6}
        ,{Qt::Key_7, keymap::n7}
        ,{Qt::Key_8, keymap::n8}
        ,{Qt::Key_9, keymap::n9}
        ,{Qt::Key_Period, keymap::dot}
        ,{Qt::Key_Minus | Qt::AltModifier, keymap::neg}    // conflict, but not redundant
        ,{Qt::Key_QuoteLeft, keymap::neg}

            // Left buttons
        ,{Qt::Key_Equal, keymap::equ}
        ,{Qt::Key_Q | Qt::AltModifier, keymap::equ}  // conflict, redundant
        ,{Qt::Key_Backslash, keymap::trig}
        ,{Qt::Key_T | Qt::AltModifier, keymap::trig}  // conflict, redundant
        ,{Qt::Key_AsciiCircum, keymap::pow}
        ,{Qt::Key_P | Qt::AltModifier, keymap::pow}  // conflict, redundant
        ,{Qt::Key_At, keymap::squ}
        ,{Qt::Key_At | Qt::AltModifier, keymap::squ}  // conflict, redundant
        ,{Qt::Key_2 | Qt::AltModifier, keymap::squ}  // conflict, redundant, on german layout: [shift]+[2] produces [^2]
        ,{Qt::Key_BracketLeft, keymap::exp}  // unintuitive
        ,{Qt::Key_X | Qt::AltModifier, keymap::exp}  // conflict, redundant
        ,{Qt::Key_BracketRight, keymap::pow10}  // unintuitive
        ,{Qt::Key_1 | Qt::AltModifier, keymap::pow10}  // conflict, redundant
        ,{Qt::Key_ParenLeft, keymap::pleft}
        ,{Qt::Key_F1, keymap::pleft}  // unintuitive, redundant
        ,{Qt::Key_ParenRight, keymap::pright}
        ,{Qt::Key_F2, keymap::pright}  // unintuitive, redundant

            // Right buttons
        ,{Qt::Key_Semicolon, keymap::metrix}
        ,{Qt::Key_O | Qt::AltModifier, keymap::metrix}  // conflict, redundant
        ,{Qt::Key_Apostrophe, keymap::cat}
        ,{Qt::Key_C | Qt::AltModifier, keymap::cat}  // conflict, redundant
        ,{Qt::Key_Asterisk, keymap::mult}
        ,{Qt::Key_A | Qt::AltModifier, keymap::mult}  // conflict, redundant
        ,{Qt::Key_Slash, keymap::div}
        ,{Qt::Key_F3, keymap::div}
        ,{Qt::Key_Plus, keymap::plus}
        ,{Qt::Key_Equal | Qt::AltModifier, keymap::plus}  // conflict, redundant... maybe because of US-layout? but [Alt]+[=] should already yield [+]
        ,{Qt::Key_Minus, keymap::minus}
        ,{Qt::Key_Underscore, keymap::minus}
        ,{Qt::Key_Enter, keymap::enter}
        ,{Qt::Key_Return, keymap::enter}
    }
{
    */
    // ...
}

void QtKeypadBridge::setKeypad(unsigned int keymap_id, bool state)
{
    int col = keymap_id % KEYPAD_COLS, row = keymap_id / KEYPAD_COLS;
    assert(row < KEYPAD_ROWS);
    //assert(col < KEYPAD_COLS); Not needed.

    ::keypad_set_key(row, col, state);
    the_qml_bridge->notifyButtonStateChanged(row, col, state);
}

void QtKeypadBridge::keyToKeypad(QKeyEvent *event)
{
    /*
    // Determine virtual key that correspond to the key we got
    auto vkey = event->nativeVirtualKey();

    // nativeVirtualKey should be working everywhere, but just in case it's not
    if (vkey == 0 || vkey == 1)
        vkey = event->nativeScanCode();

    // If neither of them worked then simply use key code
    if (vkey == 0 || vkey == 1)
        vkey = event->key();
    */

    auto mkey = event->key();
    auto iterator = pressed_keys.find(mkey);

    // If vkey is already pressed, then this must the the release event
    if (iterator != pressed_keys.end())
    {
        for (auto keymap_id: bind[mkey]) {
            setKeypad(keymap_id, false);
        }
        pressed_keys.erase(iterator);
    }
    else if (event->type() == QEvent::KeyPress) // But press only on the press event
    {
        if (event->modifiers() & Qt::AltModifier)
        {
            mkey |= Qt::AltModifier; // Compose alt into the unused bit of the keycode
        }

        auto translated = bind.find(mkey);

        if (translated != bind.end())
        {
            pressed_keys.insert(mkey);
            for (auto const & keymap_id: bind[mkey]) {
                setKeypad(keymap_id, true);
            }
        }
    }
}

void QtKeypadBridge::keyPressEvent(QKeyEvent *event)
{
    // Ignore autorepeat, calc os must handle it on its own
    if(event->isAutoRepeat())
        return;

    Qt::Key key = static_cast<Qt::Key>(event->key());

    switch(key)
    {
    case Qt::Key_Down:
        keypad.touchpad_x = TOUCHPAD_X_MAX / 2;
        keypad.touchpad_y = 0;
        break;
    case Qt::Key_Up:
        keypad.touchpad_x = TOUCHPAD_X_MAX / 2;
        keypad.touchpad_y = TOUCHPAD_Y_MAX;
        break;
    case Qt::Key_Left:
        keypad.touchpad_y = TOUCHPAD_Y_MAX / 2;
        keypad.touchpad_x = 0;
        break;
    case Qt::Key_Right:
        keypad.touchpad_y = TOUCHPAD_Y_MAX / 2;
        keypad.touchpad_x = TOUCHPAD_X_MAX;
        break;
    default:
        keyToKeypad(event);

        return;
    }

    keypad.touchpad_contact = keypad.touchpad_down = true;
    the_qml_bridge->touchpadStateChanged();
    keypad.kpc.gpio_int_active |= 0x800;

    keypad_int_check();
}

void QtKeypadBridge::keyReleaseEvent(QKeyEvent *event)
{
    // Ignore autorepeat, calc os must handle it on its own
    if(event->isAutoRepeat())
        return;

    Qt::Key key = static_cast<Qt::Key>(event->key());

    switch(key)
    {
    case Qt::Key_Down:
        if(keypad.touchpad_x == TOUCHPAD_X_MAX / 2
            && keypad.touchpad_y == 0)
            keypad.touchpad_contact = keypad.touchpad_down = false;
        break;
    case Qt::Key_Up:
        if(keypad.touchpad_x == TOUCHPAD_X_MAX / 2
            && keypad.touchpad_y == TOUCHPAD_Y_MAX)
            keypad.touchpad_contact = keypad.touchpad_down = false;
        break;
    case Qt::Key_Left:
        if(keypad.touchpad_y == TOUCHPAD_Y_MAX / 2
            && keypad.touchpad_x == 0)
            keypad.touchpad_contact = keypad.touchpad_down = false;
        break;
    case Qt::Key_Right:
        if(keypad.touchpad_y == TOUCHPAD_Y_MAX / 2
            && keypad.touchpad_x == TOUCHPAD_X_MAX)
            keypad.touchpad_contact = keypad.touchpad_down = false;
        break;
    default:
        keyToKeypad(event);

        return;
    }

    the_qml_bridge->touchpadStateChanged();
    keypad.kpc.gpio_int_active |= 0x800;
    keypad_int_check();
}

bool QtKeypadBridge::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);

    if(event->type() == QEvent::KeyPress)
        keyPressEvent(static_cast<QKeyEvent*>(event));
    else if(event->type() == QEvent::KeyRelease)
        keyReleaseEvent(static_cast<QKeyEvent*>(event));
    else if(event->type() == QEvent::FocusOut)
    {
        // Release all keys on focus change
        for(auto calc_key : pressed_keys)
            setKeypad(calc_key, false);

        pressed_keys.clear();
        return false;
    }
    else
        return false;

    return true;
}

QtKeypadBridge qt_keypad_bridge;
