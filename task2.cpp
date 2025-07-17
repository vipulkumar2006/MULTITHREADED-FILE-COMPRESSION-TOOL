

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;

// Simple run-length encoding
string compressChunk(const string& data) {
    string result = "";
    int count = 1;
    for (size_t i = 1; i <= data.length(); ++i) {
        if (i < data.length() && data[i] == data[i - 1]) {
            ++count;
        } else {
            result += to_string(count) + data[i - 1];
            count = 1;
        }
    }
    return result;
}

// Reverse of run-length encoding
string decompressChunk(const string& data) {
    string result = "";
    string count = "";
    for (char c : data) {
        if (isdigit(c)) {
            count += c;
        } else {
            result += string(stoi(count), c);
            count = "";
        }
    }
    return result;
}

// Worker thread for compression
void compressWorker(vector<string>& inputChunks, vector<string>& compressedChunks, int index) {
    string compressed = compressChunk(inputChunks[index]);
    lock_guard<mutex> lock(mtx);
    compressedChunks[index] = compressed;
}

// Worker thread for decompression
void decompressWorker(vector<string>& inputChunks, vector<string>& decompressedChunks, int index) {
    string decompressed = decompressChunk(inputChunks[index]);
    lock_guard<mutex> lock(mtx);
    decompressedChunks[index] = decompressed;
}

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("compressed.txt");
    ofstream deFile("decompressed.txt");

    string data((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    int chunkSize = 1000;
    int numChunks = (data.size() + chunkSize - 1) / chunkSize;

    vector<string> inputChunks(numChunks), compressedChunks(numChunks), decompressedChunks(numChunks);

    for (int i = 0; i < numChunks; ++i) {
        inputChunks[i] = data.substr(i * chunkSize, chunkSize);
    }

    // Compression timing
    auto start = chrono::high_resolution_clock::now();
    vector<thread> threads;
    for (int i = 0; i < numChunks; ++i) {
        threads.emplace_back(compressWorker, ref(inputChunks), ref(compressedChunks), i);
    }
    for (auto& th : threads) th.join();
    auto end = chrono::high_resolution_clock::now();
    cout << "Compression Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    for (const auto& chunk : compressedChunks)
        outFile << chunk;

    // Decompression timing
    start = chrono::high_resolution_clock::now();
    threads.clear();
    for (int i = 0; i < numChunks; ++i) {
        threads.emplace_back(decompressWorker, ref(compressedChunks), ref(decompressedChunks), i);
    }
    for (auto& th : threads) th.join();
    end = chrono::high_resolution_clock::now();
    cout << "Decompression Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    for (const auto& chunk : decompressedChunks)
        deFile << chunk;

    return 0;
}
