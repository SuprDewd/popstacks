#ifndef _FIELD_H_
#define _FIELD_H_

template <class T>
class field {
public:
    T operator +(const T &other) const = 0;
    T operator -(const T &other) const = 0;
    T operator *(const T &other) const = 0;
    T operator /(const T &other) const = 0;
};

#endif
