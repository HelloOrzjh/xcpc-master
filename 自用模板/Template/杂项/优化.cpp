// 关闭iostream同步流
std::ios::sync_with_stdio(false); std::cin.tie(0);
// 如果编译开启了 C++11 或更高版本，建议使用 std::cin.tie(nullptr);
// 注意，此后不可和scanf/printf混用

// 普通快读快写
inline void read_int(int &X) {
    X = 0; int w = 0; char ch = 0;
    while(!isdigit(ch)) w |= ch=='-', ch = getchar();
    while( isdigit(ch)) X = (X<<3)+ (X<<1) + (ch-48), ch = getchar();
    X = w ? -X : X;
}

inline void write_int(int x) {
    static int sta[65];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while(x);
    while(top) putchar(sta[--top] + 48); 
}

// fread快读
namespace fastIO {
#define BUF_SIZE 100000
    //fread -> read
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while (blank(ch = nc()));
        if (IOerror) return;
        for (x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
#undef BUF_SIZE
};
using namespace fastIO;

// 手动扩栈
#pragma comment(linker, "/STACK:1024000000,1024000000") 

// O2 O3优化
#pragma GCC optimize(2)
#pragma GCC optimize(3)