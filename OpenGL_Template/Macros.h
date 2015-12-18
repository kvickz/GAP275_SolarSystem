//Macros.h

#ifndef MACROS_H
#define MACROS_H

#define SAFE_DELETE(_x_) delete _x_; _x_ = nullptr;
#define SAFE_DELETE_ARRAY(_x_) delete[] _x_; _x_ = nullptr;

#endif // !MACROS_H
