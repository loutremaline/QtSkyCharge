/*
 * Copyright 2020 loutremaline79
 *
 * This file is part of QtSkyCharge.
 *
 *  QtSkyCharge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>
 */
#ifndef HIDEXCEPTION_H
#define HIDEXCEPTION_H

#include <exception>
#include <QString>


class HidException : public std::exception
{
public:
    HidException(int code = 0, QString phrase = "") throw()
        :m_code(code), m_phrase(phrase) {}

    virtual ~HidException() throw() {}

    virtual const char * what() const throw()
    {
        return m_phrase.toStdString().c_str();
    }

    virtual const QString message() throw()
    {
        return m_phrase;
    }

    int code(HidException) const throw()
    {
        return m_code;
    }

private:
    int m_code;
    QString m_phrase;
};

#endif // HIDEXCEPTION_H
