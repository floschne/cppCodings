//
// Created by p0w3r on 16.03.16.
//

#ifndef PIPELINETESTC_11_PIPELINESTAGE_H
#define PIPELINETESTC_11_PIPELINESTAGE_H


#include <iostream>
#include <condition_variable>

class PipelineStage {
public:

    PipelineStage() {
        _id++;
    }

    ~PipelineStage() = default;

    static uint8_t _id;
    bool _run{false};

    void wait();
    void step();

    void operator()(){
        while(_run) {
            wait();
            step();
        }
    }
};


#endif //PIPELINETESTC_11_PIPELINESTAGE_H
