#ifndef INC_5_CIRCULARBUFFER_HPP
#define INC_5_CIRCULARBUFFER_HPP


template<class Type>
class CircularBuffer {
private:
    Type *buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t size = 0;
    size_t capacity;

    class myIterator {
    private:
        Type *cur;
        Type *buf;
        size_t tail;
        size_t index;
        size_t capacity;
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type [[maybe_unused]] = Type;
        using difference_type = int;
        using reference = Type &;
        using pointer = Type *;

        explicit myIterator(pointer first, pointer buffer, size_t tail_id, size_t id, size_t cap) : cur(first),
                                                                                                    buf(buffer),
                                                                                                    tail(tail_id),
                                                                                                    index(id),
                                                                                                    capacity(cap) {}

        myIterator &operator++() {
            ++cur;
            ++index;
            return *this;
        }

        myIterator &operator--() {
            --cur;
            --index;
            return *this;
        }

        reference operator*() {
            return buf[(tail + capacity - 1 - index) % capacity];
        }

        difference_type operator-(myIterator someIterator) {
            return cur - someIterator.cur;
        }

        myIterator operator-(int n) {
            return myIterator(cur - n, buf, tail, index - n, capacity);
        }

        myIterator operator+(int n) {
            return myIterator(cur + n, buf, tail, index + n, capacity);
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

        bool operator>(myIterator it) {
            return cur > it.cur;
        }
    };

public:
    CircularBuffer(size_t i) : capacity(i) {
        buffer = new Type[i];
    }


    void addFirst(Type data) {
        buffer[tail] = data;
        if (size == capacity) {
            if (tail == capacity - 1) {
                tail = 0;
                head = 0;
            } else {
                tail++;
                head++;
            }
        } else {
            tail = (tail + 1) % capacity;
            size++;
        }
    }

    void addLast(Type data) {
        if (size == capacity) {
            buffer[head] = data;
        } else {
            head = (head + capacity - 1) % capacity;
            buffer[head] = data;
            size++;
        }
    }


    Type first() {
        return buffer[(tail + capacity - 1) % capacity];
    }

    Type last() {
        return buffer[head];
    }

    void delFirst() {
        if (size > 0) {
            tail = (tail + capacity - 1) % capacity;
            size--;
        } else
            throw std::out_of_range("nothing to delete, buffer is empty");
    }

    void delLast() {
        if (size > 0) {
            head = (head + 1) % capacity;
            size--;
        } else
            throw std::out_of_range("nothing to delete, buffer is empty");
    }

    void changeCapacity(size_t i) {
        Type *Newbuffer = new Type[i];
        Newbuffer[0] = buffer[head];
        head = (head + 1) % capacity;
        size_t it = 1;
        while (head != tail) {
            Newbuffer[it] = buffer[head];
            head = (head + 1) % capacity;
            it++;
        }
        head = 0;
        tail = size;
        delete[] buffer;
        buffer = Newbuffer;
        capacity = i;
    }

    const Type &operator[](unsigned index) const {
        if (index > size - 1) {
            std::string str =
                    "out of range, index(" + std::to_string(index) + ") is more than size(" + std::to_string(size - 1) +
                    ")";
            throw std::out_of_range(str);
        }
        if (size > 0)
            return buffer[(tail + capacity - 1 - index) % capacity];
        else
            throw std::out_of_range("out of range, size is less than 0"); //shiiish

    }

    Type &operator[](unsigned index) {
        if (index > size - 1) {
            std::string str =
                    "out of range, index(" + std::to_string(index) + ") is more than size(" + std::to_string(size - 1) +
                    ")";
            throw std::out_of_range(str);
        }
        if (size > 0)
            return buffer[(tail + capacity - 1 - index) % capacity];
        else
            throw std::out_of_range("out of range, size is less than 0");
    }

    myIterator begin() const {
        return myIterator(buffer, buffer, tail, 0, capacity);
    }

    myIterator end() const {
        return myIterator(&buffer[size], buffer, tail, size, capacity);
    }
};


#endif //INC_5_CIRCULARBUFFER_HPP
