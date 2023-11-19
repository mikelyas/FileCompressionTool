#include "FIleManager.h"
#include "CompressionManager.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;


std::vector<uint8_t> FileManager::readFile(const std::string& file) {
    std::ifstream input(file, std::ios::binary);
    if (!input.is_open()) {
        // Handle file opening error
        return std::vector<uint8_t>();
    }

    input.seekg(0, std::ios::end);
    std::streampos fileSize = input.tellg();
    input.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    input.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    input.close();
    return buffer;
}

void FileManager::writeFile(const std::string& file, const std::vector<uint8_t>& data) {
    std::ofstream output(file, std::ios::binary);
    if (!output.is_open()) {
        // Handle file creation error
        return;
    }

    output.write(reinterpret_cast<const char*>(data.data()), data.size());
    output.close();
}

std::vector<std::string> FileManager::getFilesInFolder(const std::string& folder) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

void FileManager::compressFolder(const std::string& folder) {
    std::vector<std::string> filesToCompress = getFilesInFolder(folder);
    CompressionManager* compressionManager = new CompressionManager();

    nlohmann::json metadata; // JSON object to store metadata

    for (const std::string& file : filesToCompress) {
        std::vector<uint8_t> fileData = readFile(file);
        std::vector<uint8_t> compressedData = compressionManager->compress(fileData);
       
        // Write compressed data back to file
        std::string compressedFile = file + ".compressed"; // Change extension or use a different naming convention
        writeFile(compressedFile, compressedData);

        // Add file information to metadata
        metadata["compressed_files"].push_back({
            {"filename", file},
            {"compressed_size", compressedData.size()},
            {"original_size", fileData.size()}
        });
    }

    // Write metadata to a file
    std::string metadataFile = folder + "/metadata.json"; // Store metadata in the folder
    std::ofstream metadataOutput(metadataFile);
    metadataOutput << metadata.dump(4); // Indented JSON for readability
    metadataOutput.close();
}