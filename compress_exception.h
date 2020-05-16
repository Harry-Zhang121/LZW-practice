#include <exception>

class open_mode_error : public std::exception
{
    const char * what () const throw ()
  {
    return "function and open mode does not match. Please read documentation for more info";
  }
};

