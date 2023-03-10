#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <list>
#include <forward_list>
#include <set>
#include <iterator>
#include <unordered_set>
#include <optional>

// answer


//template<typename T>
//auto get_fib(T x) -> Trequires std::is_integral_v<T> {
//    if (x < 1) {}
//    else if (x < 3) {
//        return std::forward<T>(1);
//    }
//    return get_fib(x - 1) + get_fib(x - 2);
//}
//
//template<unsigned N>
//struct fib {
//    enum {
//        value = fib<N - 1>::value + fib<N - 2>::value //recursive
//    };
//};
//template<>
//struct fib<1> {
//    enum {
//        value = 1
//    };
//};
//template<>
//struct fib<2> {
//    enum {
//        value = 1
//    };
//};
//
//#define get_fib_(n) (fib<n>::value)
//
//void f102() {
//    int x = 0;
//    int y = 0;
//    std::cin >> x >> y;
//    auto f = [&x, &y]() { std::cout << x + y << std::endl; };
//    f();
//
//}

//#include <cmath>
//
//auto fibonacci(int n) -> std::vector<int> {
//    std::vector<int> nums{1, 1};
//    if (n == 0) {
//        return std::vector<int>{};
//    } else if (n == 1) {
//        return std::vector<int>{1};
//    } else if (n == 2) {
//        return nums;
//    }
//
//    for (size_t i = 3; i <= static_cast<size_t>(n); ++i) {
//        nums.emplace_back(nums[i - 2] + nums[i - 3]);
//    }
//    return nums;
//}
//
//
//void srt2(auto &x, auto &y)requires std::is_same_v<std::remove_cvref_t<decltype(x)>, std::remove_cvref_t<decltype(y)>> {
//    if (x > y) {
//        std::swap(x, y);
//    }
//}
//
//auto srt3(auto &a, auto &b, auto &c) {
//    if (srt2(a, b);b < c) return;
//    if (std::swap(b, c);a < b) return;
//    std::swap(a, b);
//}

//
//enum paint {
//    red,
//    green,
//    blue,
//    yellow,
//    cyan,
//    magenta,
//    brown
//};


//
//using mixer_fn = std::optional<paint>(paint, paint);
//
//auto wacky_colour(paint p1, paint p2) -> std::optional<paint> {
//    switch (p1) {
//        case red:
//            if (p2 == green) return yellow;
//            else if (p2 == blue) return magenta;
//            else return {};
//        case green:
//            if (p2 == blue) return cyan;
//            else return {};
//        case yellow:
//            if (p2 == magenta || p2 == cyan) return brown;
//            else return {};
//        case cyan:
//            if (p2 == magenta) return brown;
//            else return {};
//        case brown:
//            if (p2 == brown) return brown;
//            else return {};
//        default:
//            return {};
//    }
//}
//
//auto mix(const std::vector<paint> &paints, std::function<mixer_fn> fn = wacky_colour) -> std::optional<paint> {
//    if (paints.at(0) == magenta || paints.at(0) == blue) return {};
//    std::optional<paint> p1_cur = paints.at(0);
//    for (__SIZE_TYPE__ i = 1; i < paints.size(); ++i) {
//        auto p2_cur = paints.at(i);
//        p1_cur = fn(p1_cur.value(), p2_cur);
//        if (!p1_cur.has_value()) return {};
//    }
//    return p1_cur;
//}


///* 1 */ auto put(char x1) -> void{
//    std::cout << "1";
//};
///* 2 */ auto put(int x2) -> void{
//    std::cout << "2";
//}
///* 3 */ auto put(const char& x3) -> void{
//    std::cout << "3";
//}
///* 4 */ auto put(char & x4) -> void{
//    std::cout << "4";
//}

///* 1 */ auto memcpy(char *dst, const char *src, int n = 0) -> void *{
//    std::cout << "1";
//    return nullptr;
//}
///* 2 */ auto memcpy(const char *dst, char * const src) -> char *{
//    std::cout << "2";
//    return nullptr;
//}


///* 1 */ auto min(int(&arr)[2]) -> int{
//    std::cout << "1";
//    return 1;
//}
///* 2 */ auto min(int *arr) -> int{
//    std::cout << "2";
//    return 2;
//}
///* 3 */ auto mint(int(&arr)[]) -> int{
//    std::cout << "3";
//    return 3;
//}
//
//
//auto fn(int buf[3]) -> void {
//    min(buf);
//}

///* 1 */ auto sink(int i, ...){std::cout << "1";}
///* 2 */ auto sink(int i, short s){std::cout << "2";}
///* 3 */ auto sink(...){std::cout << "3";}

//
//
//auto vsort(std::vector<std::string> &vs) -> void {
//
//    auto vowel_sort = [&](const std::string& a_word, const std::string& b_word) -> bool{
//        std::size_t a_nv = 0;
//        std::size_t b_nv = 0;
//        const std::unordered_set<char> vowel{'a','e','i','o','u'};
//        for (const auto& c: a_word) {
//            if (vowel.count(c))
//                a_nv++;
//
//        }
//        for (const auto& c_: b_word) {
//            if (vowel.count(c_))
//                b_nv++;
//        }
//        // return a_nv==b_nv ? a_word<b_word : a_nv<b_nv;
//    };
//    std::sort(vs.begin(),vs.end(),vowel_sort);
//}


// void f_m() {
    //    int a= -1;
    //    std::cout<<signbit(a);
    //    std::cout<< get_fib_(10);
    //    std::string a = "1";
    //    std::string b = ".";
    //    std::string c = "a";
    //    srt3(a, b, c);
    //    std::cout << a << b << c << std::endl;
    //    std::function<void()> fn = []() {  };

    //    char x = 'x';
    //    char y = 'y';
    //    char *dst = &x;
    //    const char *src = &y;
    //    auto *ptr = memcpy(dst, src);

    //    int buf[] = {0,1,2,3,4};
    //    fn(buf);
    //    auto L = std::numeric_limits<long>::max();
    //    sink(1, L);

    //    std::vector<std::string> test_case = {"ff","dd","cc","gg","bb"};
    //    vsort(test_case);
    //    std::vector<std::string> expected = {"bb","cc","dd","ff","gg"};
    //    auto a=0 ;auto b =0;
    //    auto y = std::minmax_element(test_case.begin(),test_case.end());
    //    std::vector<int> marks{10,12,10,13};
    //
    //    auto marks_(marks);
    //    std::sort(marks_.begin(), marks_.end());
    //    auto xx = marks_.size()%2 ? marks_[marks_.size()/2] : (marks_[marks_.size()/2]+marks_[marks_.size()/2 -1]);
    //    std::cout<< xx;
    //    auto iter = std::istream_iterator<int>(std::cin);
    //    std::cout<<*iter;
//}

int main() {
    // std::cout << "run time"<< std::endl;

    static constexpr auto k = 4u;
    static constexpr auto k_ = 5u;
    static constexpr auto hval = 31u;

    static constexpr uint32_t mask = 0xFFFFFFFF;
    static constexpr auto mask_ = std::numeric_limits<uint32_t>::max();
    static_assert(0xFFFFFFFF==-1);
    static_assert(mask_ == mask);
    static_assert(mask_ == 0xFFFFFFFF);

    static constexpr auto f_hash=
            [&](uint32_t hval, auto k, auto mask) consteval -> uint32_t {
        return hval & (mask>>(32-k));
    };

    constexpr auto output = f_hash(hval, k,mask);
    constexpr auto output_ = hval & (mask>>(32-k_));
    static_assert(output == 15);
    static_assert(output_ == 31);

    return 0;
}
