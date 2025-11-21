#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

class Input
{
public:
    void Init();
    void Update(MSG& msg);

    bool GetIsMousePressed() const { return m_isMousePressed; }

private:
    bool m_isMousePressed;
    bool m_isMouseHeld;
};

#endif
