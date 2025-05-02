#ifndef PHASE_FOURTH_HPP
#define PHASE_FOURTH_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
class PhaseFourth: public Phase {
public:
    int spikeCount = 0;
    std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;

    explicit PhaseFourth() { phase = Enum::PhaseEnum::PhaseFourth; }

    void Start() override;
    void Update() override;
    void End() override;
};

#endif // PHASE_FOURTH_HPP