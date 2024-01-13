# test
make debug test

# print /proc/PID/status vmrss

# watch -d 'cat /proc/self/status | grep VmRSS'
this is what you would normaly execute, but there is also kubernetes
with its memory constraints....

# build release
make -j4 release