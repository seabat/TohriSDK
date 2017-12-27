#ifndef COMMON_H
#define COMMON_H

#if DEBUG
#define LOGD(...) printf(__VA_ARGS__)
#else
#define LOGD(...)
#endif

#endif /* COMMON_H */
