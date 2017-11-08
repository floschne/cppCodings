//
// Created by p0w3r on 16.03.16.
//

#include "PipelineStage.h"

uint8_t PipelineStage::_id = 0;

void PipelineStage::step() {
    std::cout << _id <<  " : step working" << std::endl;
}

void PipelineStage::wait() {
    std::cout << _id << " : waiting for work.." << std::endl;
}
