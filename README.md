COMPANY:CODETECH IT SOLUTIONS
NAME:VIPUL KUMAR
INTERN ID:CT04DH2995
MENTOR:NEELA SANTHOSH
DURATION:4 WEEK
DOMAIN:C++ PROGRAMMING


# MULTITHREADED-FILE-COMPRESSION-TOOL
This project is a high-performance tool developed in C++ that compresses and decompresses files using multithreading. It aims to demonstrate performance optimization by dividing the file into chunks and processing them in parallel.

---

## 📌 Objective

The goal was to implement a practical system that handles both compression and decompression efficiently, especially for large files. Traditional compression processes are single-threaded, which can be slow for big data. This tool addresses that by using C++ threads to divide and conquer the workload.

---

## ⚙ How It Works

The tool reads an input file and splits it into fixed-size chunks. Each chunk is assigned to a separate thread. Compression (and later decompression) of these chunks happens concurrently using Run-Length Encoding (RLE) — a simple yet effective compression method suitable for repetitive data patterns.

Once all threads finish their tasks, the compressed results are merged into one output file. Similarly, during decompression, each compressed chunk is restored using threads and merged into the final output.

---

## 🛠 Components Used

- *Language*: C++ (Standard C++11 and above)
- *Multithreading*: std::thread, mutex, and lock_guard for thread safety
- *File Handling*: fstream for reading/writing files
- *Compression Logic*: Custom Run-Length Encoding (RLE)
- *Timer*: chrono library used to benchmark performance

---

## 🚀 Performance

During execution, the tool measures the time taken to compress and decompress using multiple threads. This clearly shows how parallelism reduces total processing time, especially on multicore processors.

The compression speed is significantly faster when compared to a single-threaded approach, particularly with large data files (e.g., >10MB).

---

## 📂 Files

- main.cpp – Core logic for compression, decompression, multithreading, and file operations
- input.txt – Source text file to be compressed
- compressed.txt – Output after compression
- decompressed.txt – Output after restoring original file

- ![Image](https://github.com/user-attachments/assets/5245ec5a-5476-474a-a196-1960bd17c581)

- ![Image](https://github.com/user-attachments/assets/9ce08653-0c5a-443f-81bc-6a022ce15348)


