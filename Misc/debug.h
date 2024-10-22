template<class Os, typename A, typename B>
Os& operator<<(Os &os, const std::pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template<class Os, typename T_container,
typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value,
typename T_container::value_type>::type>
Os& operator<<(Os &os, const T_container &v) {
    os << '{'; std::string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

void dbg_out() { std::cerr << "\033[39m" << std::endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    std::cerr << H; std::cerr << (sizeof...(T) ? ", " : "]"); dbg_out(T...); 
}

#define dbg(...) std::cerr << __func__ << ":" << "LINE(" << __LINE__ << ") -> \
[" << #__VA_ARGS__ << "]: [", dbg_out(__VA_ARGS__)

#define mrd(...) std::cerr << "\033[91m" << __func__ << ":" << "LINE(" << __LINE__ << ") -> \
[" << #__VA_ARGS__ << "]: [", dbg_out(__VA_ARGS__)
