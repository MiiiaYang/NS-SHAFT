#ifndef PHASE_THIRD_HPP
#define PHASE_THIRD_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
class PhaseThird: public Phase {
public:
    int spikeCount = 0;
    std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;

    explicit PhaseThird() { phase = Enum::PhaseEnum::PhaseThird; }
    int m_initialTimer=0;
    void Start() override;
    void Update() override;
    void End() override;
};

#endif // PHASE_THIRD_HPP