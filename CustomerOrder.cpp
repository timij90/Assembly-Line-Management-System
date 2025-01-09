// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

namespace seneca
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() : m_name{ }, m_product{}, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

	CustomerOrder::CustomerOrder(const std::string& custOrder) : m_name{ }, m_product{}, m_cntItem{ 0 }, m_lstItem{ nullptr }
	{
		size_t pos = 0;
		bool more = true;
		Utilities ut;
		ut.getDelimiter();

		m_name = ut.extractToken(custOrder, pos, more);

		m_product = ut.extractToken(custOrder, pos, more);

		for (; more; )
		{
			std::string itemName = ut.extractToken(custOrder, pos, more);

			Item** temp = m_lstItem;
			m_lstItem = new Item * [m_cntItem + 1];

			for (size_t i = 0; i < m_cntItem; ++i) {
				m_lstItem[i] = temp[i];
			}

			m_lstItem[m_cntItem] = new Item(itemName);
			m_cntItem++;

			delete[] temp;
		}

		m_widthField = std::max(m_widthField, ut.getFieldWidth());
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& cust)
	{
		throw "Copy not allowed";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& cust) noexcept : m_name{ }, m_product{}, m_cntItem{ 0 }, m_lstItem{ nullptr }
	{
		operator=(std::move(cust));
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cust) noexcept
	{
		if (this != &cust)
		{
			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; ++i)
				{
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
			}

			m_name = cust.m_name;
			m_product = cust.m_product;
			m_cntItem = cust.m_cntItem;
			m_lstItem = cust.m_lstItem;
		}

		cust.m_name = "";
		cust.m_product = "";
		cust.m_cntItem = 0;
		cust.m_lstItem = nullptr;

		return *this;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool allFilled = true;

		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (!m_lstItem[i]->m_isFilled) {
				allFilled = false;
				break;
			}
		}
		return allFilled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		bool stop = false;

		for (size_t i = 0; i < m_cntItem && !stop; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled)
				{
					filled = false;
					stop = true;
				}
			}
		}
		return filled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool filled = false;
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_isFilled == filled && m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", "
						<< m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					filled = true;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", "
						<< m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; ++i)
		{
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
				<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - "
				<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
	}
}