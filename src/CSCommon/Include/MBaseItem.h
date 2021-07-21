#ifndef _MBASEITEM_H
#define _MBASEITEM_H


#define MAX_ITEM_COUNT					100			// �ѻ���� �ִ�� ���� �� �ִ� ������ ����
//#define RENT_PERIOD_UNLIMITED			(8760)		// �Ⱓ�� ������ hour period�� 8760�̸� ������(1��)
#define RENT_MINUTE_PERIOD_UNLIMITED	(525600)	// Ŭ���̾�Ʈ���״� �Ⱓ�� ������ �Ⱓ�� minute������ ������. 525600�̸� ������(1��)


// ������. ����, Ŭ���̾�Ʈ ������ �θ� Ŭ����
class MBaseItem
{
protected:
	bool				m_bIsRentItem;						///< �Ⱓ�� ���������� ����
	int					m_nRentMinutePeriodRemainder;		///< �Ⱓ�� �����Ⱓ(�д���)
	bool				m_bIsSpendingItem;					///< �Һ���������� ����
	int					m_nCount;							///< ����
public:
	MBaseItem(): m_bIsRentItem(false), m_nRentMinutePeriodRemainder(RENT_MINUTE_PERIOD_UNLIMITED), m_bIsSpendingItem(false),
					m_nCount(0) { }
	virtual ~MBaseItem() = default;
	bool IsRentItem()		{ return m_bIsRentItem; }
	bool IsSpendingItem()	{ return m_bIsSpendingItem; }
	int GetRentMinutePeriodRemainder() { return ((IsRentItem()) ? m_nRentMinutePeriodRemainder : RENT_MINUTE_PERIOD_UNLIMITED); }
	void SetRentItem(int nRentMinutePeriodRemainder)	
	{ 
		m_bIsRentItem=true; 
		m_nRentMinutePeriodRemainder=nRentMinutePeriodRemainder; 
	}
};


#endif