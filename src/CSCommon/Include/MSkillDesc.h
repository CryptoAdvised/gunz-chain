#ifndef MSKILLDESC_H
#define MSKILLDESC_H


#include "MSkillTypes.h"
#include "MObjectTypes.h"


#include <map>
using namespace std;

#define FILENAME_SKILL_DESC		"system/skill.xml"


/// ��ų
/// enum�� �����ϰ��� ��ȹ���� �ִ� �״�� Ÿ���� ����. ���� ��� �Է¿� ���� ���� �ʿ�.
class MSkillDesc{
public:
	// �ĺ�
	int				nID;
	char			Name[32];

	// �з�
	MSkillType			SkillType;
	MSkillFomulaType	SkillFomulaType;
	MPrimaSkill			PrimaSkill;

	// Stack
	unsigned int	StackFlag1;
	unsigned int	StackFlag2;
	unsigned int	OverwriteFlag1;
	unsigned int	OverwriteFlag2;

	// ���
	short int		nHP;
	short int		nEN;

	// �ð�
	short int		nActivationTime;
	short int		nReactivationTime;
	short int		nDuration;

	// ���
	MTargetType		TargetType;
	MSpecies		Species;

	// �Ÿ�
	unsigned char	nRangeMin;
	unsigned char	nRangeMax;
	unsigned char	nRadius;

	// ����
	MCharacterClass	Class;
	unsigned char	nLevel;
	MWeaponType		WeaponType;
	unsigned char	nDifficulty;
	unsigned short	PrerequisiteType;
	int				nPrerequisiteID;

	// ���밨
	int				nHateValue;

	unsigned int	MODFlags;

	// �ǰ� ����ġ
	unsigned short	MOD_HP;
	unsigned short	MOD_EN;

	// Ư��ġ ����
	unsigned short	MOD_STR;
	unsigned short	MOD_CON;
	unsigned short	MOD_DEX;
	unsigned short	MOD_AGI;
	unsigned short	MOD_INT;
	unsigned short	MOD_CHA;

	// ���׷� ����ġ
	unsigned short	MOD_MR;
	unsigned short	MOD_FR;
	unsigned short	MOD_CR;
	unsigned short	MOD_PR;
	unsigned short	MOD_LR;
	unsigned char	nResist;
	unsigned char	nResistAdjust;

	// ���� ����ġ
	unsigned short	MOD_AC;
	unsigned short	MOD_ABS;
	unsigned short	MOD_MFlee;
	unsigned short	MOD_RFlee;
	unsigned short	MOD_SFlee;
	unsigned short	MOD_HPRegen;
	unsigned short	MOD_ENRegen;

	// ���ݷ� ����ġ
	unsigned short	MOD_PriATK;
	unsigned short	MOD_SecATK;
	unsigned short	MOD_Aspd;
	unsigned short	MOD_MCritical;
	unsigned short	MOD_RCritical;
	unsigned short	MOD_SCritical;
	unsigned short	MOD_MAccu;
	unsigned short	MOD_RAccu;
	float			MOD_DamageAmp;

	// �Ϲ� ����ġ
	unsigned short	MOD_DSight;
	unsigned short	MOD_NSight;
	unsigned short	MOD_Spd;

	// ���� ����ġ
	unsigned short	MOD_Mode;
	unsigned short	MOD_State;
	unsigned short	MOD_Ability;

	// ���� ����ġ
	unsigned short	MOD_KeyFlag;
	unsigned short	MOD_KeySkill;

	// ������ ��ų ����ġ
	unsigned short	MOD_OCS;
	unsigned short	MOD_DCS;
	unsigned short	MOD_RCS;
	unsigned short	MOD_ECS;
	unsigned short	MOD_OMS;
	unsigned short	MOD_DMS;
	unsigned short	MOD_EMS;
	unsigned short	MOD_MCS;
	unsigned short	MOD_SCS;

	// �����
	unsigned short	nIcon;
	unsigned short	nActivationAni;
	unsigned short	nUseAni;
	unsigned short	nHitAni;
	unsigned short	nSound;

public:
	MSkillDesc(int id, char* name);

	bool ExamMODFlag(unsigned int nFlag)	{ return (MODFlags & nFlag)? true:false; }
	void SetMODFlag(unsigned int nFlag)		{ MODFlags |= nFlag; }
	void ResetMODFlag() { MODFlags = 0; }
};


class MSkillDescManager : public map<int, MSkillDesc*>
{
private:
protected:

public:
	MSkillDescManager();
	virtual ~MSkillDescManager();
	bool Read(const char* szFileName);
	void Clear();
	MSkillDesc* Find(int nDescID);
};

extern MSkillDescManager	g_SkillDescManager;


#endif