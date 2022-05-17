#pragma once
#include <cstdint>  // библиотека в която се намира uint8_t и uint32_t
#include <string>   // библиотека за текст
#include "Point.h"  // библиотека където е дефинирана структурата точка
#include <vector>   // билиботека за низове от данни

namespace Editor { // в този namespace ни се намират всички класове и функции за редактора

	class Map { // обект Map, който е картата на играта
	public:
		Map(uint32_t width = 0,uint32_t height = 0); // конструктор на обекта с параметър width,height , които задава големина на картата

		void Set(Point pos, int8_t value) { 
			m_Data[(int)pos.y][(int)pos.x] = value; 
		} // функция която замества дадена точка от картата с value

		int8_t Get(Point pos) const {  // функция за взимане на стойността на клетка в картата
			if (IsValid(pos))  // проверяваме дали точката се намира в картата
				return m_Data[(int)pos.y][(int)pos.x]; // връщаме стойността на клетката в тази точка
		}

		bool IsValid(Point pos) { return (pos.y < m_Height && pos.x < m_Width && pos.x >= 0 && pos.y >= 0); } // функция която проверява дали точката се намира в картата
		bool IsValid(Point pos) const { return (pos.y < m_Height&& pos.x < m_Width && pos.x >= 0 && pos.y >= 0); }// функция която проверява дали точката се намира в картата

		auto& data() { return m_Data; } // функция която връща низ от данни за картата, която се показва на екрана

		auto GetWidth() const { return m_Width; }; // функция която връща големината на картата
		auto GetHeight() const { return m_Height; }; // функция която връща големината на картата

		const void Draw() const; // функция която рисува картата със разкритите пространства
		void Fill(int8_t symbol); // функция която запълва картата със value

		void SetCursorPos(Point position,Point lastPosition) {
			if (position.x >= 0 && position.x < m_Width && position.y >= 0 && position.y < m_Height) {
				m_ShownData[lastPosition.y][lastPosition.x] = m_Data[lastPosition.y][lastPosition.x];
				m_ShownData[position.y][position.x] = '#';
			}
		}
		std::vector<std::vector<char>> m_Data; // 2D низ от символи с информация която се показва
		std::vector<std::vector<char>> m_ShownData; // 2D низ от символи с информация която се показва

		uint32_t m_Width{}; // големина на картата
		uint32_t m_Height{}; // големина на картата
	};

}
