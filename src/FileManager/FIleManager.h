

class FileManager {
public:
    std::vector<uint8_t> readFile(const std::string& file);

    void writeFile(const std::string& file, const std::vector<uint8_t>& data);

    std::vector<std::string> getFilesInFolder(const std::string& folder);

    void compressFolder(const std::string& folder);
};
