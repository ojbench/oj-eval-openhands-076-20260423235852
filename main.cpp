#include <iostream>
#include <string>
#include <sstream>

template<typename ValueType>
class MyList
{
private:
    struct Node {
        ValueType value;
        Node* next;
        Node* prev;
        
        Node(const ValueType& val) : value(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int list_size;
    
public:
    MyList() : head(nullptr), tail(nullptr), list_size(0) {}
    
    MyList(MyList &&obj) noexcept : head(obj.head), tail(obj.tail), list_size(obj.list_size) {
        obj.head = nullptr;
        obj.tail = nullptr;
        obj.list_size = 0;
    }
    
    MyList(const MyList &obj) : head(nullptr), tail(nullptr), list_size(0) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    
    ~MyList() {
        clear();
    }
    
    MyList& operator=(const MyList &obj) {
        if (this != &obj) {
            clear();
            Node* current = obj.head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }
    
    MyList& operator=(MyList &&obj) noexcept {
        if (this != &obj) {
            clear();
            head = obj.head;
            tail = obj.tail;
            list_size = obj.list_size;
            obj.head = nullptr;
            obj.tail = nullptr;
            obj.list_size = 0;
        }
        return *this;
    }
    
    void push_back(const ValueType &value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }
    
    void pop_back() {
        if (tail == nullptr) return;
        
        Node* to_delete = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete to_delete;
        list_size--;
    }
    
    void push_front(const ValueType &value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }
    
    void pop_front() {
        if (head == nullptr) return;
        
        Node* to_delete = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete to_delete;
        list_size--;
    }
    
    ValueType &front() const {
        return head->value;
    }
    
    ValueType &back() const {
        return tail->value;
    }
    
    void insert(int index, const ValueType &value) {
        if (index <= 0) {
            push_front(value);
            return;
        }
        if (index >= list_size) {
            push_back(value);
            return;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        Node* new_node = new Node(value);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        list_size++;
    }
    
    void erase(int index) {
        if (index < 0 || index >= list_size || head == nullptr) return;
        
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == list_size - 1) {
            pop_back();
            return;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }
    
    int size() const {
        return list_size;
    }
    
    bool empty() const {
        return list_size == 0;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;
        list_size = 0;
    }
    
    void link(const MyList &obj) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    
    MyList cut(int index) {
        MyList result;
        
        if (index <= 0 || index >= list_size || head == nullptr) {
            return result;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        result.head = current;
        result.tail = tail;
        result.list_size = list_size - index;
        
        tail = current->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        current->prev = nullptr;
        
        list_size = index;
        
        return result;
    }
    
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value;
            if (current->next != nullptr) {
                std::cout << " ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    int n;
    std::cin >> n;
    
    MyList<int>* lists = new MyList<int>[n];
    
    int m;
    std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        std::string command;
        std::cin >> command;
        
        if (command == "push_back") {
            int list_id, value;
            std::cin >> list_id >> value;
            lists[list_id].push_back(value);
        } else if (command == "pop_back") {
            int list_id;
            std::cin >> list_id;
            lists[list_id].pop_back();
        } else if (command == "push_front") {
            int list_id, value;
            std::cin >> list_id >> value;
            lists[list_id].push_front(value);
        } else if (command == "pop_front") {
            int list_id;
            std::cin >> list_id;
            lists[list_id].pop_front();
        } else if (command == "insert") {
            int list_id, index, value;
            std::cin >> list_id >> index >> value;
            lists[list_id].insert(index, value);
        } else if (command == "erase") {
            int list_id, index;
            std::cin >> list_id >> index;
            lists[list_id].erase(index);
        } else if (command == "link") {
            int list_id1, list_id2;
            std::cin >> list_id1 >> list_id2;
            lists[list_id1].link(lists[list_id2]);
        } else if (command == "cut") {
            int list_id1, list_id2, index;
            std::cin >> list_id1 >> list_id2 >> index;
            lists[list_id2] = lists[list_id1].cut(index);
        } else if (command == "size") {
            int list_id;
            std::cin >> list_id;
            std::cout << lists[list_id].size() << std::endl;
        } else if (command == "empty") {
            int list_id;
            std::cin >> list_id;
            std::cout << (lists[list_id].empty() ? "true" : "false") << std::endl;
        } else if (command == "clear") {
            int list_id;
            std::cin >> list_id;
            lists[list_id].clear();
        } else if (command == "front") {
            int list_id;
            std::cin >> list_id;
            std::cout << lists[list_id].front() << std::endl;
        } else if (command == "back") {
            int list_id;
            std::cin >> list_id;
            std::cout << lists[list_id].back() << std::endl;
        } else if (command == "print") {
            int list_id;
            std::cin >> list_id;
            lists[list_id].print();
        }
    }
    
    delete[] lists;
    return 0;
}
