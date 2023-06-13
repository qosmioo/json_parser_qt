#ifndef FACADE_H
#define FACADE_H
#include <iostream>
#include <memory>
#include "work_with_file.h"
#include "json_checker.h"

class Facade {
private:
    Work_with_file file_worker;
    Json_checker json_cheker;
public:
    Facade (Work_with_file file_worker, Json_checker json_checker) {
        this->file_worker = file_worker;
        this->json_cheker = json_checker;
    }
    ~Facade(){};
    std::string fp;
    std::string read_operation(const std::string& fp);
    void check_operation(const std::string& ft);
};

#endif // FACADE_H
