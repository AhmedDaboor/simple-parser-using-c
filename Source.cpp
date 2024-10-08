#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum TokenType { Identifier, KeyWord, Integer, Float, Operator, String, Punctuator };

struct Token {
    TokenType type;
    string value;
};

const string FileName = "SourceCode.txt";

const string Keywords[]{ "cin",   "cout",   "string", "if",    "else", "int",
                         "float", "double", "do",     "while", "for" };

bool isIdentifierStart(char c) {
    // Is c an alphabetic character or _ ??
    return isupper(c) || islower(c) || c == '_';
}

bool isIdentifierChar(char c) {
    // Is c number, alphabetic, or _ ??
    return isdigit(c) || isIdentifierStart(c);
}

bool isKeyword(string& word) {
    for (auto& kw :
        Keywords)  // Constant Array (KeyWords) transfers values to ky ..
        if (word ==
            kw)  // Check whether the string sent to the funcation is keyword ..
            return true;

    return false;
}

bool isFloat(char c) {

    return isdigit(c) || c == '.';
}

bool isOperator(char c) {

    return c == '&' || c == '|' || c == '!';
}

vector<Token> FillingInTokenInfoWithinTheVector(const string& code) {
    vector<Token> Texts;
    short start = 0;
    Token T;

    short i = 0;
    while (i < code.length()) {
        if (code[i] == ' ') {  // if the first char of the string is a blank,
            // the loops start over ..
            i++;
            continue;
        }

        if (isIdentifierStart(code[i])) {
            start = i;

            // A loop that assembles the word ..
            while (i < code.length() && isIdentifierChar(code[i])) {
                i++;
            }

            T.value = code.substr(start, i - start);
            T.type = isKeyword(T.value) ? KeyWord : Identifier;
            Texts.push_back(T);
            start = 0;

        }

        else if (isdigit(code[i])) {

            string str = "";

            start = i;
            while (i < code.length() && isFloat(code[i])) {
                str += code[i];
                i++;
            }
            if (str.find('.') != string::npos) {
                T.value = code.substr(start, i - start);
                T.type = Float;
                Texts.push_back(T);

            }
            else {
                T.value = code.substr(start, i - start);
                T.type = Integer;
                Texts.push_back(T);

            }
            start = 0;
        }

        else if (isOperator(code[i])) {

            start = i;

            while (i < code.length() && isOperator(code[i])) {
                i++;
            }

            T.value = code.substr(start, i - start);
            T.type = Operator;
            Texts.push_back(T);
            start = 0;
        }

        else if (code[i] == '"') {
            i++;

            start = i;

            // Count from after the first quotation mark to the last quotation
            // mark ..
            while (i < code.length() && code[i] != '"') {
                i++;
            }

            T.value = code.substr(start, i - start);
            T.type = String;
            Texts.push_back(T);
            start = 0;
            i++;
        }

        else if (ispunct(code[i])) {
            T.value = code[i];
            T.type = Punctuator;
            Texts.push_back(T);

            i++;
        }
    }

    return Texts;
}

void PrintTokens(vector<Token>& Tokens) {

    for (auto& token : Tokens) {

        switch (token.type) {
        case Identifier:cout << "Identifier :" << token.value << endl; break;
        case KeyWord:   cout << "Keyword    :" << token.value << endl; break;
        case Integer:   cout << "Integer    :" << token.value << endl; break;
        case Float:     cout << "Float      :" << token.value << endl; break;
        case String:    cout << "String     :" << token.value << endl; break;
        case Punctuator:cout << "Punctuator :" << token.value << endl; break;
        case Operator:  cout << "Operator   :" << token.value << endl; break;
        default:        cout << "Unknown    :" << token.value << endl; break;
        }
    }
}

string ReadTheCodeFromFile() {
    fstream MyFile;
    string Text = "";
    string Code = "";

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        while (getline(MyFile, Text)) {
            Code += Text;
        }

        MyFile.close();
    }
    return Code;
}

int main() {
    string Code = ReadTheCodeFromFile();
    vector<Token> Texts = FillingInTokenInfoWithinTheVector(Code);
    PrintTokens(Texts);

    return 0;
}