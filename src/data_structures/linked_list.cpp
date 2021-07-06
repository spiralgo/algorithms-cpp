#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

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
    int size = 0;
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

    struct NodeIndexPair
    {
        uint32_t idx = -1;
        Node *node = nullptr;
        NodeIndexPair(){};
        NodeIndexPair(uint32_t idx, Node *node)
        {
            this->idx = idx;
            this->node = node;
        }
    };

    NodeIndexPair *find_pair(T val)
    {
        if (size == 0)
        {
            return new NodeIndexPair();
        }
        Node *base = head;
        int idx = 0;
        while (base != nullptr)
        {
            if (base->val == val)
            {
                return new NodeIndexPair(idx, base);
            }
            idx++;
            base = base->next;
        }
        return new NodeIndexPair();
    }

    Node *node_at_idx(int idx)
    {
        if (idx >= (int)this->size || (idx < 0 && idx*(-1) > this->size) )
        {
            out_of_range(idx);
        }

        if (idx == 0 || idx == this->size*(-1))
        {
            return head;
        }
        else if(idx == -1 || idx == this->size-1)
        {
            return tail;
        }

        Node *base;
        
        if(idx < 0)
        {
            base = tail;

            while (++idx < 0)
            {
                base = base->prev;
            }
            return base;            
        }

        base = head;

        while (idx-- > 0)
        {
            base = base->next;
        }
        return base;
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
        if (head == nullptr)
        {
            out_of_range(0);
        }
        return head->val;
    }
    T get_last()
    {
        if (head == nullptr)
        {
            out_of_range(-1);
        }
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
            out_of_range(-1);
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
        NodeIndexPair *find_n = this->find_pair(val);
        uint32_t idx = find_n->idx;
        free(find_n);
        return idx;
    }

    bool remove_at(int idx)
    {
        Node* rem = node_at_idx(idx);
        if(idx == 0 || idx == size*(-1))
        {
            if(size == 1)
            {
                free(head);
                head = nullptr;
                tail = nullptr;
                size--;
                return true;
            }
            head = head->next;
            free(head->prev);
            head->prev = nullptr;
            size--;
            return true;
        }
        else if(idx == size-1 || idx == -1)
        {
            tail = tail->prev;
            free(tail->next);
            tail->next = nullptr;
            size--;
            return true;
        }
        else
        {
            rem->next->prev = rem->prev;
            rem->prev->next = rem->next;
            free(rem);
            size--;
            return true;
        }
    }
    void remove_first()
    {
        remove_at(0);
    }

    void remove_last()
    {
        remove_at(-1);
    }

    bool remove(T val)
    {
        NodeIndexPair *rem = this->find_pair(val);
        int idx = rem->idx;
        if(idx == 0 || idx == size*(-1))
        {
            if(size == 1)
            {
                free(head);
                head = nullptr;
                tail = nullptr;
                size--;
                return true;
            }
            head = head->next;
            free(head->prev);
            head->prev = nullptr;
            size--;
            return true;
        }
        else if(idx == size-1 || idx == -1)
        {
            tail = tail->prev;
            free(tail->next);
            tail->next = nullptr;
            size--;
            return true;
        }
        else
        {
            Node* node =rem->node;
            node->next->prev = node->prev;
            node->prev->next = node->next;
            free(node);
            size--;
            return true;
        }
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
        if (idx > this->size)
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

        Node *base = node_at_idx(idx);
        
        inserted->next = base;
        inserted->prev = base->prev;
        base->prev->next = inserted;
        base->prev = inserted;
        size++;
    }

    void add_all(LinkedList<T>* vals)
    {
        Node* base = vals->head;
        while(base != nullptr)
        {
            add(base->val);
        }
    }

    void add_all(initializer_list<T> vals)
    {
        for (T val : vals)
        {
            this->add(val);
        }
    }

    T get(int idx)
    {
        Node *base; 
        try
        {
            base = node_at_idx(idx);
        }
        catch(const std::exception& e)
        {
            return NULL;
        }
        return base->val;
    }

    bool set(int idx, T val)
    {
        Node *base; 
        try
        {
            base = node_at_idx(idx);
        }
        catch(const std::exception& e)
        {
            return false;
        }
        base->val = val;
        return true;
    }

    bool contains(T val)
    {
        NodeIndexPair *node = find_pair(val);
        if(node->node == nullptr)
        {
            return false;
        }

        return true;
    }

    bool is_empty()
    {
        return size == 0;
    }

    uint32_t get_size()
    {
        return this->size;
    }

    T* data()
    {
        T* arr = (T*) malloc(size * sizeof(T));
        Node* base = head;
        for(int i = 0; i<size; i++)
        {
            arr[i] = base->val;
            base = base->next;
        }
        return arr;
    }

    std::vector<T>* to_vector()
    {
        vector<T>* vec = new vector<int>(size);
        Node* base = head;
        for(int i = 0; i<size; i++)
        {
            (*vec)[i] = base->val;
            base = base->next;
        }
        return vec;
    }

    string to_string()
    {
        if (size == 0)
        {
            return "[]";
        }
        string str = "[";
        Node *node = head;
        while (node != nullptr)
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
    
    private: 

    class Iterator
    {
        Node* curr;
        
        public :
        T get()
        {
            T val = curr->val;
            curr = curr->next;
            return val;
        }
        bool has_next()
        {
            return curr != nullptr;
        }
        Iterator(Node* head) {curr = head;}
    };

    Iterator iterator = Iterator(head);
    
    public: 

    void set_iterator()
    {
        iterator = Iterator(head);
    }
    bool has_next()
    {
        return iterator.has_next();
    }


    T next()
    {
        return iterator.get();
    }
};

int main(int argc, char const *argv[])
{

    LinkedList<int> *i_nums = new LinkedList<int>({1, 2, 3, 4});
    i_nums->add(9);
    
    i_nums->set_iterator();
    while(i_nums->has_next())
    {
        int a = i_nums->next();
        cout << a << endl;
    }
}
