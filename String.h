#if !defined(STRING_H_INCLUDED)
#define STRING_H_INCLUDED
#include <iostream>

class String  
{
  friend std::ostream& operator<< (std::ostream& os, const String& s);
public:
  String();
  String (const char* s);
  String (const String& s);
  size_t length() const;
  explicit String (char ch, size_t count = 1);
  ~String();
  String& append(const char* other);
  String& append(const String& other);
  String substr(size_t start, size_t numChars) const;
  char char_at(size_t pos) const;
  char& char_at(size_t pos);
  char operator[]( size_t pos) const;
  char& operator[]( size_t pos);
  String& operator+=( const char* other);
  String& operator+=(const String& other);
  String& operator=( const String& other);
  String& operator=(const char* other);
  bool operator<( const String& other) const;
  bool operator==( const String& other) const;

private:
  void init();
  void ensureSize (size_t size);
  char* m_buffer;
  size_t counter(const char* other);
  size_t m_length;
  size_t m_bufSize;
};

#endif // !defined(STRING_H_INCLUDED)