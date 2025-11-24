#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>
#include <windowsx.h>

class Input
{
public:
    void Init();
    void Update(MSG& msg);

    bool GetIsMousePressed() const { return m_isMousePressed; }
    POINT GetMousePos() const { return m_mousePos; }

private:
    bool m_isMousePressed;
    bool m_isMouseHeld;
    POINT  m_mousePos;
};

#endif
