#pragma once
#include "Point.h"
#include "File.h"
#include <cstdint>
#include "Map.h"
namespace Editor{ // всичко свързано с редактора се намира в този неймспейс
    class Application{ // обект аппликация
    public:
        Application() { m_Map = Map(0, 0); };
        void Init(); // функция за инициализация
        void Update(); // функция която ъпдейтва редактора
        bool IsReadyToExit(){ return m_ReadyToExit;} // функция която връща дали редактора е приключил своето изпълнение

    private:
        bool m_ReadyToExit{}; // флаг който служи за излизане от програмата
        Point m_CursorPosition{}; // точка на която се намира курсора
        Point m_CursorLastPosition{}; // точка на която се намира курсора
        uint32_t m_Mode{};
        Map m_Map;
        Util::File m_CurrentFile{};
        uint32_t m_FontWidth{}, m_FontHeight{};
    };
}
