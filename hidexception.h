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
