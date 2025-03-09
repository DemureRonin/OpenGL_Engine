#pragma once
#include <atomic>
#include <string>
#include <sstream>
#include <iomanip>

namespace Engine {
    struct UIID {
        uint32_t id;

        UIID() : id(Generate()) {}

        static uint32_t Generate() {
            static std::atomic<uint32_t> counter(1); 
            return counter.fetch_add(1, std::memory_order_relaxed);
        }

        std::string ToString() const {
            std::ostringstream oss;
            oss << "UIID-" << std::hex << std::setw(8) << std::setfill('0') << id;
            return oss.str();
        }

        bool operator==(const UIID& other) const {
            return id == other.id;
        }

        friend std::ostream& operator<<(std::ostream& os, const UIID& uiid) {
            return os << uiid.ToString();
        }
    };
}

// Specialization of std::hash for UIID
namespace std {
    template<>
    struct hash<Engine::UIID> {
        size_t operator()(const Engine::UIID& uiid) const noexcept {
            return std::hash<uint32_t>{}(uiid.id);
        }
    };
}
