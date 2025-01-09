// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca
{
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	seneca::Station::Station(const std::string& line) : m_id(0), m_name{ }, 
		m_description{ }, m_serialNumber(0), m_quantity(0)
	{
		size_t pos = 0;
		bool more = true;
		Utilities ut;
		ut.getDelimiter();

		m_name = ut.extractToken(line, pos, more);

		std::string s_number = ut.extractToken(line, pos, more);
		m_serialNumber = stoi(s_number);

		std::string quantity = ut.extractToken(line, pos, more);
		m_quantity = stoi(quantity);

		m_widthField = std::max(m_widthField, ut.getFieldWidth());

		m_description = ut.extractToken(line, pos, more);

		m_id = ++id_generator;
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		m_quantity > 0 ? m_quantity-- : m_quantity;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (!full)
			os << std::setfill('0') << std::setw(3) << std::right << m_id
			<< " | " << std::setfill(' ') << std::left << std::setw(m_widthField) << m_name
			<< " | " << std::setfill('0') << std::setw(6) << std::right << m_serialNumber << " | ";
		else
			os << std::setfill('0') << std::setw(3) << std::right << m_id
			<< " | " << std::setfill(' ') << std::left << std::setw(m_widthField) << m_name
			<< " | " << std::setfill('0') << std::setw(6) << std::right << m_serialNumber 
			<< " | "	<< std::setfill(' ') << std::setw(4) << std::right << m_quantity 
			<< " | " << std::left << m_description;

		os << std::endl;

	}
}