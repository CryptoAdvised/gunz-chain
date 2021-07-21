#ifndef _ZWeaponMgr_h
#define _ZWeaponMgr_h

#include <list>
using namespace std;

#include "RTypes.h"
#include "RVisualMeshMgr.h"
#include "ZWeapon.h"

// ����ź
// ������ġ�ְ�
// �����ְ� (���ӵ�)
// define �Ҹ�ð� ( �ʰ��� ��ġ���� , ź�� )
// ���� ����ź���� �˾ƾ� �ϴ°�? ( ���߿� ���� �ֱ� ����,ų���� �ø��ų�.. ) ( ��� ǥ�� )
// Effect
enum eCrashType{
	et_crash_none = 0,
	et_crash_wall,
	et_crash_floor
};

class ZCharacter;
class ZEffectBillboardSource;

typedef list<ZWeapon*>			z_weapon_list;
typedef z_weapon_list::iterator	z_weapon_node;

class ZWeaponMgr {
public:
	ZWeaponMgr();
	~ZWeaponMgr();

public:
	void Add(ZWeapon* pWeapon) {
		m_list.push_back(pWeapon);
	}
	void Clear();
	void AddGrenade(const rvector& pos,const rvector& velocity,ZObject* pC);
	void AddRocket(const rvector& pos,const rvector& dir,ZObject* pC);
	void AddMagic(ZSkill* pSkill, const rvector& pos, const rvector& dir,ZObject* pOwner);
	void AddFlashBang(const rvector& pos,const rvector& dir,ZObject* pC);
	void AddSmokeGrenade(const rvector& pos,const rvector& velocity,ZObject* pC);

	void AddKit(const rvector& pos, const rvector& velocity, ZCharacter* pC, float Delaytime,
		const char *szMeshName, int nLinkedWorldItemID);

	void Update();
	void Render();

	ZMovingWeapon*	UpdateWorldItem(int nItemID, const rvector& pos);//���� �����۰� �������� ���� ����͵�...
	ZWeapon*		GetWorldItem(int nItemID);

	z_weapon_list m_list;

protected:

	bool	SamePoint(rvector& p1,rvector& p2);

	float	m_fLastTime;

};

#endif//_ZWeaponMgr_h