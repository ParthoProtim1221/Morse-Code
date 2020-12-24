#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
    char data = '&';
    Node* left = NULL;
    Node* right = NULL;
    string value = "";
    char small = '&';
};

void printInorder(Node* head)
{
    if (head == NULL)
        return;
    printInorder(head->left);
    cout << head->data << " ";
    printInorder(head->right);
}

void insertNode(string a,Node* head,char c,char c1)
{
    string s = a;
    Node* temp = head;
    int b = a.length();
    for(int i=0; i<b; i++)
    {
        if(a[i] == '.')
        {
            if(temp->left != NULL )
                temp = temp->left;
            else
            {
                Node* temp1 = new Node();
                temp->left = temp1;
                temp = temp->left;
            }
        }
        else if(a[i] == '-')
        {
            if(temp->right != NULL)
                temp = temp->right;
            else
            {
                Node* temp1 = new Node();
                temp->right = temp1;
                temp = temp->right;
            }
        }
    }
    temp->data = c;
    temp->value = s;
    temp->small = c1;
}
string result ="";
void searching(Node* head, char n)
{
    if (head == NULL)
        return ;

    searching(head->left,n);
    if(head->data == n  || head->small == n)
    {
        string a= head->value;
        result += a;
        result += " ";
    }
    searching(head->right,n);
}

void anothersearching(Node* head, string a)
{
    Node* temp = head;
    for(int i=0; i<a.length(); i++)
    {
        if(a[i] == '.')
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    result += temp->data;
}
void encode(Node* head,string input)
{
    Node* temp = head;
    for(int i=0; i<input.length(); i++)
    {
        if(input[i] == ' ')
            result += "  ";
        else
        {
            searching(head,input[i]);
        }
    }
    cout << result << endl ;
}
int doubleSpaceChecker(string input)
{
    int a =0;
    a = input.find("  ");
    return a;
}
int singleSpaceChecker(string input)
{
    int a =0;
    a = input.find(" ");
    return a;
}
void decode(Node* head,string input)
{
    string s1 = input;
    Node* temp = head;

    if(singleSpaceChecker(input)>0)
    {

        while(doubleSpaceChecker(input)>0)
        {

            int pos = doubleSpaceChecker(input);
            string s = input.substr(0, pos);
            while(singleSpaceChecker(s)>0)
            {
                int pos1 = singleSpaceChecker(s);
                s1 = s.substr(0,pos1);
                anothersearching(head,s1);
                s = s.substr(pos1+1);
            }
            anothersearching(head,s);
            result += " ";
            input = input.substr(pos+2);
        }
        int pos = doubleSpaceChecker(input);
        string s = input.substr(0, pos);
        while(singleSpaceChecker(s)>0)
        {
            int pos1 = singleSpaceChecker(s);
            s1 = s.substr(0,pos1);
            anothersearching(head,s1);
            s = s.substr(pos1+1);
        }
        anothersearching(head,s);
    }
    else
        anothersearching(head,s1);

    return;
}



int main()
{
    string ter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string characterS = "abcdefghijklmnopqrstuvwxyz";
    string symbol[36] = {".-", "-...", "-.-.", "-..",
                         ".", "..-.", "--.", "....", "..", ".---", "-.-",
                         ".-..", "--", "-.", "---", ".--.", "--.-",
                         ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                         "-.--", "--..", ".----", "..---", "...--", "....-",
                         ".....", "-....", "--...", "---..", "----.", "-----"
                        };

    Node* root = new Node();

    for(int i=0; i<36; i++)
    {
        insertNode(symbol[i],root,character[i],characterS[i]);
    }

    //printInorder(root);
    cout << endl << endl;
    int option = 0;
    while(option<3)
    {
        cout << "Choose Your Option: " << endl;
        cout << "1. Encode my language(input your string ... this code will change your string)" << endl;
        cout << "2.. Decode my language(input your Code ... this code will change that to English Language)" << endl;
        cout << "3. Exit ." <<endl;
        cin >> option;
        switch(option)
        {
        case 1:
        {
            string input;
            string result1;
            ifstream myfile ("morse_code.txt");
            if (myfile.is_open())
            {
                while ( getline (myfile,input) )
                {
                    result = "";
                    encode(root,input);
                    result1 += result;
                    result1 += "\n";
                }
                myfile.close();
            }

            else
                cout << "Unable to open file";

            ofstream newfile ("answer1.txt");
            if (newfile.is_open())
            {
                newfile << result1;
                newfile.close();
            }
            else
                cout << "Unable to open file";
            break;
        }
        case 2:
        {

            string input;

            string result1;
            ifstream myfile ("another_Morse_code.txt");
            if (myfile.is_open())
            {
                while ( getline (myfile,input) )
                {

                    result ="";

                    decode(root,input);

                    result1 += result;
                    result1 += "\n";
                }

                myfile.close();
            }

            else
                cout << "Unable to open file";
            cout << result1;
            ofstream newfile ("answer2.txt");
            if (newfile.is_open())
            {
                newfile << result1;
                newfile.close();
            }
            else
                cout << "Unable to open file";
            break;
        }
        }
    }
    return 0;
}
