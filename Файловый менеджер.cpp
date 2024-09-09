#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

void clear_field() {
	system("cls");
	cout << endl;
}

bool file_open(const string& file_name) {
	ifstream file(file_name);
	return file.good();
}

int main()
{
	string command;
	string file_name;

	while (true) {
		cout << "List of all commands:" << endl << "1-remove file" << endl << "2-create file" << endl << "3-exists file" << endl
			<< "4-info file" << endl << "5-copy file1 file2" << endl << "6-move file1 file2" << endl << "7-rename file new_file" << endl << "8-exit" << endl;
		cout << endl << "Enter command:\n";
		cin >> command;

		if (command == "1") {
			cout << "Enter name remove file:\n";
			cin >> (file_name);
			if (remove(file_name.c_str()) != 0) {
				clear_field();
				cerr << "Error deleting file " << file_name << endl << endl;
			}
			else {
				clear_field();
				cout << "File " << file_name << " successfully deleted" << endl << endl;
			}
		}

		else if (command == "2") {
			cout << "Enter name new file:\n";
			cin >> file_name;
			if (file_open(file_name)) {
				clear_field();
				cerr << "Error: File " << file_name << " already exists" << endl << endl;
			}
			else {
				ofstream fout(file_name);
				clear_field();
				cout << "File " << file_name << " successfully created" << endl << endl;
			}
		}

		else if (command == "3") {
			cout << "Enter name file being checked:\n";
			cin >> file_name;
			if (file_open(file_name)) {
				clear_field();
				cout << "File " << file_name << " exists" << endl << endl;
			}
			else {
				clear_field();
				cout << "File " << file_name << " does not exists" << endl << endl;
			}
		}

		else if (command == "4") {
			string str;

			cout << "Enter name getting information file:\n";
			cin >> file_name;
			if (!file_open(file_name)) {
				clear_field();
				cerr << "Error: File " << file_name << " does not exists" << endl << endl;
			}
			else {
				ifstream file(file_name);
				file.seekg(0, ios::end);
				if (file.tellg() == 0) {   //tellg() возвращает текущую позицию указателя чтения файла
					clear_field();
					cout << "File " << file_name << " is empty" << endl << endl;
				}
				else {
					clear_field();
					file.seekg(0, ios::beg);
					getline(file, str);
					cout << str << endl << endl;
				}
				file.close();
			}
		}

		else if (command == "5") {
			string file_name_copy;
			string str;

			cout << "Enter name file you want to copy\n";
	        cin >> file_name;
			if (file_open(file_name)) {
				cout << "Enter name of the file where you want to copy\n";
				cin >> file_name_copy;
                    if (file_open(file_name_copy)) {
					clear_field();
					cerr << "Error: File " << file_name_copy << " is empty" << endl << endl;
				}
				else {
					ifstream copy_file(file_name);
					getline(copy_file, str);
					ofstream file(file_name_copy);
					file << str;
					clear_field();
					cout << "File " << file_name << " successfully copied to file " << file_name_copy << endl << endl;
					file.close();
				}
			}
			else {
				clear_field();
			    cerr << "Error: File " << file_name << " does not exist" << endl << endl;
			}
		}

		else if (command == "6") {
			string file_name_move;
			string str;

			cout << "Enter name file you want to move\n";
			cin >> file_name;
			if (file_open(file_name)) {
				cout << "Enter the name of the file where you want to move it\n";
				cin >> file_name_move;
				if (file_name == file_name_move) {
					clear_field();
					cerr << "Error: File " << file_name << " cannot be move to the same file" << endl << endl;
				}
				else if (!file_open(file_name_move)){
					clear_field();
					cerr << "Error: File " << file_name_move << " does not exists" << endl << endl;
				}
				else {
					ifstream move_file(file_name, ios_base::in);
					getline(move_file, str);
					ofstream file(file_name_move, ios_base::app);
					file << ' ' << str;
					clear_field();
					cout << "File " << file_name << " successfully move to file " << file_name_move << endl << endl;
					file.close();
				}

			}
			else {
				clear_field();
				cerr << "Error: File " << file_name << " does not exist" << endl << endl;
			}

		}

		else if (command == "7") {
			string file_name_change;

			cout << "Enter name file you want rename\n";
			cin >> file_name;
			if (file_open(file_name)) {
				cout << "Enter new name file you want change\n";
				cin >> file_name_change;
				if (!file_open(file_name_change)) {
					rename(file_name.c_str(), file_name_change.c_str());
					clear_field();
					cout << "File " << file_name << " successfully renamed to " << file_name_change << endl << endl;
				}
				else {
					clear_field();
					cerr << "Error: file " << file_name_change << " is empty" << endl << endl;
				}
			}
			else {
				clear_field();
				cerr << "Error: File " << file_name << " does not exist" << endl << endl;
			}
		}

		else if (command == "8") {
			break;
		}

		else {
			clear_field();
			cerr << "Error: Invalid command" << endl << endl;
		}
	}
}
