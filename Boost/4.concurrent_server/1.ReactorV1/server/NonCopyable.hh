#ifndef __NonCopyable_HH__
#define __NonCopyable_HH__

class NonCopyable{
protected:
    NonCopyable(){} 
    ~NonCopyable(){};
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable & operator=(const NonCopyable &) = delete;
};

#endif
