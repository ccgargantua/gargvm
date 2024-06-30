#ifndef VM_ASSERT_H
#define VM_ASSERT_H


#include <stdio.h>


#define ASSERT(condition, message)                                                     \
do                                                                                     \
{                                                                                      \
    if ( !(condition) )                                                                \
    {                                                                                  \
        fprintf(stderr, "FAILED ASSERT at %s:%d '%s'\n", __FILE__, __LINE__, message); \
        exit(1);                                                                       \
    }                                                                                  \
}while(0)


#define ASSERT_UNREACHABLE    ASSERT(0, "Reached unreachable position.")
#define ASSERT_EQUAL(a, b)    ASSERT(a == b, #a " does not equal " #b " when it shouldn't.")
#define ASSERT_NONEQUAL(a, b) ASSERT(a != b, #a " equals " #b "when it shouldn't.")
#define ASSERT_NULL(a)        ASSERT(a == NULL, #a "is not NULL when it should be.")
#define ASSERT_NONNULL(a)     ASSERT(a != NULL, #a "is NULL when it shouldn't be.")


#endif