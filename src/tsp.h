#include <string>

class TSP {
private:
    std::string matrixFile;
public:
    TSP(std::string matrixFile){
        this->matrixFile = matrixFile;
    }
    void sequential();
    void parallel();
};