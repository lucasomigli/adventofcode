#ifndef DAY09_H
#define DAY09_H

#include "../utils2024.h"

long checksum(const std::vector<int>& disk) {
    long sum = 0;
    for (size_t i = 0; i < disk.size(); ++i) {
        sum += i * disk[i];
    }
    return sum;
}

std::vector<int> transform_line(const std::string& line) {
    std::vector<int> disk;
    int leftIndex = 0;
    int rightIndex = line.size() - 1;
    int moveBlockSize = line[rightIndex] - '0';

    while (leftIndex < rightIndex) {
        int n = line[leftIndex] - '0';
        if (leftIndex % 2 == 0) {
            disk.insert(disk.end(), n, leftIndex / 2);
        } else {
            for (int i = 0; i < n; ++i) {
                if (moveBlockSize < 1) {
                    rightIndex -= 2;
                    moveBlockSize = line[rightIndex] - '0';
                }
                if (rightIndex > leftIndex) {
                    moveBlockSize--;
                    disk.push_back(rightIndex / 2);
                }
            }
        }
        ++leftIndex;
    }

    if (rightIndex >= leftIndex && moveBlockSize > 0) {
        disk.insert(disk.end(), moveBlockSize, rightIndex / 2);
    }

    return disk;
}

inline long Solver::Solve_Day09_part1() {
    {
        std::ifstream file(this->fileInput);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileInput << std::endl;
            return 0;
        }

        std::string line;
        if (!std::getline(file, line) || line.size() < 2) {
            return 0;
        }

        std::vector<int> transformed = transform_line(line);
        return checksum(transformed);
    }
}

struct BlockInfo {
    int index;
    int size;
};

class FreeBlockMap {
   private:
    std::vector<BlockInfo> freeBlocks;

   public:
    void append(const BlockInfo& block) {
        freeBlocks.push_back(block);
    }

    BlockInfo* find_space(int spaceRequired) {
        for (auto& block : freeBlocks) {
            if (block.size >= spaceRequired) {
                return &block;
            }
        }
        return nullptr;
    }
};

class Disk {
   private:
    std::vector<int> data;
    std::unordered_map<int, BlockInfo> files;
    FreeBlockMap freeBlocks;

   public:
    void append(int block_count, int value) {
        data.insert(data.end(), block_count, value);
    }

    void move(int from, int to, int block_count) {
        std::copy(data.begin() + from, data.begin() + from + block_count, data.begin() + to);
        std::fill(data.begin() + from, data.begin() + from + block_count, -1);
    }

    void write_file(int id, int size) {
        files[id] = {last_index(), size};
        append(size, id);
    }

    void write_empty_blocks(int size) {
        freeBlocks.append({last_index(), size});
        append(size, -1);
    }

    void defragment() {
        for (auto it = files.begin(); it != files.end(); ++it) {  // d
            int file_size = it->second.size;
            BlockInfo* free_space = freeBlocks.find_space(file_size);
            if (free_space && free_space->index < it->second.index) {
                move(it->second.index, free_space->index, file_size);
                free_space->index += file_size;
                free_space->size -= file_size;
            }
        }
    }

    long checksum() const {
        long sum = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] != -1) {
                sum += i * data[i];
            }
        }
        return sum;
    }

    int last_index() const {
        return data.size();
    }
};

bool is_file(int x) {
    return x % 2 == 0;
}

inline long Solver::Solve_Day09_part2() {
    std::ifstream file(this->fileInput);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileInput << std::endl;
        return 0;
    }

    std::string line;
    if (!std::getline(file, line) || line.size() < 2) {
        return 0;
    }

    std::vector<int> input;
    for (char c : line) {
        fileInput.push_back(c - '0');
    }

    Disk disk;

    for (size_t i = 0; i < input.size(); ++i) {
        int size = input[i];
        if (is_file(i)) {
            disk.write_file(i / 2, size);
        } else {
            disk.write_empty_blocks(size);
        }
    }

    disk.defragment();

    return disk.checksum();
};

#endif