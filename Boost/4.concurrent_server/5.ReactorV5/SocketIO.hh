#ifndef __SOCKETIO_HH__
#define __SOCKETIO_HH__

class SocketIO {
public:
    explicit SocketIO(int);
    ~SocketIO();
public:
    int readn(char *, int );
    int writen(const char *, int);
    int readLine(char *, int);
private:
    int _fd;
};

#endif
