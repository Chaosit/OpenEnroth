#include "NuklearEventHandler.h"

#include "Nuklear.h"

bool NuklearEventHandler::KeyPressEvent(const PlatformKeyEvent *event) {
    PlatformKey key = event->key;
    PlatformModifiers mods = event->mods;

    if (nuklear->KeyEvent(key))
        return true;

    return KeyEvent(key, mods, true);
}

bool NuklearEventHandler::KeyReleaseEvent(const PlatformKeyEvent *event) {
    PlatformKey key = event->key;
    PlatformModifiers mods = event->mods;

    if (key == PlatformKey::Tilde && (mods & PlatformModifier::Ctrl))
        nuklear->Reload();

    return KeyEvent(key, mods, false);
}

bool NuklearEventHandler::KeyEvent(PlatformKey key, PlatformModifiers mods, bool down) {
    if (key == PlatformKey::Shift) {
        nk_input_key(nuklear->ctx, NK_KEY_SHIFT, down);
    } else if (key == PlatformKey::Delete) {
        nk_input_key(nuklear->ctx, NK_KEY_DEL, down);
    } else if (key == PlatformKey::Return) {
        nk_input_key(nuklear->ctx, NK_KEY_ENTER, down);
    } else if (key == PlatformKey::Tab) {
        nk_input_key(nuklear->ctx, NK_KEY_TAB, down);
    } else if (key == PlatformKey::Backspace) {
        nk_input_key(nuklear->ctx, NK_KEY_BACKSPACE, down);
    } else if (key == PlatformKey::Home) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_START, down);
        nk_input_key(nuklear->ctx, NK_KEY_SCROLL_START, down);
    } else if (key == PlatformKey::End) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_END, down);
        nk_input_key(nuklear->ctx, NK_KEY_SCROLL_END, down);
    } else if (key == PlatformKey::PageDown) {
        nk_input_key(nuklear->ctx, NK_KEY_SCROLL_DOWN, down);
    } else if (key == PlatformKey::PageUp) {
        nk_input_key(nuklear->ctx, NK_KEY_SCROLL_UP, down);
    } else if (key == PlatformKey::Z && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_UNDO, down);
    } else if (key == PlatformKey::R && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_REDO, down);
    } else if (key == PlatformKey::C && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_COPY, down);
    } else if (key == PlatformKey::V && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_PASTE, down);
    } else if (key == PlatformKey::X && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_CUT, down);
    } else if (key == PlatformKey::B && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_LINE_START, down);
    } else if (key == PlatformKey::E && (mods & PlatformModifier::Ctrl)) {
        nk_input_key(nuklear->ctx, NK_KEY_TEXT_LINE_END, down);
    } else if (key == PlatformKey::Up) {
        nk_input_key(nuklear->ctx, NK_KEY_UP, down);
    } else if (key == PlatformKey::Down) {
        nk_input_key(nuklear->ctx, NK_KEY_DOWN, down);
    } else if (key == PlatformKey::Left) {
        if (mods & PlatformModifier::Ctrl)
            nk_input_key(nuklear->ctx, NK_KEY_TEXT_WORD_LEFT, down);
        else
            nk_input_key(nuklear->ctx, NK_KEY_LEFT, down);
    } else if (key == PlatformKey::Right) {
        if (mods & PlatformModifier::Ctrl)
            nk_input_key(nuklear->ctx, NK_KEY_TEXT_WORD_RIGHT, down);
        else
            nk_input_key(nuklear->ctx, NK_KEY_RIGHT, down);
    } else {
        return false;
    }

    return true;
}


bool NuklearEventHandler::MouseMoveEvent(const PlatformMouseEvent *event) {
    nk_input_motion(nuklear->ctx, event->pos.x, event->pos.y);

    return true;
}

bool NuklearEventHandler::MousePressEvent(const PlatformMouseEvent *event) {
    if (event->button == PlatformMouseButton::Left && event->isDoubleClick)
        nk_input_button(nuklear->ctx, NK_BUTTON_DOUBLE, event->pos.x, event->pos.y, true);

    return MouseEvent(event->button, event->pos, true);
}

bool NuklearEventHandler::MouseReleaseEvent(const PlatformMouseEvent *event) {
    return MouseEvent(event->button, event->pos, true);
}

bool NuklearEventHandler::MouseEvent(PlatformMouseButton button, const Pointi &pos, bool down) {
    /* mouse button */
    if (button == PlatformMouseButton::Left) {
        nk_input_button(nuklear->ctx, NK_BUTTON_LEFT, pos.x, pos.y, down);
    } else if (button == PlatformMouseButton::Middle) {
        nk_input_button(nuklear->ctx, NK_BUTTON_MIDDLE, pos.x, pos.y, down);
    } else if (button == PlatformMouseButton::Right) {
        nk_input_button(nuklear->ctx, NK_BUTTON_RIGHT, pos.x, pos.y, down);
    }

    return true;
}

bool NuklearEventHandler::WheelEvent(const PlatformWheelEvent *event) {
    nk_input_scroll(nuklear->ctx, nk_vec2(event->angleDelta.x, event->angleDelta.y));

    return true;
}

std::shared_ptr<NuklearEventHandler> nuklearEventHandler;
