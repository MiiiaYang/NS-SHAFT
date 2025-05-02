#ifndef PHASE_FOURTH_HPP
#define PHASE_FOURTH_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
#include "component/FallingObstacle.hpp"
class PhaseFourth: public Phase {
public:
    int spikeCount = 0;
    std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;
    int m_initialTimer = 0;
    explicit PhaseFourth() { phase = Enum::PhaseEnum::PhaseFourth; }

    std::vector<std::shared_ptr<FallingObstacle>> m_obstacles;

    void Start() override;
    void Update() override;
    void End() override;
};

#endif // PHASE_FOURTH_HPP