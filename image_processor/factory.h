#pragma once
#include "filter_structure.h"
#include "bmp_reader_writer.h"
#include <functional>
#include <memory>
#include <unordered_map>

class Filter {
public:
    virtual void Apply(BmpHolder& image) const = 0;
    virtual ~Filter() = default;

};

class Factory {
public:
    Factory();
    void Register(std::string_view name, std::function<std::unique_ptr<Filter>()> creator);
    std::unique_ptr<Filter> Create(std::string_view name);

private:
    std::unordered_map<std::string_view, std::function<std::unique_ptr<Filter>()>> name_to_func_;
};
