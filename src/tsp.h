class TSP {
private:
    const char * matrixFile;
public:
    TSP(const char * matrixFile){
        this->matrixFile = matrixFile;
    }
    void sequential();
    void parallel(); //compilar independientemente
};