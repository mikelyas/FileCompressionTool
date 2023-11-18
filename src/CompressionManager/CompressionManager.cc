#include "CompressionManager.h"
#include <queue>


struct Compare {
    bool operator()(Node* left, Node* right) { return left->freq > right->freq; }
};

void CompressionManager::generateCodes(Node* root, std::string code) {
    if (!root) return;

    if (root->data != '\0') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

std::vector<uint8_t> CompressionManager::compress(const std::vector<uint8_t>& data) {
    std::unordered_map<uint8_t, int> freq;
    for (uint8_t byte : data) {
        freq[byte]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    Node* root = pq.top();
    pq.pop();

    generateCodes(root, "");

    std::vector<uint8_t> compressedData;
    std::string buffer;
    for (uint8_t byte : data) {
        std::string code = codes[byte];
        buffer += code;
        while (buffer.length() >= 8) {
            uint8_t byteValue = 0;
            for (int i = 0; i < 8; ++i) {
                byteValue <<= 1;
                byteValue |= (buffer[i] - '0');
            }
            compressedData.push_back(byteValue);
            buffer = buffer.substr(8);
        }
    }

    // Handling remaining bits (if any)
    if (!buffer.empty()) {
        while (buffer.length() < 8) {
            buffer += '0'; // Padding with zeros to complete the byte
        }
        uint8_t byteValue = 0;
        for (int i = 0; i < 8; ++i) {
            byteValue <<= 1;
            byteValue |= (buffer[i] - '0');
        }
        compressedData.push_back(byteValue);
    }

    return compressedData;
}

std::vector<uint8_t> CompressionManager::decompress(const std::vector<uint8_t>& data) {
    Node* root = new Node('\0', 0);
    Node* current = root;

    std::vector<uint8_t> decompressedData;
    for (uint8_t byte : data) {
        for (int i = 7; i >= 0; --i) {
            if ((byte >> i) & 1) {
                current = current->right;
            } else {
                current = current->left;
            }
            if (current->left == nullptr && current->right == nullptr) {
                decompressedData.push_back(current->data);
                current = root;
            }
        }
    }

    return decompressedData;
}