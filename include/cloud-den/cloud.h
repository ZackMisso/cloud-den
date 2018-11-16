#pragma once

#include <cloud-den/dense_emitter.h>
#include <vector>

template<typename T>
class Cloud
{
public:
    Cloud(int w, int h, int d)
    {
        density = std::vector<T>(w*h*d);
    }

    ~Cloud()
    {
        for (int i = 0; i < densityEmitters.size(); ++i)
            delete densityEmitters[i];
    }

    void addDensityEmitter(DensityEmitter<T>* emitter)
    {
        densityEmitters.push_back(emitter);
    }
protected:
    std::vector<DensityEmitter<T>*> densityEmitters;
    std::vector<T> density;
};
