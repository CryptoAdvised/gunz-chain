// �����п� ���õ� �Լ���
//
// ������
// �Ÿ� : ����
// �ð� : ��
//
#ifndef PHYSICS_H
#define PHYSICS_H

#include "RTypes.h"

/// �߷� ���ӵ�
#define GRAVITY_ACCELERATION 9.8f

/// ������ �
v3 ParabolicMotion(const v3& InitialVelocity, float fSec);

template <typename T>
bool MoveMovingWeapon(const v3 & Pos, v3 & Vel, const T& Pick)
{
	return false;
}


#endif