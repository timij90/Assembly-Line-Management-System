// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca
{
	class Station
	{
		int m_id;
		std::string m_name;
		std::string m_description;
		size_t m_serialNumber;
		size_t m_quantity;

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const std::string& line);
		const std::string& getItemName() const;
		size_t getNextSerialNumber(); 
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif
