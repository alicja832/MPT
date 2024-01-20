#pragma once
#include <cstdint>
#include <vector>
#include <memory>

template <typename T>
class Packet
{
    uint64_t id;
    std::vector<uint64_t> depends_on;
    std::shared_ptr<T> obj;

public:
    Packet(uint64_t id, std::shared_ptr<T> obj, std::vector<uint64_t> depends_on) : id{id}, obj{obj}, depends_on(depends_on) {}
    uint64_t get_id() const { return id; }
    std::vector<uint64_t> get_depends_on_ids() const { return depends_on; }
    std::shared_ptr<T> get_obj() const { return obj; }
};
