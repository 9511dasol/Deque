#include <iostream>
#include<cassert>
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <unordered_map>
using namespace std;

const char DECIMAL = '.';
const char RIGHT_PARENTHESIS = ')';

bool is_operator(char c); 
bool is_valid_char(char c); 
int precedence(char op);

template <typename T>
class node;

template <typename T>
class OurDeque {
public:
    //생성자
    OurDeque();
    OurDeque(T val);
    OurDeque(const OurDeque& copy);
    ~OurDeque();
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    bool empty() const;
    size_t size() const;
    void operator=(const OurDeque& addend);
    T front() const;
    T back() const;

private:
    node<T>* head = NULL;
    node<T>* tail = NULL;
    int size_ = 0;
    //복사용 포인터
    node<T>* cphead = NULL;
    node<T>* cptail = NULL;
    int cpsize = 0;
};

class evaluator {
public:
    string read_expression();
    string convert_to_postfix(string s);
    double evaluate_postfix(string s);
};

template <typename T>
class node {
    friend OurDeque<T>;
public:
    node(node* n, node* p, T val) {
        next = n;
        prev = p;
        this->value = val;
    }
    node(T val) {
        next = NULL;
        prev = NULL;
        this->value = val;
    }
private:
    T value; // value_type == double == 1
    node* next; // next node
    node* prev; // previous node
};

