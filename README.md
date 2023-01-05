# s-talk
a simple "chat"-like facility that enables someone at one terminal (or Xterm) to communicate with someone at another terminal. The interface will not be pretty, but it will be functional. This facility will be called "s-talk" for simple-talk.

./s-talk 1001 linux1 1006
./s-talk 1006 linux2 1001

# troubles
- able to optmize fluency, user interface and code
- some unresolved reachable memory leaks caused by pthread_cancel_init and pthread_cancel
- don't know if I shutdown the thread properly
