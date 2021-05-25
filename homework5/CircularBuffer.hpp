#ifndef INC_5_CIRCULARBUFFER_HPP
#define INC_5_CIRCULARBUFFER_HPP


//fixed warning
template<class Type>
class CircularBuffer {
private:
    Type *buffer;
    size_t capacity;
    size_t size = 0;
    size_t _begin = 0, _end = 0;

    class myIterator {
    private:
        Type *cur;
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type [[maybe_unused]] = Type;
        using difference_type = int;
        using reference = Type &;
        using pointer = Type *;

        explicit myIterator(pointer first) : cur(first) {}

        myIterator &operator++() {
            ++cur;
            return *this;
        }

        myIterator &operator--() {
            --cur;
            return *this;
        }

        reference operator*() {
            return *cur;
        }

        difference_type operator-(myIterator someIterator) {
            return cur - someIterator.cur;
        }

        myIterator operator-(int n) {
            return myIterator(cur - n);
        }

        myIterator operator+(int n) {
            return myIterator(cur + n);
        }

        bool operator!=(myIterator it) {
            return cur != it.cur;
        }

        bool operator==(myIterator it) {
            return cur == it.cur;
        }

        bool operator<(myIterator it) {
            return cur < it.cur;
        }
    };

public:

    explicit CircularBuffer(size_t _capacity) :
            capacity(_capacity) {
        buffer = new Type[capacity];
    };

    //todo O(1)
    void addFirst(Type data) {
        for (int i=size; i > 0; i--)
            buffer[i] = buffer[i - 1];
        buffer[0]=data;
        if (size < capacity)
            size++;
    }

    void addLast(Type data) {
        size++;
        _end = (_end + 1) % capacity;
        if (_begin == _end)
            _begin = (_begin + 1) % capacity;
        buffer[_end] = data;
    }

    //fixed return 0 if empty
    Type first() {
        if (size != 0) {
            return buffer[_begin];
        }
        return 0;
    }

    Type last() {
        if (size != 0) {
            return buffer[_end];
        }
        return 0;
    }

    const Type &operator[](unsigned index) const {
        if (index > size - 1)
            throw std::out_of_range("out of range, index is more than size");
        if (size > 0)
            return buffer[(_begin + index) % capacity];
        else
            throw std::out_of_range("out of range, size is less than 0");

    }

    //fixed more information in exceptions
    Type &operator[](unsigned index) {
        if (index > size - 1)
            throw std::out_of_range("out of range, index is more than size");
        if (size > 0)
            return buffer[(_begin + index) % capacity];
        else
            throw std::out_of_range("out of range, size is less than 0");
    }

    void delFirst() {
        if (size > 0) {
            buffer[_begin] = 0;
            _begin = (_begin + 1) % capacity;
            size--;
        }
    }

    void delLast() {
        if (size > 0) {
            buffer[_end] = 0;
            _end = (_end - 1) % capacity;
            size--;
        }
    }

    void changeCapacity(int cap) {
        Type *Newbuffer = new Type[cap];
        for (size_t i = 0; i < capacity % cap; i++) {
            Newbuffer[i] = buffer[i];
        }
        //fixed delete[]
        delete[] buffer;
        buffer = Newbuffer;
        capacity = cap;
    }

    myIterator begin() const {
        return myIterator(buffer);
    }

    myIterator end() const {
        return myIterator(&buffer[size]);
    }

};


#endif //INC_5_CIRCULARBUFFER_HPP
