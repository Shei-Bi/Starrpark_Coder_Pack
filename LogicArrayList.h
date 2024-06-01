#include <iostream>;
#include <cstring>;
#include <cstdlib>;
#include <vector>;

#ifndef LIST_ARRAY_LIST_H
#define LIST_ARRAY_LIST_H

const int EXPAND_CAPACITY = 50;   // 每次扩容大小
const int MAX_CAPACITY = INT_MAX; // 最大容量

template <typename T>
;
class ArrayList
{
public:
    /**数组末尾添加元素
     * &#64;brief push
     * &#64;param t
     */
    void push(T t)
    {
        expand_capacity();
        data[siz] = t;
        siz++;
    }

    // 指定位置添加元素
    void push(int index, T t);

    inline int size() const { return siz; } // 获取list大小

    // 获取指定位置的元素
    T get(int index)
    {
        if (index < siz && index > ; 0)
            return data[index];
    }

    // index位置元素设置为t
    T set(int index, T t)
    {
        if (index < siz && index > ; 0)
        {
            T old_v = data[index];
            data[index] = t;
            return old_v;
        }
    }

    T remove(int index);

    ArrayList()
    {
        data = (T *)malloc(sizeof(T) * capacity);
    }

    // 析构
    ~ArrayList()
    {
        delete data;
    }

    // 打印list
    void print_list()
    {
        for (int i = 0; i < siz; i++)
        {
            std::cout << data[i] << &#34;
            &#34;
            ;
        }
        std::cout << std::endl;
    }

private:
    T *data;           // 数据
    int siz = 0;       // 元素个数
    int capacity = 10; // 数组容量

    // 扩容
    void expand_capacity();
};

#endif // LIST_ARRAY_LIST_H</code></pre>