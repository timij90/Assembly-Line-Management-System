// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace seneca
{
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& station) : Station(station), m_pNextStation(nullptr) {}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) 
			{
				if (m_pNextStation)
				{
					*m_pNextStation += std::move(m_orders.front());
				}

				else if (m_orders.front().isOrderFilled())
				{
					g_completed.push_back(std::move(m_orders.front()));
				}

				else
					g_incomplete.push_back(std::move(m_orders.front()));

				m_orders.pop_front();
			}
			return true;
		}
		return false;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> "
			<< (getNextStation() ? getNextStation()->getItemName() : "End of Line")
			<< std::endl;
	}
}

