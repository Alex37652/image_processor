#pragma once

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

class Parser {
public:
    using Argument = std::variant<std::string *, double *, size_t *>;

    Parser();

    void AddPositionalArg(const std::string &arg_name, Argument output);

    void AddKeywordArg(const std::string &keyword, const std::vector<std::pair<std::string, Argument>> args);

    void Parse(size_t argc, char **argv);

    std::vector<std::string> GetFilters() const;

    struct Internal {
        explicit Internal(const char *data);

        void operator()(std::string *s);

        void operator()(size_t *s);

        void operator()(double *s);

    private:
        const char *data_;
    };

private:
    std::vector<std::pair<std::string, Argument>> positional_args_;
    std::unordered_map<std::string, std::vector<std::pair<std::string, Argument>>> keyword_fields_;
    std::vector<std::string> filters_;
};
