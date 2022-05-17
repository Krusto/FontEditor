#include "Editor.h"
#include <iostream>
#include "WindowsFunctions.h"
#include <conio.h> // библиотека която включва _getch()

namespace Editor{
void Application::Init(){
    std::cout << "Select an option:\n";
    std::cout << "1. Create new Font\n";
    std::cout << "2. Edit existing Font\n";
    std::cin >> m_Mode;
    if(m_Mode == 1){
        ClearScreen();
        std::string FontName,letter;
        int width{}, height{};
        std::cout<<"Font name:";std::cin >> FontName;
        std::cout << "Select Size: "; std::cin >> width >> height;
        std::cout << "Select letter:"; std::cin >> letter;
        
        m_CurrentFile.CreateNew(("./"+FontName +"."+ std::to_string(width)+"."+std::to_string(height) + "." + letter + ".txt").data());
        m_FontWidth = width;
        m_FontHeight = height;
        m_Map = Map(width,height);
        m_Map.Fill(' ');
        m_CurrentFile.mode = 1;
        ClearScreen();
    }
    else if (m_Mode == 2) {
        ClearScreen();
        std::string FontName, letter;
        int width{}, height{};
        std::cout << "Font name:"; std::cin >> FontName;
        std::cout << "Select Size: "; std::cin >> width >> height;
        std::cout << "Select letter:"; std::cin >> letter;
        m_CurrentFile.Open(("./" + FontName + "." + std::to_string(width) + "." + std::to_string(height) + "." + letter + ".txt").data(),
            Util::FileDataType::Text, Util::FileOperationFlags::Read);
        m_CurrentFile.mode = 2;
        m_FontWidth = width;
        m_FontHeight = height;
        m_Map = Map(width, height);
        m_Map.Fill(' ');
        m_CurrentFile.GetData(m_Map.data(),m_FontWidth);
        for (size_t i = 0; i < m_FontHeight; i++)
        {
            for (size_t j = 0; j < m_FontWidth; j++)
            {
                m_Map.m_ShownData[i][j] = m_Map.data()[i][j];
            }
        }
        ClearScreen();
    }
}

void Application::Update(){
    GotoXY(0, 0);
    m_Map.Draw();
    if (GetAsyncKeyState(VK_ESCAPE)) {
        m_ReadyToExit = true;
        m_CurrentFile.SaveData(m_Map.data());
        return;
    }
    char key = _getch();
    if (key == 'j') {
        if (m_CursorPosition.y - 1 >= 0) {
            m_CursorLastPosition = m_CursorPosition;
            m_CursorPosition.y -= 1;
            m_Map.SetCursorPos(m_CursorPosition, m_CursorLastPosition);
        }
    }
    else if (key == 'l') {
        if (m_CursorPosition.y + 1 < m_FontHeight) {
            m_CursorLastPosition = m_CursorPosition;
            m_CursorPosition.y += 1;
            m_Map.SetCursorPos(m_CursorPosition, m_CursorLastPosition);
        }
    }
    else if (key == 'i') {
        if (m_CursorPosition.x - 1 >= 0) {
            m_CursorLastPosition = m_CursorPosition;
            m_CursorPosition.x -= 1;
            m_Map.SetCursorPos(m_CursorPosition, m_CursorLastPosition);
        }
    }
    else if (key == 'k') {
        if (m_CursorPosition.x + 1 < m_FontWidth) {
            m_CursorLastPosition = m_CursorPosition;
            m_CursorPosition.x += 1;
            m_Map.SetCursorPos(m_CursorPosition, m_CursorLastPosition);
        }
    }
    if (key == 's') {
        m_Map.Set(m_CursorPosition, '.');
    }
    if (key == 'd') {
        m_Map.Set(m_CursorPosition, ' ');
    }
    Sleep(20);  

}

}
