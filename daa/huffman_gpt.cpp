#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq, Node *left = nullptr, Node *right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}

    ~Node()
    {
        delete left;
        delete right;
    }
};

struct comp
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node *root, int &index, string str)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{

    if (text.empty())
    {
        cout << "Empty string provided. Nothing to encode or decode.\n";
        return;
    }

    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, comp> pq;

    for (auto pair : freq)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    if (pq.size() == 1)
    {
        cout << "Only one unique character. Encoding is trivial.\n";
        Node *root = pq.top();
        unordered_map<char, string> huffmanCode;
        huffmanCode[root->ch] = "0";

        cout << "Huffman Codes are :\n";
        cout << root->ch << " " << huffmanCode[root->ch] << '\n';

        string encodedStr;
        for (char ch : text)
        {
            encodedStr += huffmanCode[ch];
        }

        cout << "\nEncoded string is :\n"
             << encodedStr << '\n';
        cout << "\nDecoded string is: \n"
             << text << '\n';

        delete root;
        return;
    }

    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node *root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n";
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << '\n';
    }

    string encodedStr;
    for (char ch : text)
    {
        encodedStr += huffmanCode[ch];
    }

    cout << "\nOriginal string was :\n"
         << text << '\n';
    cout << "\nEncoded string is :\n"
         << encodedStr << '\n';

    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)encodedStr.size() - 2)
    {
        decode(root, index, encodedStr);
    }
    cout << '\n';

    delete root;
}

int main()
{
    string text = "Huffman coding is a data compression algorithm.";
    buildHuffmanTree(text);

    return 0;
}
