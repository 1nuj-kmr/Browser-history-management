#include<bits/stdc++.h>
using namespace std;

struct Node {

    string url;
    Node* prev;
    Node* next;

    Node(string url) {
        this->url = url;
        prev = next = NULL;
    }
};

class BrowserHistory {
private:
    Node* current;

public:
    BrowserHistory(string homepage)
    {
        current = new Node(homepage);
    }

    void saveToFile( ){

        ofstream file ("History.txt");

        if( !file.is_open()) {
            cout <<"ERROR : Could not open file for saving\n";
            return;
        }

        if( !current){
            cout << "Nothing to save.\n";
            return;
        }
        
        Node* temp = current;
        while( temp -> prev){
            temp = temp ->prev ;
        }

        while( temp ){
            if ( temp == current){
                file << "CURRENT: "<< temp -> url << '\n';
            }
            else {
                file << temp -> url <<'\n';
            }

            temp = temp -> next;
        }

        file.close();
        cout << "History Saved to \"History.txt\" file\n";

    }

    void LoadFromFile() {

        ifstream file("History.txt");

        if (!file.is_open()) {
            cout << "No file found\n";
            return;
        }

        Node* temp = current;
        while( temp -> prev) temp = temp -> prev;

        while( temp) {
            Node* del = temp;
            temp = temp -> next;
            del->next = nullptr;
            del->prev = nullptr;
            delete del;
        }
        current = nullptr; 


        string line;
        Node* tail = NULL;
        Node* currPtr = NULL; 

        while ( getline(file, line)) {

            bool isCurrent = false;
            string url = line;

            if ( url.substr(0,9) == "CURRENT: ") {
                isCurrent = true;
                url = line.substr(9); 
            }

            Node* newNode = new Node(url);

            if (!tail ) {
                tail = newNode;
            } else {
                tail -> next = newNode;
                newNode -> prev = tail;
                tail = newNode;
            }

            if (isCurrent) {
                currPtr = newNode;
            }
        }

        // set current correctly
        current = ( currPtr!= nullptr ) ? currPtr : tail;

        file.close();
        cout << "History Loaded Successfully\n";

    }

    ~BrowserHistory(){

        if( !current) {
            return;
        }

        Node* temp = current;

        while( temp -> prev){
            temp = temp -> prev;
        }

        while( temp){
            Node* del = temp;
            temp = temp ->next;
            del->next = nullptr;
            del->prev = nullptr;
            delete del;
        }

    }

    void visit (string url){

        Node* newNode = new Node(url);

        Node* temp = current -> next;
        while( temp ){
            Node* del = temp;
            temp = temp -> next;
            del->prev = NULL;
            del->next = NULL;
            delete del; 
        }
        current -> next = NULL; 

        current -> next = newNode;
        newNode -> prev = current;
        current = newNode;

        cout << "Visited URL -> " << current -> url << '\n';

    }

    void showCurrent() {

        if( current == NULL ){
            cout << "No page visited yet.\n"; 
        }
        else{
            cout << "Current page: " << current -> url << endl;
        }

    }

    void goBack() {

        if(current -> prev == NULL) {
            cout << "Cannot go back. No history!" << endl;
            return;
        }

        current = current -> prev;

        cout << "Went Back to : " << current -> url << '\n'; 

    }

    void goForward() {


        if (current->next == NULL) {
            cout << "No forward history\n";
            return;
        }

        current = current->next;

        cout << "Went forward to: " << current->url << "\n";
    }
    
    void showFullHistory() {

        Node* temp = current;
        while( temp -> prev ){
            temp = temp -> prev;
        }

        cout << "\n--- Full History ---\n";

        while( temp ){

            if(temp == current)
                cout << "[" << temp->url << "] ";
            else
                cout << temp->url << " -> ";

            temp = temp->next;
        }

        cout << '\n';

    }
    
};


int main(){

    BrowserHistory browser("default.com");

    browser.LoadFromFile();

    int choice;
    string url;

    cout << "-- Browser History Simulator --" << endl;

    while (true) {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Visit a page" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Show Current Page" << endl;
        cout << "5. Show Full History" << endl;
        cout << "6. Save File and Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            cout << "Enter URL: ";
            cin >> url;
            browser.visit(url);
        }
        else if (choice == 2) browser.goBack();
        else if (choice == 3) browser.goForward();
        else if (choice == 4) browser.showCurrent();
        else if (choice == 5) browser.showFullHistory();
        else if (choice == 6) {
            browser.saveToFile();
            cout << "Bye!" << endl;
            break;
        }
        else cout << "Invalid choice." << endl;

    }

    return 0;
    
}