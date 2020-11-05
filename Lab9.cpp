#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void wait() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
}

template <typename T>
struct Node {
	T data;
	Node * next;
};

template <typename T>
class Stack {
  private:
	Node<T> * head;
	int size;
  public:
	Stack() {
		head = NULL;
		size = 0;
	}

	void push(T s) {
		Node<T> * newHead = new Node<T>;

		newHead->data = s;
		newHead->next = head;
		head = newHead;

		size++;
	}

	T pop() {
		if (size == 0) {
			return -1;
		}
		Node<T> * temp;
		T result;

		temp = head;
		head = head->next;
		result = temp->data;

		delete temp;
		size--;

		return result;
	}

	char top() {
		if (size == 0) {
			return -1;
		}
		return head->data;
	}

	bool isEmpty() {
		return !isNotEmpty();
	}

	bool isNotEmpty() {
		return size;
	}
};

bool isLetter(char c) {
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

bool isNumber(char c) {
	return (c >= 48 && c <= 57);
}

bool isOperand(char c) {
	return isLetter(c) || isNumber(c);
}

bool isOperator(char c) {
	return (c >= 40 && c <= 43) || (c == 45) || (c == 47);
}

bool canEvaluate(string postfix) {
	for (char c: postfix) {
		if (!(isNumber(c) || isOperator(c))) return false;
	}
	return true;
}

string toPostfix(string infix) {
	string postfix = "";
	Stack<char> operatorStack;

	for (char c: infix) {
		if (!(isOperand(c) || isOperator(c))) return "Not a valid infix expression";
		if (isOperand(c)) {
			postfix += c;
		} else if (c == ')') {
			while (operatorStack.top() != '(') {
				postfix += operatorStack.pop();
			}
			operatorStack.pop();
		} else if (c == '(') {
			operatorStack.push(c);
		} else {
			// fix this
			if (c == '+' || c == '-') {
				while (operatorStack.top() == '*' || operatorStack.top() == '/') {
					postfix += operatorStack.pop();
				}
			}
			if (c == '-') {
				while (operatorStack.top() == '+') {
					postfix += operatorStack.pop();
				}
			}
			if (c == '*') {
				while (operatorStack.top() == '/') {
					postfix += operatorStack.pop();
				}
			}
			operatorStack.push(c);
		}
	}
	while (operatorStack.isNotEmpty()) postfix += operatorStack.pop();
	return postfix;
}

float evaluate(string postfix) {
	Stack<float> s;
	for (char c: postfix) {
		if (isOperand(c)) s.push(c - '0');
		if (isOperator(c)) {
			float a = s.pop();
			float b = s.pop();
			float r = 0.0;

			if (c == '+') {
				r = b + a;
			} else if (c == '*') {
				r = b * a;
			} else if (c == '-') {
				r = b - a;
			} else if (c == '/') {
				r = b / a;
			}

			s.push(r);
		}
	}
	return s.pop();
}

int main() {
	// assume that the parentheses in infix expression are always valid
	string infix, postfix;
	
	while (true) {
		clearScreen();
		cout << "Infix expression (q to quit): ";
		cin >> infix;

		if (infix == "q") break;

		postfix = toPostfix(infix);
		cout << endl;
		cout << "Postfix expression: " << postfix << endl;
		if (canEvaluate(postfix)) cout << "Evaluated: " << evaluate(postfix) << endl;
		wait();
	}
}