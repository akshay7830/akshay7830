#include <iostream>
#include <map>
#include <string>
#include<stack>

using namespace std;

class Calculations {
public:
    // Method for addition
    double addition(double a, double b) {
        return a + b;
    }

    // Method for subtraction
    double subtraction(double a, double b) {
        return a - b;
    }

    // Method for multiplication
    double multiplication(double a, double b) {
        return a * b;
    }

    // Method for division
    double division(double a, double b) {
        if (b == 0) {
            throw runtime_error("Division by zero error"); 
        }
        return a / b;
    }
};

class Calculator : public Calculations {
private:
    map<int, string> calculationMap;
    int index; 

public:
    Calculator() : index(0) {} 

   
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

   
    double applyOperation(double a, double b, char op) {
        switch (op) {
            case '+': return addition(a, b);
            case '-': return subtraction(a, b);
            case '*': return multiplication(a, b);
            case '/': return division(a, b);
            default: throw runtime_error("Invalid operator");
        }
    }

  
    double evaluateExpression(const string& expression) {
        stack<double> values;
        stack<char> ops;     

        for (size_t i = 0; i < expression.length(); i++) {
             if(isspace(expression[i])) continue;

            if (isdigit(expression[i])) {
                double value = 0;
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        i++;
                        double decimalPlace = 0.1;
                        while (i < expression.length() && isdigit(expression[i])) {
                            value += (expression[i] - '0') * decimalPlace;
                            decimalPlace *= 0.1;
                            i++;
                        }
                        break;
                    }
                    value = (value * 10) + (expression[i] - '0');
                    i++;
                }
                values.push(value);
                i--; 
            }
            
            else if (expression[i] == '(') {
                ops.push(expression[i]);
            }
           
            else if (expression[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOperation(val1, val2, op));
                }
                ops.pop(); 
            }
            
            else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOperation(val1, val2, op));
                }
                ops.push(expression[i]);
            }
        }

        
        while (!ops.empty()) {
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOperation(val1, val2, op));
        }

        return values.top(); 
    }

    void clearCalculations() {
        if(calculationMap.empty()) {
           cout<<"\nCalculations are already empty.\n";
           return;
        }
        calculationMap.clear(); 
        cout << "All calculations have been cleared." << endl;
    }

    void pushCalculation(const string& calculation) {
        calculationMap[index++] = calculation; 
    }
    void displayCalculations() {
        if (calculationMap.empty()) {
            cout << "No calculations to display." << endl;
            return;
        }

        cout << "Calculations:" << endl;
        for (const auto& entry : calculationMap) {
            cout << entry.first+1 << ": " << entry.second << endl;
        }
    }

    void help() {
        cout << "\nWelcome to the help section of Advanced Calculator.\n";
        cout << "\nX - Cut.  H-History. C-Clear. (.) - Dot\n";
        cout << "\nThe below information is the usage of the buttons.\n";
        cout << "\nX - Backspace.-(Shift + 9), )-(Shift + 0),/(Divide), x(Shift+8), -(Click -) ,\n +(Shift + '+'), %-:(Shift + 5) , =(Click Enter)\n ";
        cout << "\nYou can enter complex mathematical expressions like ((2+3)*5)/5.\n";
        cout << "Available operations: +, -, *, /\n";
        cout << "Use parentheses to group operations.\n";
    }

    void performCalculation(const string& calculation) {
        try {
            double result = evaluateExpression(calculation);
            cout << "Result: " << result << endl;
            pushCalculation(calculation + " = " + to_string(result));
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
};

void display() {
    cout<<"Welcome to Advanced Calculator Application\n\n";
    printf("\n%2s %20s\n", "H", " X ");
    printf("  %20s  \n\n", "____________________");
    printf("(%1s) (%1s) (%1s) (%1s)\n", " C ", " () ", " % ", " / ");
    printf("(%1s) (%1s) (%1s) (%1s)\n", " 9 ", " 8 ", " 7 ", " x ");
    printf("(%1s) (%1s) (%1s) (%1s)\n", " 6 ", " 5 ", " 4 ", " - ");
    printf("(%1s) (%1s) (%1s) (%1s)\n", " 3 ", " 2 ", " 1 ", " + ");
    printf("(%1s) (%1s) (%1s) (%1s)\n", "+/-", " 0 ", " . ", " = ");
}

int main() {
    Calculator calculator;
    int choice;
    display();
        
        cout << "\n1. Perform a calculation." << endl;
        cout << "2. Show History." << endl;
        cout << "3. Remove The History." << endl;
        cout << "4. Help." << endl;
        cout << "5. Exit.\n" << endl;
    while (true) {
        cout << "\nEnter your choice:" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                string calculation;
                cout << "\nEnter your calculation (e.g. ((2+3)*5)/5): ";
                cin.ignore();
                getline(cin, calculation);
                calculator.performCalculation(calculation);
                break;
            }
            case 2: {
                calculator.displayCalculations();
                break;
            }
            case 3:
                calculator.clearCalculations();
                break;
            case 4: {
                calculator.help();
                break;
            }
            case 5: {
                return 0;
            }
            default: {
                cout << "\nInvalid choice. Please choose a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}