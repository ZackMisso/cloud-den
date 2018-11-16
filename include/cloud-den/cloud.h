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

    void previewTransmittanceFromDir(Direction dir, string filename="test.png")
    {
        switch (dir)
        {
            case POS_X:
            case NEG_X:
                {
                    // TODO
                    break;
                }
            case POS_Y:
            case NEG_Y:
                {
                    // TODO
                    break;
                }
            case POS_Z:
            case NEG_Z:
                {
                    // TODO
                    break;
                }
            default:
                {
                    std::cout << "Unrecognized Direction" << std::endl;
                }
        }
    }
protected:
    std::vector<DensityEmitter<T>*> densityEmitters;
    std::vector<T> sigma_s;
    std::vector<T> sigma_a;
};
