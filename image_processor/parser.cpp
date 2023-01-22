#include "parser.h"

Parser::Parser() : positional_args_(), keyword_fields_(), filters_() {}

void Parser::AddPositionalArg(const std::string &arg_name, Parser::Argument output) {
    positional_args_.push_back(std::make_pair(arg_name, output));
}

void Parser::AddKeywordArg(const std::string &keyword, const std::vector<std::pair<std::string, Argument>> args) {
    keyword_fields_[keyword] = args;
}

void Parser::Parse(size_t argc, char **argv) {
    if (argc == 1) {
        throw "command line argument format descriptions: {program name} {input file} {output file} [-{filter 1} [filter parameter 1] [filter parameter 2] ...] [-{filter 2} [filter parameter 1] [filter parameter 2] ...] ...";
    }
    if (argc == 2) {
        throw "no input or output file";
    }
    for (size_t i = 0; i < positional_args_.size(); ++i) {
        Internal assign(argv[i + 1]);
        std::visit(assign, positional_args_[i].second);
        auto file_name = get<std::string *>(positional_args_[i].second);
        if (file_name->size() < 5 or file_name->substr(file_name->size() - 4, file_name->size()) != ".bmp") {
            throw "Invalid input or output file format";
        }
    }
    for (size_t i = positional_args_.size() + 1; i < argc; ++i) {
        auto it = keyword_fields_.find(argv[i]);
        if (it == keyword_fields_.end()) {
            throw "Invalid filter name";
        }
        filters_.push_back(argv[i]);
        auto param_required = it->second.size();
        for (size_t j = 1; j <= param_required; ++j) {
            if (i + j >= argc) {
                throw "Incorrect amount of arguments";
            }
            Internal assign(argv[i + j]);
            std::visit(assign, it->second[j - 1].second);
        }
        if (i + param_required + 1 < argc &&
            keyword_fields_.find(argv[i + param_required + 1]) == keyword_fields_.end()) {
            throw "Incorrect amount of arguments";
        }
        i += param_required;
    }
}

std::vector<std::string> Parser::GetFilters() const {
    return filters_;
}

Parser::Internal::Internal(const char *data) : data_(data) {}

void Parser::Internal::operator()(std::string *s) {
    *s = std::string(data_);
}

void Parser::Internal::operator()(size_t *s) {
    *s = std::stoi(data_);
}

void Parser::Internal::operator()(double *s) {
    *s = std::stod(data_);
}
