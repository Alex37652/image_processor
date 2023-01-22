#include "factory.h"
#include "filter_structure.h"

class MyFilter : public Filter {
public:
    MyFilter(const MyFilterParams &params);

    static std::unique_ptr<MyFilter> CreateMyFilter(const MyFilterParams &params);

    void Apply(BmpHolder &image) const override;

private:
    MyFilterParams params_;
};
