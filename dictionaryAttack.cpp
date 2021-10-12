/*
Requires the two inputs, also requires you to be in the directory of where rockyou.txt is.
*/
#include <iostream>
#include <fstream>
using namespace std;


int returnhash(string password){
    char nts1[password.length()];
    for (int i = 0; i < password.length(); i ++){
        nts1[i] = password[i];
    }
    
    std::string str1 (nts1);

    std::hash<std::string> str_hash;
    
    return str_hash(str1);
}

bool checkHash(int passwordHashed, string pass_a){
    int pass_hash = returnhash(pass_a);

    return (pass_hash==passwordHashed);
}


string getPass(int pass_a){
    int start = clock();
    string myText;

    // Read from the text file
    ifstream MyReadFile("rockyou.txt");
    
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        if (checkHash(pass_a, myText)){
            break;
        }
    }

    // Close the file
    MyReadFile.close();

    int end = clock();
    cout << end - start << "    " << ((float)end - start)/CLOCKS_PER_SEC << endl;
    return myText;
}




int main() {
    
    string password;
    cout << "Enter password: ";
    cin >> password;
    string password_a = "password";

    int passwordHashed = returnhash(password);
    
    //cout << getPass(password_a) << endl;
    
    string ans = getPass(passwordHashed);
    if (ans == password){
        cout << ans << " is in the database." << endl;
    } else{
        cout << password << " is not in the database." << endl;
    }
    
    
    return 0;
}
