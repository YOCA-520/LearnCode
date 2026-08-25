#include <iostream>
#include <nlohmann/json.hpp>
#include "logger.h"

int main() {
    Logger logger{"runlog.log"};
    logger.info("Hello World!");
    logger.error("failed open the file");
    logger.warning("manba out");
    std::cout <<"program over"<< std::endl;

}