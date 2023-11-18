#include <vector>
#include <unordered_map>
#include <string>


struct Node {
    uint8_t data;
    int freq;
    Node* left;
    Node* right;

    Node(uint8_t data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};


class CompressionManager {
public:
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data);
private:
    void generateCodes(Node* root, std::string code);
    std::unordered_map<uint8_t, std::string> codes;
};