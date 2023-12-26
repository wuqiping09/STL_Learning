#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <complex.h>
#include "myvector.h"
#include "myless.h"

void testUnorderedSet() {
    std::unordered_set<int> S;
    std::vector<int> v = {1, 2, 3, 7, 12, 21};
    S.insert(v.begin(), v.end());
    std::cout << "total number of buckets:" << S.bucket_count() << std::endl;
    std::cout << "21 is in bucket " << S.bucket(21) << std::endl;
    std::cout << "load_factor is " << S.load_factor() << std::endl;
}

void testConstIterator() {
    std::set<int> S = {1, 2, 3, 5};
    std::set<int>::const_iterator iter = S.cbegin();
    ++iter;
    std::cout << *iter << std::endl;
    std::for_each(S.cbegin(), S.cend(), [](const int &a) {
        std::cout << a << std::endl;
    });
}

void testInsertIterator() {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 4, 5};
    auto iter = find(v2.begin(), v2.end(), 4);
    std::insert_iterator<std::vector<int>> i_iter(v2, iter);
    std::copy(v1.begin(), v1.end(), i_iter);
    for (auto iter = v2.begin(); iter != v2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void testStreamIterator() {
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::ostream_iterator<std::string>(std::cout, " "));
}

void testReverseIterator() {
    std::vector<int> v = {2, 6, 9};
    for (std::reverse_iterator<std::vector<int>::iterator> r_iter = v.rbegin(); r_iter != v.rend(); ++r_iter) {
        std::cout << *r_iter << " ";
    }
    std::cout << std::endl;
}

