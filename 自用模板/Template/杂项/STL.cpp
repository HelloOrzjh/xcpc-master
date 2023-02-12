// 万能（误）算法头文件（部分）
#include <algorithm>
using namespace std; 
int main() {
    iterator begin, end; // 指代某种数据结构首尾迭代器
    T i, x, a, b;
    
    sort(begin, end, <cmp>); // 排序函数，默认从小到大
    // 遇到需要特殊排序的需要编写cmp函数 or 重载内部运算符
    next_permutation(begin, end); // 下一个排列
    prev_permutation(begin, end); // 前一个排列
    
    set_union(begin(a), end(a), begin(b), end(b), begin(c));
    // 取两个有序序列a、b的并集，存放到c中
    set_intersection(begin(a), end(a), begin(b), end(b), begin(c));
    // 取两个有序序列a、b的交集，存放到c中
    set_difference(begin(a), end(a), begin(b), end(b), begin(c));
    // 取两个有序序列a、b的差集，存放到c中
    unique(begin, end); // 有序数据去重
    merge(begin(a), end(a), begin(b), end(b), begin(c), cmp);
    // 合并两个有序序列a、b，存放到c中，cmp可定义新序列排列方式
    
    lower_bound(begin, end, x); // 返回x的前驱迭代器
    // 在普通的升序序列中，x的前驱指的是第一个大于等于x的值
    upper_bound(begin, end, x); // 返回x的后继迭代器
    // 在普通的升序序列中，x的后继指的是第一个大于x的值
    // 上述两个函数时间复杂度为O(log2(n))，内部实现是二分
    // 如果找不到这样的值，会返回end
    
    find(begin, end, x); // O(n)查找x
    binary_search(begin, end, x) // 二分查找x，返回bool
    min(a, b); max(a, b); // 返回a、b中的最小/最大值
    fill(begin, end, x); // 往容器的[begin, end)内填充x
    swap(a, b); // 交换a、b的值
    
    return 0;
}

// 动态数组（vector）、双向链表（list）
#include <vector>
#include <list>
using namespace std;
int main() {
    T i;
    unsigned int n, x;
    bool flag;
    iterator it;
    
    // 动态数组部分
    // 注意vector的空间需要预留两倍大小
    vector<T> v;
    v.push_back(i); // 往数组尾添加一个元素i
    v[x]; // 访问第x - 1个元素
    v.begin(); // 返回头元素的迭代器
    v.end(); // 返回末尾迭代器（尾元素的下一个）
    n = v.size(); // 数组中元素数量
    v.pop_back(); // 删除最后一个元素
    v.erase(it);  // 删除某个的元素
    v.insert(x, i);  // 在x位置插入元素i
    // erase、insert时间复杂度为O(n)
    v.clear(); // 清空数组，不释放空间
    flag = v.empty(); // 判断数组是否为空（真值）
    
    // 链表部分
    list<T> li;
    li.push_front(i); // 在链头添加一个元素i
    li.push_back(i); // 在链尾添加一个元素i
    li.pop_front(i); // 删除链表头元素
    li.pop_back(i); // 删除链表尾元素
    li.erase(it);  // 删除某个的元素
    li.insert(x, i);  // 在x位置插入元素i O(n)
    li.begin(); // 返回头元素的迭代器
    li.end(); // 返回末尾迭代器（尾元素的下一个）
    n = li.size(); // 链表中元素数量
    li.remove(i); // 删除链表中所有值为i的元素
    li.unique(); // 移除所有连续相同元素，留下一个
    li.reverse(); // 反转链表
    li.clear(); // 情况链表，不释放空间
    
    return 0;
}

