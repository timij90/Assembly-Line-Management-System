// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include "Station.h"

namespace seneca
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;

		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string& custOrder);
		CustomerOrder(const CustomerOrder& cust);
		CustomerOrder& operator=(const CustomerOrder& cust) = delete;
		CustomerOrder(CustomerOrder&& cust) noexcept;
		CustomerOrder& operator=(CustomerOrder&& cust) noexcept;
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		~CustomerOrder();
	};

}
#endif
