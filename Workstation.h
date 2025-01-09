// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder>m_orders;
		Workstation* m_pNextStation;

	public:
		Workstation(const std::string& station);
		Workstation(const Workstation& ws) = delete;
		Workstation& operator=(const Workstation& ws) = delete;
		Workstation(Workstation&& ws) = delete;
		Workstation& operator=(Workstation&& ws) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		void display(std::ostream& os) const;
	};
}
#endif