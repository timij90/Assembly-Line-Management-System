// Name: Jacobs Oluwatimilehin Uba
// Seneca Student ID: 148981228
// Seneca email: oujacobs@myseneca.ca
// Date of completion: 18/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <stdexcept>
#include "Utilities.h"

namespace seneca
{
    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string token;
        size_t pos = str.find(m_delimiter, next_pos);
        if (pos == next_pos) 
        {
            more = false;
            throw "Delimiter found at next_pos";
        }

        more = pos != std::string::npos;
        token = str.substr(next_pos, pos - next_pos);
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        next_pos = pos + 1;
        m_widthField = std::max(m_widthField, token.size());
        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}