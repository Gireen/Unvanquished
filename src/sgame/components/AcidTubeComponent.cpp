#include "common/Common.h"
#include "AcidTubeComponent.h"
#include "../Entities.h"

const float AcidTubeComponent::ATTACK_DAMAGE      = 20.0f;
const float AcidTubeComponent::ATTACK_RANGE       = ACIDTUBE_RANGE;
const int   AcidTubeComponent::ATTACK_ANIM_PERIOD = 2000;

AcidTubeComponent::AcidTubeComponent(Entity& entity, AlienBuildableComponent& r_AlienBuildableComponent)
	: AcidTubeComponentBase(entity, r_AlienBuildableComponent), lastAttackAnimation(-1) {
	// TODO: Adjust after DaemonDevelopers/CBSE-Toolchain#28 is complete.
	GetAlienBuildableComponent().GetBuildableComponent().REGISTER_THINKER(
		ConsiderAttack, ThinkingComponent::SCHEDULER_AVERAGE, 100);
}

void AcidTubeComponent::ConsiderAttack(int timeDelta) {
	if (!GetAlienBuildableComponent().GetBuildableComponent().Active()) return;

	bool attacking = Entities::AntiHumanRadiusDamage(entity, ATTACK_DAMAGE * timeDelta * 0.001f,
	                                                 ATTACK_RANGE, MOD_ATUBE);

	if (attacking && (lastAttackAnimation < 0 || level.time - lastAttackAnimation > 2000)) {
		G_SetBuildableAnim(entity.oldEnt, BANIM_ATTACK1, false);
		G_AddEvent(entity.oldEnt, EV_ALIEN_ACIDTUBE, DirToByte(entity.oldEnt->s.origin2));
		lastAttackAnimation = level.time;
	}
}
