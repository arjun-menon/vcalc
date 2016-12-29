#include "common.hpp"

void repl() {
    Env env;
    define_builtin_functions(env);

    for (string input; true; cout << endl) {
        cout << "> ";

        if (!getline(std::cin, input))
            break;

        if (input == "exit" || input == "quit") {
            break;
        } else {
            try {
                cout << *eval(Parser::parse(input), env) << endl;
            }
            catch(exception &e) {
                cout << e.what() << endl;
            }
            catch(...) {
                cout << "Error: Unhandled Exception" << endl;
            }
        }
    }
}

void stuff() {
    cout<<"x = "<< sizeof(Real) <<endl;
    Table table;
    DataReader::read_file("test_data/t1.txt", table);
    cout << "table" << endl << table << endl;
    cout << table[3].getMin() << endl;
    table.display(cout, {1, 3});
    cout << endl << *(table[1] + table[3]) << endl;
}

int main() {
    repl();
    // stuff();
    return 0;
}
