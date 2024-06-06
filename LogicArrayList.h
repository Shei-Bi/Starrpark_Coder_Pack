#ifndef LIST_ARRAY_LIST_H
#define LIST_ARRAY_LIST_H

template <class T>
class LogicArrayList
{
private:
	T* array;           // 数据
	int capacity = 5; // 数组容量
	// 扩容
	void ensureCapacity(int);
public:
	int length = 0;       // 元素个数
	LogicArrayList();
	void add(T t)
	{
		if (length == capacity) {
			if (length == 0) ensureCapacity(5);
			else ensureCapacity(length * 2);
		}
		array[length] = t;
		length++;
	}
	// 获取指定位置的元素
	T get(int index)
	{
		if (index < length && index > 0)
			return array[index];
	}
	T& operator[](int);
	// index位置元素设置为t
	/*T set(int index, T t)
	{
		if (index < siz&& index >; 0)
		{
			T old_v = data[index];
			data[index] = t;
			return old_v;
		}
	}*/

	//T remove(int index);
};
template<class T>
void LogicArrayList<T>::ensureCapacity(int count) {
	if (capacity < count) {
		capacity = count;
		T* newArr = new T[capacity];
		for (int i = 0;i < length;i++) {
			newArr[i] = array[i];
		}
		delete[] array;
		array = newArr;
	}
}
template<class T>
inline T& LogicArrayList<T>::operator[](int i) {
	return array[i];
}
template<class T>
LogicArrayList<T>::LogicArrayList() {
	capacity = 5;
	array = new T[capacity];
}
#endif