// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <deque>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "CustomerOrder.h"
#include "Station.h"
#include "LineManager.h"
#include "Utilities.h"

namespace seneca
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream load(file);
		if (!load) {
			throw std::string("Cannot open file ") + file;
		}

		Utilities ut;
		bool more = true;
		size_t pos = 0;
		std::string line;

		while (!load.eof()) {
			std::getline(load, line);

			std::string stationName = ut.extractToken(line, pos, more);
			std::string nextStationName = more ? ut.extractToken(line, pos, more) : "";

			auto stationIt = std::find_if(stations.begin(), stations.end(),
				[&](const Workstation* station) {
					return station->getItemName() == stationName;
				});

			if (stationIt != stations.end())
			{
				m_activeLine.push_back(*stationIt);

				if (!nextStationName.empty()) {
					auto nextIt = std::find_if(stations.begin(), stations.end(),
						[&](const Workstation* station) {
							return station->getItemName() == nextStationName;
						});

					if (nextIt != stations.end())
						(*stationIt)->setNextStation(*nextIt);
				}
			}
		}

		auto firstStationIt = std::find_if(stations.begin(), stations.end(),
			[&](Workstation* station) {
				return std::none_of(stations.begin(), stations.end(),
				[&](Workstation* otherStation) {
						return otherStation->getNextStation() == station;
					});
			});

		if (firstStationIt != stations.end()) {
			m_firstStation = *firstStationIt;
		}
		else {
			throw std::runtime_error("Error: No first station found.");
		}

		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations()
	{
		std::vector<Workstation*> reorderedStations;
		Workstation* currentStation = m_firstStation;

		while (currentStation != nullptr) {
			reorderedStations.push_back(currentStation);
			currentStation = currentStation->getNextStation();
		}

		m_activeLine = reorderedStations;
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t count = 0;
		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty())
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		std::for_each(m_activeLine.begin(), m_activeLine.end(),
			[&](Workstation* station) {
				station->fill(os);
			});

		std::for_each(m_activeLine.begin(), m_activeLine.end(),
			[&](Workstation* station) {
				return station->attemptToMoveOrder();
			});

		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}

	void LineManager::display(std::ostream& os) const
	{
		for (const auto& s : m_activeLine)
			s->display(os);
	}
}