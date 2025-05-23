#ifndef PHASE_Fifth_HPP
#define PHASE_Fifth_HPP

#include "Phase.hpp"
#include "component/FallingObstacle.hpp"
#include "component/stairs.hpp"
class PhaseFifth : public Phase {

public:
    int spikeCount = 0;
    int obstacleTimer = 0;
    std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;
    int m_initialTimer = 0;
    float move_speed = 1.3f;
    bool isBouncing = false;

    std::vector<std::shared_ptr<FallingObstacle>> m_obstacles;

    explicit PhaseFifth() { phase = Enum::PhaseEnum::PhaseFifth; }

    void Start() override;
    void Update() override;
    void End() override;
};

#endif // PHASE_Fifth_HPP