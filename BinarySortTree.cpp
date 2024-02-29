//=========================================================//
// SNHU CS300 Project 2			                   //
// Author: Melissa Cianfarano                              //
// Date: 02/18/2024                                        //
// Description:                                            //
//		Design code to read course data file.      //
//      Create a menu to prompt a user for menu options.   //
//      Load data stucture from file.                      //
//      Print list in alphanumeric order.                  //
//      Print course information.                          //
//=========================================================//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Define a structure to hold course information
struct Course {
	string courseNumber;
	string courseName;
	vector<string> prerequisite;
};

// Internal structure for tree node
struct Node{
	Course course;
	Node* left;
	Node* right;

	// Default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// Initialize with a course
	Node(Course aCourse) : Node() {
		this->course = aCourse;
	}
};

// Binary search tree class with methods
class BST {

private:
	void Destruct(Node* node);

public:
	Node* root;
	BST();
	virtual ~BST();
	void insertCourse(BST* tree, Node* node);
	void searchTree(string courseNumber);
	void printCourse(Node* node);

};

// Default constructor for binary search tree
BST::BST() {
	root = nullptr;
}

// Destructor
BST::~BST() {
	Destruct(root);
}

// Destruct and delete nodes
void BST::Destruct(Node* node) {
	if (node != nullptr) {
		Destruct(node->left);
		node->left = nullptr;
		Destruct(node->right);
		node->right = nullptr;
		delete node;
	}
};

// Search and print method
void BST::searchTree(string courseNumber) {
	// Set current node to root
	Node* currentNode = root;

	// While current node is not null
	while (currentNode != nullptr) {

		// Print course number and name
		if (currentNode->course.courseNumber == courseNumber) {
			cout << currentNode->course.courseNumber;
			cout << endl;
			cout << currentNode->course.courseName;
			cout << endl;
			cout << "Prerequisites: ";

			// Print prerequisites
			for (string prerequisite : currentNode->course.prerequisite) {
				if (prerequisite == currentNode->course.prerequisite.back()) {

					cout << prerequisite << endl;
				}
				else {
					cout << prerequisite << ", ";

				}
			}

			return;
		}

		// If left node is null
		else if (courseNumber < currentNode->course.courseNumber) {

			if (currentNode->left != nullptr) {
				currentNode = currentNode->left;
			}
		}
		// Point to right node
		else {

			currentNode = currentNode->right;
		}
	}
	// If invalid course number
	cout << "Course " << courseNumber << " is not a valid course number. " << endl;
	return;
}

// Insert course into catalog
void BST::insertCourse(BST* tree, Node* node) {
	
	if (tree->root == nullptr) {
		tree->root = node;
	}
	else {
		Node* curr = tree->root;
		while (curr != nullptr) {

			if (node->course.courseNumber < curr->course.courseNumber) {
				if (curr->left == nullptr) {
					curr->left = node;
					curr = nullptr;
				}
				else {
					curr = curr->left;
				}
			}
			else {
				if (curr->right == nullptr) {
					curr->right = node;
					curr = nullptr;
				}
				else {
					curr = curr->right;
				}
			}
		}
	}

}



// Print course list in order
void BST::printCourse(Node* node) {
	if (node == nullptr) {
		return;
	}

	printCourse(node->left);
	cout << node->course.courseNumber << ", " << node->course.courseName << endl;
	printCourse(node->right);
};


// Load files
void loadFile(string filename, BST* bst) {
	ifstream file("ABCUCourses.txt");

	// If file is loaded
	if (file.is_open()) {
		cout << "File loaded properly. \n";

		// Create placeholders
		int num;
		string line;
		string word;

		while (getline(file, line)) {

			num = 0;
			Node* node = new Node();
			stringstream str(line);

			while (num < 2) {
				getline(str, word, ',');
				if (num == 0) {
					node->course.courseNumber = word;
				}
				else {
					node->course.courseName = word;
				}
				num++;
			}
			while (getline(str, word, ',')) {
				node->course.prerequisite.push_back(word);
			}

			bst->insertCourse(bst, node);
		}
	}
	// If file not loaded
	else {
		cout << "File not loaded properly. Try again. \n";
	}
}


// Main method
void main() {
	BST* bst = new BST();

	string loadData;
	string courseNumber;


	// Display menu to prompt user for menu options
	cout << "   Welcome to ABCU's course planner. \n";
	int userInput = 0;
	while(userInput != 4) {
		cout << "*------------------------------------* \n";
		cout << "|      1. Load Data Structure.       | \n";
		cout << "|      2. Print Course List.         | \n";
		cout << "|      3. Print Course.              | \n";
		cout << "|      4. Exit Course Planner.       | \n";
		cout << "|      Please enter a choice.        | \n";
		cout << "*------------------------------------* \n";
		cin >> userInput;

		// Switch menu for choices
		switch (userInput) {

		// Load data structure
		case 1:
			loadFile("ABCUCourses.txt", bst);
			break;
		
		// Print course List
		case 2:
			cout << "Here is a sample schedule: \n\n";
			cout << "*-------------------------------------*\n";
			bst->printCourse(bst->root);
			cout << "*-------------------------------------*\n";
			break;
		
		// Print specific course
		case 3:
			cout << "Which course are you interested in? \n\n";
			cin >> courseNumber;

			cout << "*-------------------------------------*\n";
			std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
			bst->searchTree(courseNumber);
			cout << "*-------------------------------------*\n";
			break;

		// Exit course planner
		case 4:
			cout << "Thank you for using ABCU's course planner.\n";
			break;

		// Invalid choice
		default:
			cout << userInput << " is not a valid option.\n";
			break;

		}
	}

}
