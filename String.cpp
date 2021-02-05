#include <stdlib.h>
#include <string.h>
#include "String.h"

String::String()
{
  init();
}

String::String(const char* s)
{
  init();
  append(s);
}

String::String(const String& s)
{
  init();
  append(s);
}

size_t String::length() const
{
    return m_length;
}

String::String(char ch, size_t count /* = 1 */)
{
  init();
  ensureSize(count);
  memset(m_buffer, ch, count);
  m_length = count;
}

String::~String()
{
  delete[] m_buffer;
}

// helper to get the # of chars in char*. private, but can be public.
size_t String::counter(const char* other) 
{
    if (!other)
    {
        return 0;
    }
    size_t i = 0;
    while (other[i] != '\0')
    {
        ++i;
    }
    return ++i;
}

String& String::append(const char* other)
{
    size_t old_length = m_length;
    size_t o_size = counter(other);
    if (o_size == 0)
    {
        return *this;
    }
    m_length += o_size;
    m_bufSize += o_size;
    char* pNew = new char[m_length];
    if (old_length > 1)
    {
        --m_length;     // deduct off the extra \0 char.
        --m_bufSize;
        memcpy(pNew, m_buffer, old_length-1);
        for (size_t i = old_length-1; i < m_length; i++)
        {
            pNew[i] = other[i - old_length+1];
        }
    } 
    else
    {   
        memcpy(pNew, other, o_size);
    }
    delete[] m_buffer;
    m_buffer = pNew;
    return *this;
}

String& String::append(const String& other)
{
    size_t old_length = m_length;
    m_bufSize += other.m_bufSize;
    m_length += other.m_length;
    char* pNew = new char[m_length];
    if (old_length > 1) 
    {
        --m_length;     // deduct off the extra \0 char.
        --m_bufSize;
        memcpy(pNew, m_buffer, old_length-1);
        for (size_t i = old_length-1; i < m_length; ++i)
        {
            pNew[i] = other.m_buffer[i - old_length + 1];
        }
    }
    else
    {
        memcpy(pNew, other.m_buffer, other.m_length);
    }
    delete[] m_buffer;
    m_buffer = pNew;
    return *this;
}

// this func should return a copy of the result, not pointer nor reference.
String String::substr(size_t start, size_t numChars) const
{
    if (!numChars)
    {
        return String();
    }
    if (start  > m_length)
    {
        throw std::out_of_range("Out of range error.");
    }
    size_t c_bundry = start + numChars;
    if (c_bundry > this->m_length)
    {
        c_bundry = this->length();
    }
    char* tmp = new char[c_bundry-start+1];
    for (size_t i = start; i < c_bundry; ++i)
    {
        tmp[i - start] = this->m_buffer[i];
    }
    tmp[c_bundry-start] = '\0';
    String temp = String(tmp);      // construct a new string instance from result, later return the copy.
    delete[] tmp;
   return temp;
}

std::ostream& operator<< (std::ostream& os, const String& s)
{
  String temp = s;
  // Add null terminator so we can use ostream's char* output operator
  temp.ensureSize(temp.m_length + 1);
  temp.m_buffer[temp.m_length] = 0;
  os << "S(" << temp.m_length << "," << temp.m_bufSize
     << ")[" << temp.m_buffer << "]";
  return os;
}

void String::init()
{
  m_buffer = NULL;
  m_length = 0;
  m_bufSize = 0;
}

char String::char_at(size_t pos) const
{
    if (pos > m_length)
    {
        throw std::out_of_range("Out of range.");
    }
    return m_buffer[pos];
}

char& String::char_at(size_t pos)
{
    if (pos > m_length)
    {
        throw std::out_of_range("Out of range.");
    }
    return m_buffer[pos];
}

char String::operator[](size_t pos) const
{
    return m_buffer[pos];
}

char& String::operator[](size_t pos) {
    return m_buffer[pos];
}

String& String::operator+=(const char* other)
{
    this->append(other);
    return *this;
}


String&  String::operator+=( const String& other)
{
    this->append(other);
    return *this;
}

String& String::operator=(const String& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_length = other.m_length;
    m_bufSize = other.m_bufSize;
    delete[] m_buffer;
    m_buffer = new char[m_length];
    memcpy(m_buffer, other.m_buffer, m_length);
    return *this;
}

String& String::operator=(const char* other)
{
    if (other[0] == '\0')
    {
        init();
        return *this;
    }
    size_t o_size = counter(other);
    m_length = o_size;
    m_bufSize = o_size;
    delete[] m_buffer;
    char* pNew = new char[o_size];
    memcpy(pNew, other, o_size);
    m_buffer = pNew;
    return *this;
}

bool String::operator<(const String& other) const
{
    if (m_length > other.m_length)
    {
        return false;
    }
    for (size_t i = 0; i < m_length; i++)
    {
        if (m_buffer[i] >= other.m_buffer[i]) 
        {
            return false;
        }
    }
    return true;
}

bool String:: operator==(const String& other) const 
{
    if (m_length != other.m_length)
    {
        return false;
    }
    for (size_t i = 0; i < m_length; i++)
    {
        if (m_buffer[i] != other.m_buffer[i])
        {
            return false;
        }
    }
    return true;
}

void String::ensureSize(size_t size)
{
  if (size <= m_bufSize)
  {
    return;
  }

  char* pNew = new char[size];
  memcpy(pNew, m_buffer, m_length);
  m_bufSize = size;
  delete[] m_buffer;
  m_buffer = pNew;
}
