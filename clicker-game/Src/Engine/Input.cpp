#include "input.h"

void Input::Init()
{
    m_isMousePressed = false;
    m_isMouseHeld = false;
    m_mousePos = { 0, 0 };
}

void Input::Update(MSG& msg)
{
    m_isMousePressed = false;

    switch (msg.message)
    {
    case WM_LBUTTONDOWN:
        if (!m_isMouseHeld)
            m_isMousePressed = true;
        m_isMouseHeld = true;
        m_mousePos.x = GET_X_LPARAM(msg.lParam);
        m_mousePos.y = GET_Y_LPARAM(msg.lParam);
        break;
    case WM_MOUSEMOVE:
        m_mousePos.x = GET_X_LPARAM(msg.lParam);
        m_mousePos.y = GET_Y_LPARAM(msg.lParam);
        break;
    case WM_LBUTTONUP:
        m_isMouseHeld = false;
        break;
    }
}
