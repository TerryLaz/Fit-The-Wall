#include "MyMouse.h"

MyMouse::MyMouse():
    window(window)
{
    isPressed = false;
    isCorrect = false;
    insideCoords = false;
    posX = 0.0f;
    posY = 0.0f;
}

MyMouse::~MyMouse()
{
}

float MyMouse::GetPosX()
{
    return posX;
}

float MyMouse::GetPosY()
{
    return posY;
}

std::string MyMouse::GetPosAsString()
{
    return "X: " + std::to_string(posX) + " Y: " + std::to_string(posY);
}

bool MyMouse::IsPressed()
{
    return isPressed;
}

bool MyMouse::IsCorrect()
{
    return isCorrect;
}

bool MyMouse::isInsideCoords(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2)
{
    if (posX > xMin1 && posX<xMax1 && posY>yMin1 && posY < yMax1 || 
        posX > xMin2 && posX<xMax2 && posY>yMin2 && posY < yMax2)
        insideCoords = true;
    else
        insideCoords = false;

    return insideCoords;
}

bool MyMouse::puzzleCheck(float checkX1, float checkX2, float checkY1, float checkY2)
{
    if (insideCoords && isPressed)
    {
        if (posX >= checkX1 - 30.0f && posX <= checkX1 + 30.0f)
            check1 = true;

        if (posX >= checkX2 - 30.0f && posX <= checkX2 + 30.0f)
            check2 = true;

        if (posY >= checkY1 - 30.0f && posY <= checkY1 + 30.0f)
            check3 = true;

        if (posY >= checkY2 - 30.0f && posY <= checkY2 + 30.0f)
            check4 = true;

    }
    else
    {
        check1 = false;
        check2 = false;
        check3 = false;
        check4 = false;
    }

    if (check1 && check2 && check3 && check4)
        isCorrect = true;
    else
        isCorrect = false;

    return isCorrect;
}

void MyMouse::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont)
{
    if (isCorrect)
    {
        spriteFont.DrawString(&spriteBatch, L"SUCCESS!", DirectX::XMFLOAT2(0, 50), DirectX::Colors::GreenYellow, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
        isCorrect = false; 
    }
    else
        spriteFont.DrawString(&spriteBatch, GetPosAsString().c_str(), DirectX::XMFLOAT2(0, 50), DirectX::Colors::GreenYellow, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.4f, 0.4f));

}

void MyMouse::SetIsCorrect(bool correct)
{
    isCorrect = correct;
}

void MyMouse::HandleInput()
{
    if (GetKeyState(MK_LBUTTON) & 0x8000 && isPressed == false)
    {
        isPressed = true;
    }
    if (!(GetKeyState(MK_LBUTTON) & 0x8000) && isPressed == true)
    {
        isPressed = false;
    }
}

void MyMouse::Update(HWND window)
{
    HandleInput();

    //if (isPressed)
    //{
        GetCursorPos(&ptCursor);
        ScreenToClient(window, &ptCursor);
        posX = ptCursor.x;
        posY = ptCursor.y;
    //}
}
