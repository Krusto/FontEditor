#include "Map.h"
#include <iostream>// библиотека за input/output в конзолата
#include <Windows.h>  // библиотека използвана за манипулиране на конзолата
#include "WindowsFunctions.h" //библиотека в която са дефинирани функции за манипулиране на конзолата
#include <algorithm> // библиотека за алгоритми
#include <random> // библиотека за произволни числа
namespace Editor {
	Map::Map(uint32_t width,uint32_t height) // конструктор на клас Карта
	{
		m_Data.resize(height); // казваме на низа да има size редове
		std::for_each(m_Data.begin(), m_Data.end(), [&](std::vector<char>& el) { // за всеки ред взимаме низ от символи
			el.resize(width); // казвваме колко колони искаме да има редът
			});
		
		m_ShownData.resize(height); // казваме на низа да има size редове
		std::for_each(m_ShownData.begin(), m_ShownData.end(), [&](std::vector<char>& el) { // за всеки ред взимаме низ от символи
			el.resize(width); // казвваме колко колони искаме да има редът
			});


		m_Width = width; // задаваме широчината на картата да е равен на width
		m_Height = height; // задаваме височината на картата да е равен на height
	}

	const void Map::Draw() const{ // рисуваме картата на потребителят
		for (size_t x = 0; x < m_Width; x++) // минаваме през всяко х на картата
		{
			for (size_t y = 0; y < m_Height; y++) // минаваме през всяко у на картата
			{
				std::cout << m_ShownData[y][x]; // рисуваме информацията в клетката
			}
			std::cout << '\n'; // минаваме на слеващ ред
		}
	}


	void Map::Fill(int8_t symbol) // функция която запълва клетките с някакъв symbol
	{
		for (size_t x = 0; x < m_Width; x++) // минаваме през всяко х на картата
		{
			for (size_t y = 0; y < m_Height; y++) // минаваме през всяко у на картата
			{
				m_Data[y][x] = symbol; // заместваме точка х,у на картата с symbol
				m_ShownData[y][x] = symbol; // заместваме точка х,у на картата с symbol
			}
		}
	}

}
