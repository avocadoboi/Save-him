#include "../App/App.hpp"

int main()
{
	new App();
}

//#include <iostream>
//#include <random>
//#include <array>
//#include <set>
//
//class AscendingNumbersGenerator
//{
//private:
//	// Genererar slumpmässiga tal
//	std::default_random_engine m_randomEngine{ (std::random_device())() };
//
//	// En jämn fördelning av reella tal mellan 0 och 1
//	std::uniform_real_distribution<double> m_distribution{ 0., 1. };
//
//	// Det minsta talet som kan genereras
//	unsigned m_min;
//
//	// Det högsta talet som kan genereras
//	unsigned m_max;
//
//public:
//	AscendingNumbersGenerator(unsigned p_min, unsigned p_max) : 
//		m_min(p_min), m_max(p_max)
//	{
//		if (m_min >= m_max)
//		{
//			throw std::range_error("AscendingNumbersGenerator: max is less than min");
//		}
//	}
//
//	// Den gamla metoden
//	template<size_t N>
//	std::array<unsigned, N> generateNew_0()
//	{
//		if (N > m_max - m_min)
//		{
//			throw std::domain_error("AscendingNumbersGenerator: Cannot generate N unique numbers because N is too big.");
//		}
//
//		std::array<unsigned, N> result;
//		
//		for (unsigned i = 0; i < N; i++)
//		{
//			// Denna while-loop kan hänga sig ett tag eftersom den bara testar nya tal om och om igen tills man hittar ett unikt.
//			// Det är bättre att ha en array från början med alla tal man kan välja mellan och sedan ta bort de man väljer.
//			while (true)
//			{
//				result[i] = m_distribution(m_randomEngine)*(m_max + 1u - m_min) + m_min;
//
//				bool isUnique = true;
//				for (unsigned j = 0; j < i; j++)
//				{
//					if (result[j] == result[i])
//					{
//						isUnique = false;
//						break;
//					}
//				}
//				if (isUnique)
//				{
//					break;
//				}
//			}
//		}
//		// Sortering är ineffektivt eftersom komplexiteten är sämre än linjär: O(nlog(n))
//		std::sort(result.begin(), result.end());
//
//		return result;
//	}
//
//	// En mycket effektivare metod
//	template<size_t N>
//	std::array<unsigned, N> generateNew_1()
//	{
//		if (N > m_max - m_min)
//		{
//			throw std::domain_error("AscendingNumbersGenerator: Cannot generate N unique numbers because N is too big.");
//		}
//		
//		// Här är de talen man kan välja slumpmässigt från. 
//		// När man valt ett tal från den här listan tas det bort.
//		std::vector<unsigned> numbersToChooseFrom(m_max + 1 - m_min);
//		for (unsigned i = 0; i <= m_max - m_min; i++)
//		{
//			numbersToChooseFrom[i] = m_min + i;
//		}
//
//		// Ett std::set sorterar automatiskt in nya värden med konstant komplexitet
//		std::set<unsigned> resultSet;
//		for (unsigned i = 0; i < N; i++)
//		{
//			unsigned numberIndex = m_distribution(m_randomEngine) * numbersToChooseFrom.size();
//			// Lägg in talet i mängden
//			resultSet.insert(numbersToChooseFrom[numberIndex]);
//			// "ta bort" talet genom att byta ut det mot det sista och minska antalet tal som är kvar med ett.
//			numbersToChooseFrom[numberIndex] = numbersToChooseFrom.back();
//			numbersToChooseFrom.pop_back();
//		}
//		
//		// Kopiera talen till en array
//		std::array<unsigned, N> result;
//		unsigned i = 0;
//		for (auto& number : resultSet)
//		{
//			result[i++] = number;
//		}
//		return result;
//	}
//};
//
//int main()
//{
//	// Bara för att visa att båda funkar
//
//	AscendingNumbersGenerator generator(1, 35);
//	std::cout << "Sju unika slumpmässiga tal valda från 1 till och med 35 med algoritm 0:\n";
//	for (auto number : generator.generateNew_0<33>())
//	{
//		std::cout << number << ' ';
//	}
//	std::cout << "\n\Med algoritm 1:\n";
//	for (auto number : generator.generateNew_1<33>())
//	{
//		std::cout << number << ' ';
//	}
//	std::cout << '\n';
//
//	return 0;
//}
