#include "input.h"

void Input::Init()
{
    m_isMousePressed = false;
    m_isMouseHeld = false;
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
        break;
    case WM_LBUTTONUP:
        m_isMouseHeld = false;
        break;
    }
}
