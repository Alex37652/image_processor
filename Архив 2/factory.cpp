#include "factory.h"

#include <memory>

Factory::Factory() : name_to_func_() {
}

void Factory::Register(std::string_view name, std::function<std::unique_ptr<Filter>()> creator) {
    name_to_func_[name] = std::move(creator);
}

std::unique_ptr<Filter> Factory::Create(std::string_view name) {
    return name_to_func_[name]();
}