// 普通队列、双端队列、优先队列
#include <queue> // 队列头文件
#include <deque> // 双端队列头文件
using namespace std;
int main() {
    T i; 
    unsigned int n, x; 
    bool flag;
    
    // 普通队列部分，注意queue没有迭代器
    queue<T> q, tmp_q;  // 定义普通队列
    q.push(i); // 队尾插入元素i
    q.pop();   // 弹出队首元素
    i = q.front(); // 访问队首元素
    i = q.back();  // 访问队尾元素
    n = q,size();  // 队内元素数量
    flag = q.empty(); // 判断队列是否为空（真值）
    q.swap(tmp_q); // 交换两个队列元素
    
    // 优先队列部分，注意其没有迭代器
    priority_queue<T> pq; // 定义优先队列
    pq.push(i); // 队尾插入元素i
    pq.pop();   // 弹出队首元素
    i = pq.top(); // 访问队首元素
    n = q,size();  // 队内元素数量
    flag = q.empty(); // 判断队列是否为空（真值）
    q.swap(tmp_q); // 交换两个队列元素
    // 注意优先队列内部是使用<运算符，默认大根堆
    // 可以采用重载运算符或加入运算符类自定义排列方式
    // 例：priority_queue<T, vector<T>, greater<T> > 小根堆
    /*
        struct node {
            int x, y;
        };
        bool operator < (node a, node b) {
            // 这里注意是<右边的元素会放在前面
            if(a.x != b.x) return a.x < b.x;
            else return a.y < b.y;
        }
        priority_queue<node>
    */
    
    // 双端队列部分
    // 注意deque用到了map来映射，时间复杂度上常数略大
    deque<T> dq; // 定义双端队列
    // 可以称为vector、list、queue的结合体
    // 用法类似，这里只给代码不做注释
    dq.push_back(i);
    dq.push_front(i);
    dq.front();
    dq.back();
    dq.pop_front();
    dq.pop_back();
    dq.begin();
    dq.end();
    dq[x];
    n = dq.size();
    flag = dq.empty();
    dq.insert(x, i);
    
    return 0;
}

// 栈
#include <stack>
using namespace std;
int main() {
    T i;
    unsigned int n;
    bool flag;
    
    stack<T> st; // 注意stack没有迭代器
    st.push(i); // 往栈顶加入一个元素
    st.pop(); // 弹出栈顶元素
    i = st.top(); // 获得栈顶元素的值
    flag = st.empty(); // 判断是否为空（真值）
    n = st.size(); // 获得栈内元素个数
    
    return 0;
}

// pair（成组）、set（有序元素序列）
#include <set>
#include <pair>
using namespace std;
int main() {
    T i;
    T1 t1;
    T2 t2;
    iterator it;
    unsigned int n;
    bool flag;
    
    // pair是将两种元素组成一对
    pair<T1, T2> p;
    p = make_pair(t1, t2); // 将t1、t2构造成一对
    // pair支持比较，遵循字典序
    p.first;  // 访问第一个元素，这里是t1
    p.second; // 访问第二个元素，这里是t2
    
    // set内部是RB-tree维护
    set<int> st; // 注意，set内元素不重复
    st.insert(i); // 往set内插入一个元素i
    	// 时间复杂度O(log2(n)) 这里会返回一个<pair>迭代器
    	// first指向插入元素后所在的迭代器
    	// second指向是否插入成功（真值）
    st.begin(); // 返回首迭代器
    st.end(); // 范围尾迭代器
    st.erase(it); st.erase(i);
    	// 删除某个元素
    st.equal_range(i); // 返回几何中与i相等的上下限两个迭代器
    flag = st.empty(); 
    n = st.size();
    st.clear();
    // set内置了lower_bound和upeer_bound函数
    // 用法和algorithm的一样
    
    // 可重复元素set
    multiset<int> mst;
    // 用法与set大致相同
    // 唯一不同只在删除函数上
    mst.erase(i); // 会删除所有值为i的元素
    
    return 0;
}

// 如果需要给set自定义排序顺序
struct CMP {
    bool operator() (const int& a, const int& b) const {
        return a > b; // 返回真值则代表左边的值优先级高
    }
};
multiset<int, CMP> mst;

