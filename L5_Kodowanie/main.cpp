#include <iostream>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

/// ENCODING ///
struct NodeEn {
    char ch;
    int number;
    NodeEn *left, *right;
};

struct comparator {
    bool operator()(NodeEn *l, NodeEn *r) {
        return l->number > r->number;
    }
};

void saveTable(unordered_map<char, string> table, string codeTableFilePath) {
    ofstream tableFile;
    tableFile.open(codeTableFilePath);
    for (auto element: table) {
        if (element.first == '\n') {
            tableFile << "\\n " << element.second << '\n';
        } else {
            tableFile << element.first << " " << element.second << '\n';
        }
    }
    tableFile.close();
}

void saveCode(string fileFileToEncodePath, string fileEncodedPath, unordered_map<char, string> code) {
    string line;
    ifstream fileToRead(fileFileToEncodePath);

    ofstream codeFile;
    codeFile.open(fileEncodedPath);

    if (fileToRead.is_open() && codeFile.is_open()) {
        while (getline(fileToRead, line)) {
            for (char ch: line) {
                codeFile << code[ch];
            }
            codeFile << code['\n']; //new line char
            codeFile << '\n';
        }
        codeFile.close();
        fileToRead.close();
    } else {
        cout << "Error!" << endl;
    }
}

NodeEn *getNodeEn(char ch, int number, NodeEn *left, NodeEn *right) {
    NodeEn *node = new NodeEn();

    node->ch = ch;
    node->number = number;
    node->left = left;
    node->right = right;

    return node;
}

void encode(NodeEn *root, string code, unordered_map<char, string> &huffmanTable) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanTable[root->ch] = code;
    }

    encode(root->left, code + "0", huffmanTable);
    encode(root->right, code + "1", huffmanTable);
}

unordered_map<char, int> setNumber(string fileName) {
    unordered_map<char, int> freq;
    string line;
    ifstream fileToRead(fileName);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            for (char ch : line) {
                freq[ch]++;
            }
            freq['\n']++;
        }
        fileToRead.close();
        freq['\n']--;
    } else {
        cout << "Error!";
    }

    return freq;
}

void encodeHuffman(string filePath, string tablePath, string encodedFilePath) {
    unordered_map<char, int> freq = setNumber(filePath);

    priority_queue<NodeEn *, vector<NodeEn *>, comparator> pq;

    for (auto element : freq) {
        pq.push(getNodeEn(element.first, element.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        char empty = '\0';
        // two nodes with lowest number into one
        NodeEn *left = pq.top(); pq.pop();
        NodeEn *right = pq.top(); pq.pop();

        int sum = left->number + right->number;

        pq.push(getNodeEn(empty, sum, left, right));
    }

    NodeEn *root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    saveTable(huffmanCode, tablePath);

    saveCode(filePath, encodedFilePath, huffmanCode);
}

/// DECODING ///
struct NodeDe {
    char ch;
    NodeDe *left, *right;
};

NodeDe *getNodeDe(char ch, NodeDe *left, NodeDe *right) {
    NodeDe *node = new NodeDe();

    node->ch = ch;
    node->left = left;
    node->right = right;

    return node;
}

unordered_map<char, string> readTable(string fileNamePath) {
    unordered_map<char, string> tableCode;
    string line;
    char sign;
    string codeString;
    int lineLength;
    int index;
    ifstream fileToRead(fileNamePath);

    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            lineLength = line.size();
            if (lineLength > 0) {
                index = line.find(' ');
                switch(index){
                    case 1:
                        // char + space + code
                        sign = line.at(0);
                        break;
                    case 2:
                        // line with endline
                        sign = '\n';
                        break;
                    case 0:
                        sign = ' ';
                        index++;
                        break;
                    default:
                        sign = line.at(0);
                        break;
                }
                codeString = line.substr(index + 1);
                tableCode[sign] = codeString;
            }
        }
        fileToRead.close();
    } else {
        cout << "Something wrong with files";
    }
    return tableCode;
}

void addChar(string fileName, char decodedChar) {
    fstream decodeFile;
    decodeFile.open(fileName, ios::out | ios::app);

    if (decodeFile.is_open()) {
        decodeFile << decodedChar;
        decodeFile.close();
    } else {
        cout << "Error!";
    }
}

void clearFile(string filePath) {
    ofstream clearFile(filePath);
    clearFile.close();
}

void decodeOneLine(NodeDe *root, int &index, string str, string filePath) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        // dopisywanie odszyfrowanego znaku
        addChar(filePath, root->ch);
        return;
    }

    index++;

    if (str[index] == '0')
        decodeOneLine(root->left, index, str, filePath);
    else
        decodeOneLine(root->right, index, str, filePath);
}

string decodeFile(string fileNamePath, NodeDe *root, string decodedFilePath) {
    string line;
    ifstream fileToRead(fileNamePath);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            int index = -1;
            while (index < (int) line.size() - 2) {
                decodeOneLine(root, index, line, decodedFilePath);
            }
        }
    } else {
        cout << "Error!";
    }
    return line;
}

void decodeHuffman(string codeFilePath, string tableFilePath, string decodedFilePath) {
    unordered_map<char, string> huffmanCode = readTable(tableFilePath);

    priority_queue<NodeDe *, vector<NodeDe *>> pq;

    pq.push(getNodeDe('\0', nullptr, nullptr));

    NodeDe *root;

    for (auto element: huffmanCode) {
        root = pq.top();
        for (char c : element.second) {
            if (c == '1') {
                if (root->right == nullptr) {
                    root->right = getNodeDe('\0', nullptr, nullptr);
                }
                root = root->right;
            } else {
                if (root->left == nullptr) {
                    root->left = getNodeDe('\0', nullptr, nullptr);
                }
                root = root->left;
            }
        }
        root->ch = element.first;
    }
    root = pq.top();

    clearFile(decodedFilePath);

    decodeFile(codeFilePath, root, decodedFilePath);
}

/// MAIN ///

int main() {
    string toEncodeFilePath = "/home/dominik/STUDIA/ALGO/L5_Kodowanie/L5_Kodowanie/panTadeusz.txt";
    string tableFilePath = "/home/dominik/STUDIA/ALGO/L5_Kodowanie/L5_Kodowanie/table.txt";
    string encodedFilePath = "/home/dominik/STUDIA/ALGO/L5_Kodowanie/L5_Kodowanie/encodedFile.txt";
    string decodedFilePath = "/home/dominik/STUDIA/ALGO/L5_Kodowanie/L5_Kodowanie/decoded.txt";

    cout << "Encoding and decoding... ";
    cout.flush();

    encodeHuffman(toEncodeFilePath, tableFilePath, encodedFilePath);

    decodeHuffman(encodedFilePath, tableFilePath, decodedFilePath);

    cout << "Done.";

    return 0;
}
