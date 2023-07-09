#include <iostream>
#include <fstream>
///////////// RAII Example for File Handling


class FileHandler {
public:
    explicit FileHandler(const std::string& filename)
            : fileStream(filename) // Acquire the file resource by opening the file in the constructor
    {
        if (!fileStream) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    ~FileHandler() {
        if (fileStream.is_open()) {

            fileStream.close(); // Close the file in the destructor
        }
    }

    void writeData(const std::string& data) {
        if (fileStream.is_open()) {
            fileStream << data << "\n"; // Write data to the file
        }
    }

    std::string readData() {
        std::string content;
        fileStream.seekg(0); // Reset the file position to the beginning
        std::string line;
        while (std::getline(fileStream, line)) {
            content += line + '\n'; // Read data from the file
        }
        return content;
    }

private:
    std::fstream fileStream; // Resource (file) managed by the FileHandler object
};
int main() {
    try {
        FileHandler file("example.txt");
        file.writeData("Hello, RAII!");
        file.writeData("Hello, Friend");

        std::string fileContent = file.readData();
        std::cout << "File content:\n" << fileContent;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