// map（映射）
#include <map>
using namespace std;
int main() {
    T1 t1;
    T2 t2;
    
    // map将两种元素做映射，一种指向另一种
    // 内部也是RB-tree维护
    map<T1, T2> mp;
    mp[t1] = t2; // 直接让t1对应到t2
   	mp[t1]; // 访问t1对应的内容，时间复杂度O(log2(n))
    // 如果t1没有指向任何内容，则会返回T2类型的初始值
    
    return 0;
}

// 一些C++的功能/特性
#include <bits/stdc++.h> // 标准库头文件
using namespace std;
int main() {
    
    __int128 a; // 128位整数，最大值大概10^38次方
   	// C++11以上可用，无法用标准方法读入
    
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false); 
    // 关闭cin、cout同步流，此举后不可混用scanf/printf
    
    auto x; // 自动变量，可以是任意属性
    // 举个例子
    std::set<int> st;
    std::for(auto i:st); // C++版for_each
    // 其中i是auto变量，也可改成set<int>::iterator
    
    // 所有的STL容器push/insert操作都可替换为emplcace
    // 速度上减小常数（不用临时变量）
    // 例：
    int i;
    std::set<int> st;
    st.emplace(i);
    std::vector<int> vc;
    vc.emplace_back(i);
    
    return 0;
}

// 强大的pb_ds库
#include <bits/stdc++.h>
#include <bits/extc++.h> // 扩展库头文件
/*
 * 这里如果没有bits/extc++.h的话需要
 * ext/pb_ds/tree_policy.hpp
 * ext/pb_ds/assoc_container.hpp
 * ext/pb_ds/priority_queue_policy.hpp
 * ext/pb_ds/trie_policy.hpp
 * ext/rope
 * ...
 */
using namespace __gnu_pbds;
using namespace __gnu_cxx;
int main() {

    // 哈希表部分，用法与map一样，效率在C++11以下效率高
    // 注意，这部分在namespace __gnu_pbds下
    cc_hash_table<string, int> mp1; // 拉链法
    gp_hash_table<string, int> mp2; // 查探法(快一些)

    // 优先队列部分，比STL中高级
    priority_queue<int, std::greater<int>, TAG> pq;
    /*
     * 第一个参数是数据类型
     * 第二个是排序方式
     * 第三个是堆的类型
     * 其中堆的类型有下面几种
     * pairing_heap_tag
     * thin_heap_tag
     * binomial_heap_tag
     * c_binomial_heap_tag
     * binary_heap_tag
     * 其中pairing_heap_tag最快
     * 并且这个东西是带默认参数的，只需要定义一个int
     */
    // 比STL中的优先队列多了join和迭代器
    // 例子：
    priority_queue<int> pq1, pq2;
    pq1.join(pq2); // 会将pq2合并到pq1上
    pq1.begin(); pq1.end(); // 可遍历

    // 红黑树（平衡树）部分，与set相似，但更快
    tree <
        int,
        null_type,
        std::less<>,
        rb_tree_tag,
        tree_order_statistics_node_update
    > t, tre;
    /*
     * int 关键字类型
     * null_type 无映射（低版本g++为null_mapped_type）
     * less<int> 从小到大排序
     * rb_tree_tag 红黑树（splay_tree_tag splay）
     * tree_order_statistics_node_update 结点更新
     */
    int i, k;
    t.insert(i); // 插入
    t.erase(i); // 删除
    t.order_of_key(i);
    // 询问这个tree中有多少个比i小的元素
    t.find_by_order(k);
    // 找第k + 1小的元素的迭代器,如果order太大会返回end()
    t.join(tre); // tre合并到t上
    t.split(i, tre); // 小于等于i的保留，其余的属于tre
    // 基本操作有size()/empty()/begin()/end()等
    // 同样内置lower_bound/upper_bound

    // 可持久化平衡树部分
    // 注意，这部分在namespace __gun_cxx下
    rope<char> str;
    // 待我学习完后再更新

    return 0;
}