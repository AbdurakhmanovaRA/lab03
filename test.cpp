#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_negative(){
    double min = 0;
    double max = 0;
    find_minmax({-2, -1, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_samenum(){
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void test_onenum(){
    double min = 0;
    double max = 0;
    find_minmax({12}, min, max);
    assert(min == 12);
    assert(max == 12);
}

void test_empty(){
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

int
main() {
    test_positive();
    test_negative();
    test_samenum();
    test_onenum();
    test_empty();
}
