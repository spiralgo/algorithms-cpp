#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

template <typename T>
class LinkedList
{
private:
    void out_of_range(int idx)
    {
        std::cerr << "Index out of range error:" << endl;
        printf("Index %d for list of size %d\n", idx, size);
        throw std::out_of_range("Out of range");
    }
    uint32_t size = 0;
    struct Node
    {
        T val;
        Node *prev = nullptr;
        Node *next = nullptr;
        Node(){};
        Node(T val) { this->val = val; };
    };
    Node *head = nullptr;
    Node *tail = nullptr;
    struct node_index_pair
    {
        uint32_t idx = -1;
        Node *node = nullptr;
        node_index_pair(){};
        node_index_pair(uint32_t idx, Node *node)
        {
            this->idx = idx;
            this->node = node;
        }
    };

    node_index_pair *find_pair(T val)
    {
        if (size == 0)
        {
            return new node_index_pair();
        }
        Node *base = head;
        int idx = 0;
        while (base != nullptr)
        {
            if (base->val == val)
            {
                return new node_index_pair(idx, base);
            }
            idx++;
            base = base->next;
        }
        return new node_index_pair();
    }

public:
    LinkedList() {}
    LinkedList(T val)
    {
        head = new Node(val);
        tail = head;

        size = 1;
    }
    LinkedList(initializer_list<T> vals)
    {
        for (T val : vals)
        {
            this->add(val);
        }
    }

    T get_first()
    {
        return head->val;
    }
    T get_last()
    {
        return tail->val;
    }

    T poll()
    {
        if (size == 0)
        {
            out_of_range(0);
        }
        T val = head->val;
        Node *new_head = head->next;
        if (size > 1)
        {
            new_head->prev = nullptr;
        }
        else if (size == 1)
        {
            tail = nullptr;
        }
        free(head);
        head = new_head;
        size--;
        return val;
    }

    T pop()
    {
        if (size == 0)
        {
            out_of_range(0);
        }
        T val = tail->val;
        Node *new_tail = tail->prev;
        if (size > 1)
        {
            new_tail->next = nullptr;
        }
        else if (size == 1)
        {
            head = nullptr;
        }
        free(tail);
        tail = new_tail;
        size--;
        return val;
    }

    void add(T val)
    {
        if (size == 0 || head == nullptr)
        {
            head = new Node(val);
            tail = head;
            size = 1;
            return;
        }

        Node *new_tail = new Node(val);

        tail->next = new_tail;

        new_tail->prev = tail;

        tail = new_tail;
        size++;
    }
    uint32_t find(T val)
    {
        node_index_pair* find_n = this->find_pair(val);
        uint32_t idx = find_n->idx;
        free(find_n);
        return idx;
    }
    void remove(T val, int idx)
    {
    }

    void add(T val, int idx)
    {
        if (size == 0)
        {
            if (idx == 0)
            {
                add(val);
            }
            else
            {
                out_of_range(idx);
            }
        }
        if (idx == size)
        {
            add(val);
        }
        if (idx > size)
        {
            out_of_range(idx);
        }

        Node *inserted = new Node(val);

        if (idx == 0)
        {
            inserted->next = head;
            head = inserted;
            size++;
            return;
        }

        Node *base = head;

        while (idx-- > 0)
        {
            base = base->next;
        }
        inserted->next = base;
        inserted->prev = base->prev;
        base->prev->next = inserted;
        base->prev = inserted;
        size++;
    }

    T get(int idx)
    {
        if (idx >= this->size)
        {
            try
            {
                out_of_range(idx);
            }
            catch (std::exception &e)
            {
                return NULL;
            }
        }

        Node *base = head;

        while (idx-- > 0)
        {
            base = base->next;
        }
        return base->val;
    }

    bool set(int idx, T val)
    {
        if (idx >= this->size)
        {
            try
            {
                out_of_range(idx);
            }
            catch (std::exception &e)
            {
                return false;
            }
        }

        Node *base = head;

        while (idx-- > 0)
        {
            base = base->next;
        }

        base->val = val;
        return true;
    }
    uint32_t get_size()
    {
        return size;
    }
    string to_string()
    {
        if (size == 0)
        {
            return "[]";
        }
        string str = "[";
        Node *node = head;
        while (true)
        {
            // only works for int, long, char etc.
            str.append(std::to_string(node->val));
            if (node->next != nullptr)
            {
                str.append(", ");
                node = node->next;
            }
            else
            {
                break;
            }
        }
        str.append("]");
        return str;
    }
};

int main(int argc, char const *argv[])
{

    LinkedList<int> *i_nums = new LinkedList<int>({1, 2, 3, 4});
    cout << i_nums->to_string() << endl;
    i_nums->add(0, 0);
    cout << i_nums->to_string() << endl;
    cout << "size: " << i_nums->get_size() << endl;
    i_nums->add(9, 2);
    cout << i_nums->to_string() << endl;
    cout << i_nums->find(3) << endl;
    return 0;
}