int main()
{
    evaluator eval;
    string infix, postfix;
    char choice;

    do {
        cout << "Type infix: ";

        infix = eval.read_expression();
        postfix = eval.convert_to_postfix(infix);

        cout << "Infix Expression: " << infix << endl;
        cout << "Postfix Expression: " << postfix << endl;

        double result = eval.evaluate_postfix(postfix);
        cout << "Evaluation Result: " << result << endl;

        cout << "Do you want to enter another expression? (y/n): ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character in the input buffer
    } while (choice == 'y' || choice == 'Y');

    std::cout << "Exiting the program. Goodbye!" << std::endl;

    return 0;
}
template <typename T>
OurDeque<T>::OurDeque(){}
template <typename T>
OurDeque<T>::OurDeque(T val) {
    head = tail = new node(val);
    size_ = 1;
}
template <typename T>
OurDeque<T>::OurDeque(const OurDeque& copy) {
    if (copy.size_ <= 0 || copy.head == NULL) {
        cout << "nono" << endl;
        return;
    } 
    node* cur = copy.tail;

    while (cur != NULL) {
        node* newnode = new node(cur->value);
        if (head == NULL) {
            cout << "This OurSet is Null" << endl;
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        ++size;
        cur = cur->prev;
    }
}
template <typename T>
OurDeque<T>::~OurDeque() {
    while (!empty()) {
        pop_front();
    }
}
template <typename T>
void OurDeque<T>::push_back(const T& value) {
    node<T>* newNode = new node<T>(value);
    if (empty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size_++;
}
template <typename T>
void OurDeque<T>::push_front(const T& value) {
    node<T>* newnode = new node<T>(value);
    if (empty()) {
        head = tail = newnode;
    }
    else {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    size_++;
}
template <typename T>
void OurDeque<T>::pop_back() {
    if (!empty()) {
        node<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = NULL;
        }
        else {
            head = NULL;
        }
        delete temp;
        size_--;
    }
}
template <typename T>
void OurDeque<T>::pop_front() {
    if (!empty()) {
        node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = NULL;
        }
        else {
            tail = NULL;
        }
        delete temp;
        size_--;
    }
}
template <typename T>
bool OurDeque<T>::empty() const {
    return size_ == 0;
}
template <typename T>
size_t OurDeque<T>::size() const {
    return size_;
}
template <typename T>
void OurDeque<T>:: operator=(const OurDeque& addend) {
    if (this == &addend) {
        cout << "They are same!!" << endl;
        cout << "operator=" << endl;
        cout << endl;
        return;
    }//
    else if (&addend == NULL) {
        cout << "the source You've selected is NULL!" << endl;

        while (head != NULL) {
            pop_front();
        }

        if (head == NULL || tail == NULL) {
            cout << "This OurSet is Null" << endl;
        }
        return;
    }
    else {
        if (head == NULL || tail == NULL) {
            cout << "OurSet is Null" << endl;
            return;
        }
        else {
            while (head != NULL) {
                pop_front();
            }

            if (head == NULL) {
                cout << "OurSet is finally Null" << endl;
            }
        }

        node* cur = addend.tail;
        while (cur != NULL) {
            push_front(cur->value);
            cur = cur->prev;
        }

    }
}
template <typename T>
T OurDeque<T>::front() const {
    if (!empty()) {
        return head->data;
    }
    throw out_of_range("Deque is empty");
}
template <typename T>
T OurDeque<T>::back() const {
    if (!empty()) {
        return tail->data;
    }
    throw out_of_range("Deque is empty");
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_valid_char(char c) {
    return std::isdigit(c) || std::isalpha(c) || is_operator(c) || c == '(' || c == ')';
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;  // '('의 우선순위는 0으로 설정
}

string evaluator::read_expression() {
    string expression;
    char c;

    while ((c = std::cin.get()) != '\n') {
        if (is_valid_char(c)) {
            // 유효한 문자인 경우
            if (expression.length() > 0 && !std::isspace(expression.back()) && !std::isspace(c)) {
                // 이전 문자가 공백이 아니고, 현재 문자도 공백이 아닌 경우 사이에 공백 추가
                expression += ' ';
            }
            expression += c;
        }
        else if (!std::isspace(c)) {
            // 유효하지 않은 문자인 경우 에러 메시지 출력 후 무시
            std::cerr << "Invalid character: " << c << std::endl;
        }
    }
    return expression;
}

string evaluator::convert_to_postfix(string s) {
    string postfixExpression;
    stack<char> operators;

    istringstream iss(s); // string을 입력받아 다른 형식으로 바꿔주는 기능
    string token;
    
    while (iss >> token) {
        if (std::isalnum(token[0])) { // isalnum 영문자 또는 숫자
            postfixExpression += token + " ";
        }
        else if (token[0] == '(') {
            operators.push('(');
        }
        else if (token[0] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfixExpression += operators.top();
                postfixExpression += ' ';
                operators.pop();
            }
            operators.pop();  // 여는 괄호를 pop하여 버림
        }
        else if (is_operator(token[0])) {
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(token[0])) {
                postfixExpression += operators.top();
                postfixExpression += ' ';
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        postfixExpression += operators.top();
        postfixExpression += ' ';
        operators.pop();
    }

    if (!postfixExpression.empty()) {
        postfixExpression.pop_back();
    }

    return postfixExpression;
}

double evaluator::evaluate_postfix(string s) {
    stack<double> operands;
    unordered_map<char, double> variables;

    istringstream iss(s);
    string token;

    while (iss >> token) {
        if (isalnum(token[0])) {
            if (isalpha(token[0])) {
                char variable = token[0];
                if (variables.find(variable) == variables.end()) {
                    std::cout << "Enter the value for variable '" << variable << "': ";
                    std::cin >> variables[variable];
                }
                operands.push(variables[variable]);
            }
            else {
                operands.push(std::stod(token));
            }
        }
        else if (is_operator(token[0])) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();

            if (token[0] == '+') {
                operands.push(operand1 + operand2);
            }
            else if (token[0] == '-') {
                operands.push(operand1 - operand2);
            }
            else if (token[0] == '*') {
                operands.push(operand1 * operand2);
            }
            else if (token[0] == '/') {
                if (operand2 != 0) {
                    operands.push(operand1 / operand2);
                }
                else {
                    std::cerr << "Error: Division by zero!" << std::endl;
                    return 0.0;  // 에러 발생 시 0을 반환
                }
            }
        }
    }
    if (!operands.empty()) {
        return operands.top();
    }
    else {
        std::cerr << "Error: Invalid postfix expression!" << std::endl;
        return 0.0;  // 에러 발생 시 0을 반환
    }
}