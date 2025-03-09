#pragma once
#include <array>
#include <random>
#include <sstream>
#include <iomanip>

namespace Engine {
    struct GUID {
        std::array<uint8_t, 16> data;

        static GUID Generate() {
            GUID guid;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<uint32_t> dist(0, 255);

            for (auto& byte : guid.data) {
                byte = static_cast<uint8_t>(dist(gen)); 
            }
            return guid;
        }
        static GUID FromString(const std::string& str) {
            GUID guid = {};
            std::istringstream iss(str);
            std::string segment;
            size_t index = 0;

            for (char c : str) {
                if (c != '-') {
                    if (index >= 32) break; 
                    segment += c;
                }
            }

            if (segment.length() != 32) {
                throw std::invalid_argument("Invalid GUID format: " + str);
            }

            for (size_t i = 0; i < 16; ++i) {
                std::string byteStr = segment.substr(i * 2, 2);
                guid.data[i] = static_cast<uint8_t>(std::stoul(byteStr, nullptr, 16));
            }

            return guid;
        }
        std::string ToString() const {
            std::ostringstream oss;
            for (size_t i = 0; i < data.size(); ++i) {
                if (i == 4 || i == 6 || i == 8 || i == 10) oss << "-";
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
            }
            return oss.str();
        }

        bool operator==(const GUID& other) const {
            return data == other.data;
        }
        friend std::ostream& operator<<(std::ostream& os, const GUID& guid) {
            return os << guid.ToString();
        }
    };
}


namespace std {
    template<>
    struct hash<Engine::GUID> {
        size_t operator()(const Engine::GUID& guid) const noexcept
        {
            size_t hash = 0;
            for (auto byte : guid.data) {
                hash = (hash * 31) ^ byte;
            }
            return hash;
        }
    };
}