void testVectorInsert() {
    std::vector<int> v1 = {1, 0, 2};
    std::vector<int> v2 = {3, 4, 5};
    std::vector<int>::iterator iter = std::min_element(v1.begin(), v1.end());
    v2.insert(v2.end(), iter, v1.end());
    for (auto iter = v2.begin(); iter != v2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void testFindIf() {
    std::vector<int> v = {0, 1, 2, 5, 6, 7};
    std::vector<int>::iterator iter = std::find_if(v.begin(), v.end(), [](int x) {
        return x % 2;
    });
    std::cout << *iter << std::endl;
}

void testFunctor() {
    double x = std::multiplies<double>()(2.1, 1.1);
    std::cout << x << std::endl;
    if (std::not_equal_to<int>()(x, 10)) {
        std::cout << "x is not equal to 10" << std::endl;
    }
}

void testParameterBinding() {
    std::set<int> S = {2, 4, 3};

    std::vector<int> v;
    std::transform(S.begin(), S.end(), std::back_inserter(v), std::bind(std::multiplies<int>(), std::placeholders::_1, 10));
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v1;
    std::transform(S.begin(), S.end(), std::back_inserter(v1), [](int x) {
        return x * 2;
    });
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v2;
    std::transform(S.begin(), S.end(), std::back_inserter(v2), std::bind(std::logical_or<bool>(), std::bind(std::greater<int>(), std::placeholders::_1, 3), std::bind(std::less<int>(), std::placeholders::_1, 3)));
    for (auto iter = v2.begin(); iter != v2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void testMyLess() {
    std::set<int, MyLess<int>> S = {1, 30, 27, 93, 9};
    for (auto iter = S.begin(); iter != S.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
    std::cout << std::endl;
}

void testAlgorithms1() {
    std::vector<int> v1 = {1, 3, 55, 24, 1, 35, 24, 33, 55};

    std::cout << std::count(v1.begin(), v1.end(), 24) << std::endl;
    std::cout << std::count_if(v1.begin(), v1.end(), [](int x) {
        return x > 10;
    }) << std::endl;

    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> p_iter = std::minmax_element(v1.begin(), v1.end());
    std::cout << p_iter.first - v1.begin() << " " << *p_iter.first << std::endl;
    std::cout << p_iter.second - v1.begin() << " " << *p_iter.second << std::endl;

    std::cout << *std::find_if(v1.begin(), v1.end(), [](int x) {
        return x > 30;
    }) << std::endl;

    std::vector<int> v2 = {1, 3, 3, 5, 8, 3, 5};

    std::cout << std::search_n(v2.begin(), v2.end(), 2, 3) - v2.begin() << std::endl;
    std::vector<int> sub = {3, 5};
    std::cout << std::search(v2.begin(), v2.end(), sub.begin(), sub.end()) - v2.begin() << std::endl;
    std::cout << std::find_end(v2.begin(), v2.end(), sub.begin(), sub.end()) - v2.begin() << std::endl;
    std::cout << std::find_first_of(v2.begin(), v2.end(), sub.begin(), sub.end()) - v2.begin() << std::endl;
    std::cout << std::adjacent_find(v2.begin(), v2.end()) - v2.begin() << std::endl;
    
    if (std::equal(v2.begin() + 2, v2.begin() + 4, sub.begin())) {
        std::cout << "sub vector is equal to (v2+2)" << std::endl;
    }

    std::vector<int> perm = {3, 3, 3, 5, 5, 1, 8};
    if (std::is_permutation(v2.begin(), v2.end(), perm.begin())) {
        std::cout << "perm vector is permutation of v2" << std::endl;
    }

    std::vector<int> v3 = {1, 3, 3, 5, -1, 8};

    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> p_iter1 = std::mismatch(v3.begin(), v3.end(), v2.begin());
    std::cout << p_iter1.first - v3.begin() << " " << *p_iter1.first << std::endl;
    std::cout << p_iter1.second - v2.begin() << " " << *p_iter1.second << std::endl;
    
    if (std::lexicographical_compare(v2.begin(), v2.end(), v3.begin(), v3.end())) {
        std::cout << "v2 is smaller than v3" << std::endl;
    } else {
        std::cout << "v2 is not smaller than v3" << std::endl;
    }

    std::cout << *std::is_sorted_until(v3.begin(), v3.end()) << std::endl;
    if (std::is_partitioned(v3.begin(), v3.end(), [](int x) {
        return x < 6;
    })) {
        std::cout << "v3 is partitioned by <6" << std::endl;
    }

    if (std::all_of(v3.begin(), v3.end(), [](int x) {
        return x < 10;
    })) {
        std::cout << "all of v3 is <10" << std::endl;
    }
    if (std::any_of(v3.begin(), v3.end(), [](int x) {
        return x < 0;
    })) {
        std::cout << "some of v3 is <0" << std::endl;
    }
    if (std::none_of(v3.begin(), v3.end(), [](int x) {
        return x > 100;
    })) {
        std::cout << "none of v3 is >100" << std::endl;
    }
}

void testAlgorithms2() {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 5, 7};
    std::vector<int> v3(4);

    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int x, int y) {
        return x + y;
    });
    for (auto iter = v3.begin(); iter != v3.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::swap_ranges(v1.begin(), v1.end(), v2.begin());
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    for (auto iter = v2.begin(); iter != v2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v4(4);
    std::fill(v4.begin(), v4.end(), 1);
    std::generate(v4.begin(), v4.begin() + 2, rand);
    for (auto iter = v4.begin(); iter != v4.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v5 = {2, 4, 6};
    std::replace(v5.begin(), v5.end(), 4, 3);
    std::replace_if(v5.begin(), v5.end(), [](int x) {
        return x < 5;
    }, 1);
    std::remove(v5.begin(), v5.end(), 1);
    std::remove_if(v5.begin(), v5.end(), [](int x) {
        return x > 1;
    });
    std::cout << "v5 size:" << v5.size() << std::endl;

    std::vector<int> v6 = {3, 5, 5, 5, 7, 8, 9, 9};
    std::vector<int>::iterator new_end = std::unique(v6.begin(), v6.end());
    for (auto iter = v6.begin(); iter != new_end; ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v7 = {4, 6, 9, 3, 5, 1};
    std::rotate(v7.begin(), v7.begin() + 4, v7.end());
    for (auto iter = v7.begin(); iter != v7.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    //std::random_shuffle(v7.begin(), v7.end()); // removed in C++17
}

void testSort() {
    std::vector<int> v1 = {9, 50, -4, 3, 1, 49, 32};

    std::sort(v1.begin(), v1.end(), MyLess<int>());
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::partial_sort(v1.begin(), v1.begin() + 3, v1.end(), std::greater<int>());
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::nth_element(v1.begin(), v1.begin() + 3, v1.end());
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::stable_partition(v1.begin(), v1.end(), [](int x) {
        return x > 40;
    });
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v2 = {9, 1, 10, 2, 45, 3, 90, 4, 9, 5, 8};
    std::make_heap(v2.begin(), v2.end());
    std::pop_heap(v2.begin(), v2.end());
    std::cout << "the root of the heap is " << v2.back() << std::endl;
    v2.pop_back();
    v2.push_back(100);
    std::push_heap(v2.begin(), v2.end());
    if (std::is_heap(v2.begin(), v2.end())) {
        std::cout << "v2 is a heap" << std::endl;
        std::sort_heap(v2.begin(), v2.end());
    }
    for (auto iter = v2.begin(); iter != v2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void testSortedAlgorithms() {
    std::vector<int> v1 = {2, 5, 5, 7, 10};
    if (std::binary_search(v1.begin(), v1.end(), 7)) {
        std::cout << "7 is in v1" << std::endl;
    }
    std::vector<int> sub = {2, 7, 10};
    if (std::includes(v1.begin(), v1.end(), sub.begin(), sub.end())) {
        std::cout << "sub is included in v1" << std::endl;
    }
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> p_iter = std::equal_range(v1.begin(), v1.end(), 5);
    std::cout << "5 is from " << p_iter.first - v1.begin() << " to " << p_iter.second - v1.begin() - 1 << std::endl;

    std::vector<int> v2 = {2, 3, 9, 98};
    std::vector<int> v3;
    // std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin()); //error
    // for (auto iter = v3.begin(); iter != v3.end(); ++iter) {
    //     std::cout << *iter << " ";
    // }
    // std::cout << std::endl;

    std::vector<int> v4 = {1, 2, 5, 7, 2, 4, 5, 8, 9};
    std::inplace_merge(v4.begin(), v4.begin() + 4, v4.end());
    for (auto iter = v4.begin(); iter != v4.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::vector<int> v5 = {2, 2, 4, 7};
    std::vector<int> v6 = {2, 4, 8};
    std::vector<int> v7;
    // std::set_union(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin()); //error
    // std::set_intersection(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin()); //error
    // std::set_difference(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin()); //error
    // std::set_symmetric_difference(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin()); //error
    // for (auto iter = v7.begin(); iter != v7.end(); ++iter) {
    //      std::cout << *iter << " ";
    // }
    // std::cout << std::endl;
}

void testNumericAlgorithms() {
    std::vector<int> v1 = {1, 3, 5, 7, 9};
    int sum = std::accumulate(v1.begin(), v1.end(), 100);
    std::cout << "100 + sum(v1) = " << sum << std::endl;
    int product = std::accumulate(v1.begin(), v1.end(), 100, std::multiplies<int>());
    std::cout << "100 * product(v1) = " << product << std::endl;

    std::vector<int> v2 = {1, 3 ,2, 5, 2};
    int innerProduct = std::inner_product(v2.begin(), v2.end(), v1.begin(), 10);
    std::cout << "10 + dot(v1, v2) = " << innerProduct << std::endl;

    // std::vector<int> v3;
    // std::partial_sum(v2.begin(), v2.end(), v3.begin()); // error
    // std::cout << "v2[0] + v2[1] + v2[2] = " << v3[2] << std::endl;
    // std::partial_sum(v2.begin(), v2.end(), v3.begin(), std::multiplies<int>()); // error
    // std::cout << "v2[0] * v2[1] * v2[2] = " << v3[2] << std::endl;

    // std::vector<int> v3;
    // std::adjacent_difference(v2.begin(), v2.end(), v3.begin()); // error
    // std::cout << "v2[3] - v2[2] = " << v3[3] << std::endl;
    // std::adjacent_difference(v2.begin(), v2.end(), v3.begin(), std::plus<int>()); // error
    // std::cout << "v2[3] + v2[2] = " << v3[3] << std::endl;
}

void testString() {
    std::string s1("Hello", 2);
    std::cout << s1 << std::endl;
    std::string s2({'a', 'b', 'c', 'd', 'e'});
    std::string s3(s2, 1, 2);
    std::cout << s3 << std::endl;

    std::cout << s1.capacity() << std::endl;
    s1.reserve(100);
    std::cout << s1.capacity() << std::endl;
    s1.shrink_to_fit();
    std::cout << s1.capacity() << std::endl;
    s1.resize(5, 'a');
    std::cout << s1 << std::endl;

    s1.insert(2, "abcde", 3);
    std::cout << s1 << std::endl;
    s1.replace(2, 3, s2, 3, 2);
    std::cout << s1 << std::endl;
    s1.erase(1, 3);
    std::cout << s1 << std::endl;
    s1.swap(s2);
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;

    size_t found = s1.find("bcd");
    std::cout << found << std::endl;
    s1 = "abcdebcd";
    found = s1.find("bcd", 3);
    std::cout << found << std::endl;

    s2 = "debc";
    if (s1.compare(3, 4, s2) == 0) {
        std::cout << "s1[3]~s1[6] is equal to s2" << std::endl;
    }

    s1 = "143fawf";
    size_t i;
    std::cout << std::stoi(s1, &i) << std::endl;
    std::cout << i << std::endl;
    s1 = "fefg";
    std::cout << std::stoi(s1, &i) << std::endl; // exception
    std::cout << i << std::endl;
}

void testFileStream() {
    std::ofstream outFile("1.txt", std::ios::out);
    outFile << "Hello World!" << std::endl;
    outFile.close();

    std::ifstream inFile("1.txt", std::ios::in);
    std::cout << inFile.rdstate() << std::endl;
    std::cout << inFile.good() << std::endl;
    std::cout << inFile.bad() << std::endl;
    std::cout << inFile.fail() << std::endl;
    std::cout << inFile.eof() << std::endl;

    inFile.exceptions(std::ios::goodbit);

    inFile.clear(std::ios::goodbit);
    std::cout << inFile.rdstate() << std::endl;
    inFile.clear(std::ios::badbit);
    std::cout << inFile.rdstate() << std::endl;
    inFile.clear(std::ios::eofbit);
    std::cout << inFile.rdstate() << std::endl;
    inFile.clear(std::ios::failbit);
    std::cout << inFile.rdstate() << std::endl;

    inFile.exceptions(std::ios::failbit | std::ios::badbit);

    inFile.close();
}

void testStdStream() {
    std::cout << std::bitset<8>(15) << std::endl;
    std::cout << std::complex<int>(2,3) << std::endl;

    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout.setf(std::ios::showbase);
    std::cout << 17 << std::endl;
    std::cout.unsetf(std::ios::showbase);
    std::cout << 17 << std::endl;
    std::cout.setf(std::ios::dec, std::ios::basefield);
    std::cout.width(5);
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << 17 << 34 << 20 << std::endl;

    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout << 123.14342 << std::endl;
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision(3);
    std::cout << 123.14342 << std::endl;

    std::ostream myCout(std::cout.rdbuf());
    myCout << 432.32 << std::endl;

    std::ofstream outFile("1.txt", std::ios::out);
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
    std::cout << "Hi, Shazam!" << std::endl;
    std::cout.rdbuf(sbuf);
    std::cout << "Hi Shazam into file completed." << std::endl;

    std::istreambuf_iterator<char> i(std::cin);
    std::ostreambuf_iterator<char> o(std::cout);
    while (*i != 'x') {
        *o = *i;
        ++o;
        ++i;
    }

    std::copy(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(std::cout));
}

void testStringStream() {
    std::stringstream ss;
    ss << 34 << " hex: " << std::hex << 34;
    std::cout << ss.str() << std::endl;

    int a, b;
    ss >> std::hex >> a;
    ss.ignore(6);
    ss >> std::dec >> b;
    std::cout << a << " " << b << std::endl;
}

int main() {
    testStringStream();
    return 0;
}
