#pragma once

#include <string>
#include "MCommand.h"
#include "MZFileSystem.h"

#define ZOK										0			///< ��������
#define ZERR_UNKNOWN							-1			///< ���� ���ϴ� ����


// Ŭ���̾�Ʈ �����޽��� ��
#define MSG_WARNING								500			///< ����
#define MSG_REROUTE_TO_WEBSITE					501			///< ����


/// Ŭ���̾�Ʈ �������̽� ����
#define MSG_119_REPORT_WAIT_ONEMINUTE			1000		///< 1���Ŀ� �Ű����մϴ�.
#define MSG_119_REPORT_OK						1001		///< 119 �Ű��Ͽ����ϴ�.
#define MSG_CANNOT_CHAT							1002		///< ä���� �� �����ϴ�.
#define MSG_YOU_MUST_WRITE_MORE					1003		///< $1�����̻� ���� ����� �մϴ�.		// $1 - ���ڼ�
#define MSG_LESS_ARGUMENT						1004		///< ���ڰ� �����մϴ�.
#define MSG_WRONG_ARGUMENT						1005		///< ���ڰ� Ʋ�Ƚ��ϴ�.
#define MSG_MUST_EXECUTE_LOBBY					1006		///< �κ񿡼��� ���డ���մϴ�.
#define MSG_MUST_EXECUTE_STAGE					1007		///< ���濡���� ���డ���մϴ�.
#define MSG_MUST_EXECUTE_GAME					1008		///< ���ӿ����� ���డ���մϴ�.
#define MSG_CANCELED							1009		///< ��ҵǾ����ϴ�.
#define MSG_CANNOT_CHAT_CMD						1010		///< ��ɾ ����� �� �����ϴ�.
#define MSG_SCREENSHOT_SAVED					1011		///< ��ũ������ $1 �� ����Ǿ����ϴ�.
#define MSG_SCREENSHOT_CANT_SAVE				1012		///< ��ũ���� ������ �����Ͽ����ϴ�.
#define MSG_RECORD_STARTING						1013		///< ��ȭ�� ���۵Ǿ����ϴ�.
#define MSG_RECORD_SAVED						1014		///< ��ȭ�� $1 �� ����Ǿ����ϴ�.
#define MSG_RECORD_CANT_SAVE					1015		///< ��ȭ ������ �����Ͽ����ϴ�.
#define MSG_VOTE_KICK							1016		///< '%s' ���� �������忡 ���� ��ǥ�� �������Դϴ�
#define MSG_VOTE_YESNO							1017		///< ������ 'Y' �ݴ�� 'N' �� �����ø� �˴ϴ�.
#define MSG_VOTE_SELECT_PLAYER_TO_KICK			1018		///< �߹���ǥ�� ����� �����ϼ���
#define MSG_VOTE_SELECT_PLAYER_CANCEL			1019		///< [ESC] ���
#define MSG_VOTE_PASSED							1020		///< ��ǥ�� ����Ǿ����ϴ�.
#define MSG_VOTE_REJECTED						1021		///< ��ǥ�� �ΰ�Ǿ����ϴ�.
#define MSG_VOTE_ABORT							1022		///< ��ǥ������ �Ǿ����� �ʽ��ϴ�.
#define MSG_VOTE_START							1023		///< '%s' �� ���� ��ǥ�� ���۵Ǿ����ϴ�.
#define MSG_VOTE_VOTE_STOP						1025		///< ��ǥ ��� �÷��̾ ���ӿ��� �������ϴ�.

#define MSG_CLAN_SPONSOR_AGREEMENT_LABEL		1105		///< $1�Բ��� $2�԰� �Բ� '$3'Ŭ���� �Ἲ�Ϸ��� �մϴ�. �����Ͻʴϱ�?	
															// $1 - Ŭ���������, $2 - Ŭ��������, $3 - Ŭ���̸�
#define MSG_CLAN_SPONSOR_AGREEMENT_REJECT		1106		///< $1�Բ��� Ŭ�� �Ἲ�� �����Ͽ����ϴ�.	// $1 - Ŭ��������� ���
#define MSG_CLAN_CREATED						1107		///< Ŭ���� �����Ǿ����ϴ�.
#define MSG_CLAN_CLOSE_RESERVED					1108		///< Ŭ�� ��� ����Ǿ����ϴ�.
#define MSG_CLAN_ENABLED_TO_MASTER				1109		///< Ŭ�������͸� ������ �� �ֽ��ϴ�.
#define MSG_CLAN_ENABLED_TO_MASTER_AND_ADMIN	1110		///< Ŭ�������Ϳ� Ŭ����ڸ� ������ �� �ֽ��ϴ�.
#define MSG_CLAN_JOINED_ALREADY					1111		///< �̹� Ŭ���� ���ԵǾ� �ֽ��ϴ�.
#define MSG_CLAN_NOT_JOINED						1112		///< Ŭ���� ���ԵǾ� ���� �ʽ��ϴ�.
#define MSG_CLAN_JOINER_AGREEMENT_LABEL			1113		///< '$1' Ŭ�� ������ �����Ͻʴϱ�?		// $1 - Ŭ���̸�
#define MSG_CLAN_JOINER_AGREEMENT_REJECT		1114		///< �����ڰ� �����Ͽ����ϴ�.
#define MSG_CLAN_JOINED							1115		///< Ŭ���� ���ԵǾ����ϴ�.
#define MSG_CLAN_LEAVED							1116		///< Ŭ������ Ż��Ǿ����ϴ�.
#define MSG_CLAN_MASTER_CANNOT_LEAVED			1117		///< Ŭ�������ʹ� Ŭ������ Ż���� �� �����ϴ�.
#define MSG_CLAN_PLEASE_LEAVE_FROM_CHAR_DELETE	1118		///< Ŭ���� ���ԵǾ� ������ ������ �� �����ϴ�. Ŭ������ Ż�����ֽʽÿ�.
#define MSG_CLAN_CHANGED_GRADE					1119		///< ������ ����Ǿ����ϴ�.
#define MSG_CLAN_EXPEL_MEMBER					1120		///< Ż����׽��ϴ�.
#define MSG_CLAN_CREATE_NEED_SOME_SPONSOR		1121		///< Ŭ���� �����ϱ� ���ؼ��� $1���� â�� ����� �����ϼž� �մϴ�.
#define MSG_CLAN_CONFIRM_CLOSE					1122		///< ������ Ŭ���� ����Ű�ڽ��ϱ�?
#define MSG_CLAN_CONFIRM_LEAVE					1123		///< ������ Ŭ������ Ż���Ͻðڽ��ϱ�?
#define MSG_CLAN_WRONG_CLANNAME					1124		///< Ŭ���̸��� �ٸ��ϴ�.
#define MSG_CLAN_MEMBER_CONNECTED				1125		///< Ŭ���� $1���� �����Ͽ����ϴ�.

#define MSG_CANNOT_DELETE_CHAR_FOR_CASHITEM		1200		///< ĳ���������� ����ϰ��־� ������ �� �����ϴ�.
#define MSG_HAS_DELETED_CHAR					1201		///< ĳ���Ͱ� �����Ǿ����ϴ�.

#define MSG_BACKTOTHEPREV						1202		///< $1�� �ڿ� ���� �ػ󵵷� ���� �˴ϴ�

// �κ� ����
#define MSG_LOBBY_WELCOME1						1300		///< ����� ä�� '%1'�� �����ϼ̽��ϴ�.
#define MSG_LOBBY_CLAN_DETAIL					1301		///< Ŭ�������� : $1, $2�� ������
#define MSG_LOBBY_WAITING						1302		///< %1 �� �����
#define MSG_LOBBY_NO_CLAN						1303		///< Ŭ���� ���ԵǾ����� �ʽ��ϴ�
// �߰��� �κ�. 11. 13.
#define MSG_LOBBY_LIMIT_LEVEL					1304		///< ���������� ��ġ �����ø� ����ä���� �̿��� �ֽñ� �ٶ��ϴ�.
#define MSG_LOBBY_LEAGUE						1305		///< ���װ����� ä�ο� ������� ������ڵ�� �ܷ�� �˴ϴ�.
#define MSG_LOBBY_INVITATION					1306		///< $1���� ä�ù����� �ʴ��մϴ�.
#define MSG_LOBBY_WHO_INVITATION				1307		///< $1���� ä�ù� $2�� �ʴ��ϼ̽��ϴ�.
#define MSG_LOBBY_WHO_CHAT_ROMM_JOIN			1308		///< ä�ù� '$1'�� '$2'���� �����ϼ̽��ϴ�.
#define MSG_LOBBY_WHO_CHAT_ROOM_EXIT			1309		///< ä�ù� '$1'���� '$2'���� �����ϼ̽��ϴ�.
#define MSG_LOBBY_CHAT_ROOM_CHANGE				1310		///< ä�ù� '$1'�� ��ȯ�մϴ�.
//#define MRESULT_WHO_CHAT_ROOM_INVITATION		1311		///< $1' ���� ä�ù� '$2'�� �ʴ��ϼ̽��ϴ�.
#define MRESULT_CHAT_ROOM						1312		///< ä�ù�($1) $2 : $3
// #define MRESULT_WHISPER							100012	///< �ӼӸ�($1) : $2
// �߰��� �κ�. 11. 15.
#define MSG_LOBBY_REQUESTING_CREATE_CHAT_ROOM	1313		///< ä�ù� ���� ��û��...
#define MSG_LOBBY_REQUESTING_JOIN_CAHT_ROOM		1314		///< ä�ù� ���� ��û��...
#define MSG_LOBBY_LEAVE_CHAT_ROOM				1315		///< ä�ù濡�� Ż���մϴ�.
#define MSG_LOBBY_CHOICE_CHAT_ROOM				1316		///< ä�ù��� �����մϴ�.
#define MSG_LOBBY_JOIN_CHANNEL					1317		///< ����� ä�� '$1'�� �����߽��ϴ�.


// ���� ����
#define MSG_LADDER_PROPOSAL_WAIT_TITLE				1400		///< ���Ǵ��
#define MSG_LADDER_PROPOSAL_WAIT_DESC				1401		///< ���� ������ �÷��̾ ������ ���� ��ٷ��ֽʽÿ�.
#define MSG_LADDER_REPLIER_AGREEMENT_LABEL			1402		///< $1�Բ��� �����ӿ� �ʴ��ϼ̽��ϴ�. �����Ͻʴϱ�?
#define MSG_LADDER_REPLIER_AGREEMENT_REJECT			1403		///< $1�Բ��� �����Ͽ����ϴ�.	// $1 - ���
#define MSG_LADDER_CANCEL							1404		///< $1�Բ��� ����Ͽ����ϴ�.	// $1 - ���
#define MSG_LADDER_FAILED							1405		///< ������� ã�����߽��ϴ�.
#define MSG_LADDER_INVALID_COUNT					1406		///< ������ ������� ���ؾ��մϴ�.

/// ��Ʈ��ũ ���� �޼���
#define MSG_CLANBATTLE_REPLIER_AGREEMENT_LABEL		1420		/// $1�Բ��� Ŭ������ �ʴ��ϼ̽��ϴ�. �����Ͻʴϱ�?


// Ŭ���� ����
#define MSG_CLANBATTLE_BROADCAST_RENEW_VICTORIES_3	1510		///< '$1' Ŭ���� '$2' Ŭ������ �¸��Ͽ� $3�������� �⼼�� �ø��� �ֽ��ϴ�.
#define MSG_CLANBATTLE_BROADCAST_RENEW_VICTORIES_5	1511		///< '$1' Ŭ���� '$2' Ŭ������ �¸��Ͽ� $3����° �������Դϴ�.
#define MSG_CLANBATTLE_BROADCAST_RENEW_VICTORIES_7	1512		///< '$1' Ŭ���� '$2' Ŭ������ �¸��Ͽ� ��ħ���� $3������ �޸��� �ֽ��ϴ�.
#define MSG_CLANBATTLE_BROADCAST_RENEW_VICTORIES_10	1513		///< '$1' Ŭ���� '$2' Ŭ������ �¸��Ͽ� ����� $3���¿� �����Ͽ����ϴ�.
#define MSG_CLANBATTLE_BROADCAST_RENEW_VICTORIES_11	1514		///< '$1' Ŭ���� '$2' Ŭ������ �¸��Ͽ� $3������ �̾�� �ֽ��ϴ�.
#define MSG_CLANBATTLE_BROADCAST_INTERRUPT_VICTORIES 1515		///< '$1' Ŭ���� '$2' Ŭ���� $3������ �����Ͽ����ϴ�.

// ��� ����
#define MSG_DUEL_BROADCAST_RENEW_VICTORIES			1520		///< '$1' ���� '$2'ä���� $3�� �濡�� $4������ ������Դϴ�.
#define MSG_DUEL_BROADCAST_INTERRUPT_VICTORIES		1521		///< '$2' ���� '$1'���� $3������ �����Ͽ����ϴ�.


// �ε� �޽���
#define MSG_LOADING_MESSAGE11					1600		///< �ε�1 �޽���
#define MSG_LOADING_MESSAGE12					1601		///< 
#define MSG_LOADING_MESSAGE13					1602		///< 
#define MSG_LOADING_MESSAGE21					1603		///< �ε�2 �޽���
#define MSG_LOADING_MESSAGE22					1604		///< 
#define MSG_LOADING_MESSAGE23					1605		///< 
#define MSG_LOADING_MESSAGE31					1606		///< �ε�3 �޽���
#define MSG_LOADING_MESSAGE32					1607		///< 
#define MSG_LOADING_MESSAGE33					1608		///< 
#define MSG_LOADING_MESSAGE41					1609		///< �ε�4 �޽���
#define MSG_LOADING_MESSAGE42					1610		///< 
#define MSG_LOADING_MESSAGE43					1611		///< 
#define MSG_LOADING_MESSAGE51					1612		///< �ε�5 �޽���
#define MSG_LOADING_MESSAGE52					1613		///< 
#define MSG_LOADING_MESSAGE53					1614		///<
#define MSG_LOADING_MESSAGE61					1615		///< �ε�6 �޽���
#define MSG_LOADING_MESSAGE62					1616		///< 
#define MSG_LOADING_MESSAGE63					1617		///< 
#define MSG_LOADING_MESSAGE71					1618		///< �ε�7 �޽���
#define MSG_LOADING_MESSAGE72					1619		///< 
#define MSG_LOADING_MESSAGE73					1620		///< 
#define MSG_LOADING_MESSAGE81					1621		///< �ε�8 �޽���
#define MSG_LOADING_MESSAGE82					1622		///< 
#define MSG_LOADING_MESSAGE83					1623		///< 
#define MSG_LOADING_MESSAGE91					1624		///< �ε�9 �޽���
#define MSG_LOADING_MESSAGE92					1625		///< 
#define MSG_LOADING_MESSAGE93					1626		///< 

// ĳ���� ���� ǥ��
#define MSG_CHARINFO_TITLE						1700		///< [ĳ���� ����]=======================
#define MSG_CHARINFO_NAME						1701		///< �̸�
#define MSG_CHARINFO_CLAN						1702		///< Ŭ��
#define MSG_CHARINFO_LEVEL						1703		///< ����
#define MSG_CHARINFO_WINPERCENT					1704		///< �·�
#define MSG_CHARINFO_WIN						1705		///< ��
#define MSG_CHARINFO_LOSE						1706		///< ��
#define MSG_CHARINFO_CONNTIME					1707		///< ���ӽð�
#define MSG_CHARINFO_DAY						1708		///< ��
#define MSG_CHARINFO_HOUR						1709		///< �ð�
#define MSG_CHARINFO_MINUTE						1710		///< ��
#define MSG_CHARINFO_SECOND						1711		///< ��
// �߰� �κ�
#define MSG_CHARINFO_XP							1712		///< XP
#define MSG_CHARINFO_BOUNTY						1713		///< Bounty
#define MSG_CHARINFO_HP							1714		///< HP
#define MSG_CHARINFO_AP							1715		///< AP
#define MSG_CHARINFO_WEIGHT						1716		///< WT
#define MSG_CHARINFO_LEVELMARKER				1717		///< Lv.


/// ������ �޼���
#define MSG_GAME_JOIN_BATTLE					2000		///< $1�Բ��� ���ӿ� �����ϼ̽��ϴ�.
#define MSG_GAME_LEAVE_BATTLE					2001		///< $1�Բ��� ���ӿ��� �����ϼ̽��ϴ�.
#define MSG_GAME_LEVEL_UP						2002		///< $1�Բ��� ������ �ϼ̽��ϴ�.
#define MSG_GAME_LEVEL_DOWN						2003		///< $1�Բ��� �����ٿ� �ϼ̽��ϴ�.
#define MSG_GAME_SCORESCREEN_STAGENAME			2004		///< Ŭ���� ( %d vs %d )
// �߰��� �κ�.
#define MSG_GAME_FALL_NARAK						2005		///< �������� ������.
#define MSG_GAME_LOSE_BY_MY_BOMB				2006		///< ����� �ڽ��� ��ź���� ���Ͽ� �й� �Ͽ����ϴ�.
#define MSG_GAME_LOSE_MYSELF					2007		///< ����� ������ �й��Ͽ����ϴ�.
#define MSG_GAME_WHO_LOSE_SELF					2008		///< $1���� ������ �й��Ͽ����ϴ�.
#define MSG_GAME_WIN_FROM_WHO					2009		///< ����� $1�����κ��� �¸��Ͽ����ϴ�.
#define MSG_GAME_LOSE_FROM_WHO					2010		///< ����� $1�����κ��� �й� �Ͽ����ϴ�.
#define MSG_GAME_WHO_WIN_FROM_OTHER				2011		///< $1���� $2s�����κ��� �¸��Ͽ����ϴ�.
#define MSG_GAME_CLICK_FIRE						2012		///< �÷����Ϸ��� FireŰ�� �����ּ���!
#define MSG_GAME_WAIT_N_MIN						2013		///< $1�ʵ��� ��ٷ� �ּ���.
#define MSG_GAME_EXIT_N_MIN_AFTER				2014		///< $1���Ŀ� ���ӿ��� �����ϴ�.
// �߰��� �κ�. 11. 15.
#define MSG_GAME_WHISPER						2015		///< �ӼӸ�(%s) : %s
#define MSG_GAME_BRINGITEM						2016		///< �������� �����Խ��ϴ�.
#define MSG_GAME_NOTBRINGITEM					2017		///< �������� ������ �� �����ϴ�.
#define MSG_GAME_BUYITEM						2018		///< �����Ͽ����ϴ�.
#define MSG_GAME_NOTBUYITEM						2019		///< ������ �� �����ϴ�.
#define MSG_GAME_SELLITEM						2020		///< �Ǹ��Ͽ����ϴ�.
#define MSG_GAME_NOCHARACTER					2021		///< ������ �� �ִ� ĳ���Ͱ� �����ϴ�. ���� ĳ���͸� ������ �ֽñ� �ٶ��ϴ�.z
#define MSG_GAME_NOTSELLITEM					2022		///< �Ǹ��� �� �����ϴ�.
#define MSG_GAME_NEXT_N_MIN_AFTER				2023		///< $1���Ŀ� ���� ����� �̵��մϴ�.
#define MSG_GAME_GET_QUEST_ITEM					2024		///< ����Ʈ ������ $1�� ȹ���Ͽ����ϴ�.
#define MSG_GAME_GET_QUEST_ITEM2				2025		///< $1 $2�� ȹ��
#define MSG_GAME_OPEN_PORTAL					2026		///< ��Ż�� ���Ƚ��ϴ�.
#define MSG_GAME_MAKE_AUTO_BALANCED_TEAM		2027		///< �� �뷱���� ����Ǿ����ϴ�.
#define MSG_GANE_NO_QUEST_SCENARIO				2028		///< �´� �ó������� �����ϴ�.

#define MSG_ADMIN_ANNOUNCE						3000		///< ������ �޽���.



// �޴�
#define MSG_MENUITEM_NONE						8000		///< �޴�����

#define MSG_MENUITEM_FRIENDADD					8001		///< ģ���߰�
#define MSG_MENUITEM_FRIENDREMOVE				8002		///< ģ������
#define MSG_MENUITEM_FRIENDWHERE				8003		///< ��ġȮ��
#define MSG_MENUITEM_FRIENDFOLLOW				8004		///< ���󰡱�
#define MSG_MENUITEM_FRIENDWHISPER				8005		///< �Ӹ�
#define MSG_MENUITEM_FRIENDKICK					8006		///< �߹�
#define MSG_MENUITEM_FRIENDCLANINVITE			8007		///< Ŭ�����Ա���

#define MSG_MENUITEM_CLANGRADEMASTER			8008		///< Ŭ������������
#define MSG_MENUITEM_CLANGRADEADMIN				8009		///< ��ڷ� ����
#define MSG_MENUITEM_CLANMEMBER					8010		///< Ŭ�������� ����
#define MSG_MENUITEM_CLANKICK					8011		///< Ŭ������ ����
#define MSG_MENUITEM_CLANLEAVE					8012		///< Ŭ��Ż��

#define MSG_MENUITEM_SENTTOBANK					8013		///< �߾��������� ������

#define MSG_MENUITEM_OK							8014		///< Ȯ��
#define MSG_MENUITEM_CANCEL						8015		///< ���
#define MSG_MENUITEM_YES						8016		///< ��
#define MSG_MENUITEM_NO							8017		///< �ƴϿ�
#define MSG_MENUITEM_MESSAGE					8018		///< �޼���


/// ���
#define MSG_WORD_CLAN_NONE						9000		///< ����
#define MSG_WORD_CLAN_MASTER					9001		///< Ŭ��������
#define MSG_WORD_CLAN_ADMIN						9002		///< Ŭ�����
#define MSG_WORD_CLAN_MEMBER					9003		///< Ŭ����

#define MSG_WORD_ADMIN							9004		///< ���
#define MSG_WORD_DEVELOPER						9005		///< ������
#define MSG_WORD_COMMANDS						9006		///< ��ɾ�
#define MSG_WORD_HELP							9007		///< ����
#define MSG_WORD_USAGE							9008		///< ����

#define MSG_WORD_MALE							9100		///< ����
#define MSG_WORD_FEMALE							9101		///< ����
#define MSG_WORD_MALE_SHORT						9102		///< ��
#define MSG_WORD_FEMALE_SHORT					9103		///< ��

#define MSG_WORD_LOBBY							9200		///< �κ�
#define MSG_WORD_STAGE							9201		///< ��������
#define MSG_WORD_SHOP							9202		///< ����
#define MSG_WORD_EQUIPMENT						9203		///< ���
#define MSG_WORD_CASH							9204		///< Cash

#define MSG_WORD_FORMEN							9302		///< ���뼺�� : ������
#define MSG_WORD_FORWOMEN						9349		///< ���뼺�� : ������
#define MSG_WORD_WEARABLE						9302		///< ���뼺��
#define MSG_WORD_LIMITEDLEVEL					9303		///< ���ѷ���
#define MSG_WORD_WEIGHT							9304		///< ����
#define MSG_WORD_ATTRIBUTE_FIRE					9305		///< �ҼӼ�
#define MSG_WORD_ATTRIBUTE_COLD					9306		///< �����Ӽ�
#define MSG_WORD_ATTRIBUTE_POISON				9307		///< ���Ӽ�
#define MSG_WORD_ATTRIBUTE_LIGHTNING			9308		///< �����Ӽ�
#define MSG_WORD_RUNTIME						9309		///< ���ӽð�
#define MSG_WORD_BULLET							9310		///< ź��/źâ
#define MSG_WORD_ATTACK							9311		///< ���ݷ�
#define MSG_WORD_DELAY							9312		///< ������
#define MSG_WORD_MAXWEIGHT						9313		///< �ִ빫��
#define MSG_WORD_RUNSPEED						9314		///< �̵��ӵ�
#define MSG_WORD_DONOTJUMP						9315		///< ���� �Ұ�
#define MSG_WORD_DONOTDASH						9316		///< �뽬 �Ұ�
#define MSG_WORD_DONOTHANGWALL					9317		///< ��Ÿ�� �Ұ�
#define MSG_WORD_DAMAGE							9318		///< ������
#define MSG_WORD_QUEST							9319		///< ����Ʈ
#define MSG_WORD_ITEM							9320		///< ������
#define MSG_WORD_SACRIFICE						9321		///< ���
#define MSG_WORD_PLAYERS						9322		///< ���� �ο�
#define MSG_WORD_BLUETEAM						9323		///< û��
#define MSG_WORD_REDTEAM						9324		///< ȫ��
#define MSG_WORD_QUANTITY						9325		///< ���� ����
#define MSG_WORD_FINDTEAM						9326		///< ����� ã�� ��
#define MSG_WORD_GETITEMQTY						9327		///< ȹ�� ������ ��
#define MSG_WORD_REMAINNPC						9328		///< ���� NPC ��
#define MSG_WORD_RPROGRESS						9329		///< ���൵
#define MSG_WORD_REMAINTIME						9330		///< ���� �ð�
#define MSG_WORD_QUESTLEVELMARKER				9331		///< ��
#define MSG_WORD_ENDKILL						9363		///< ��ǥ KILL��
#define MSG_WORD_ROUND							9364		///< ����

#define MSG_WORD_RATE							9332		///< ������
#define MSG_WORD_GRADE							9333		///< ���
#define MSG_WORD_REGULAR						9334		///< Regular
#define MSG_WORD_LEGENDARY						9335		///< Legendary
#define MSG_WORD_BOSS							9336		///< Boss
#define MSG_WORD_ELITE							9337		///< Elite
#define MSG_WORD_VETERAN						9338		///< Veteran
#define MSG_WORD_VERYHARD						9339		///< �ſ� ����
#define MSG_WORD_HARD							9340		///< ����
#define MSG_WORD_NORAML							9341		///< ����
#define MSG_WORD_WEAK							9342		///< ����
#define MSG_WORD_VERYWEAK						9343		///< �ſ� ����

#define MSG_WORD_INFINITE						9344		///< ����
#define MSG_WORD_NONE							9345		///< ����
#define MSG_WORD_LEVELDIFF						9346		///< ������
#define MSG_WORD_PERMIT							9347		///< ���
#define MSG_WORD_PROHIBIT						9348		///< ����

// 2006�� 5�� 3�� �߰�
#define MSG_WORD_TYPE							9365		///< Type
#define MSG_WORD_EXP							9366		///< Exp
#define MSG_WORD_KILL							9367		///< Kill
#define MSG_WORD_DEATH							9368		///< Death
#define MSG_WORD_PING							9369		///< Ping

#define MSG_WORD_HEAD							9370		///< < Head >
#define MSG_WORD_CHEST							9371		///< < Chest >
#define MSG_WORD_HANDS							9372		///< < Hands >
#define MSG_WORD_LEGS							9373		///< < Legs >
#define MSG_WORD_FEET							9374		///< < Feet >
#define MSG_WORD_LFINGER						9375		///< < Left Finger >
#define MSG_WORD_RFINGER						9376		///< < Right Finger >
#define MSG_WORD_MELEE							9377		///< < Melee >
#define MSG_WORD_WEAPON1						9378		///< < Primary Weapon >
#define MSG_WORD_WEAPON2						9379		///< < Secondary Weapon >
#define MSG_WORD_ITEM1							9380		///< < Item 1 >
#define MSG_WORD_ITEM2							9381		///< < Item 2 >

#define MSG_SERVER_DEBUG						9382		///< Debug Server
#define MSG_SERVER_MATCH						9383		///< Match Server
#define MSG_SERVER_CLAN							9384		///< Clan Server
#define MSG_SERVER_QUEST						9385		///< Quest Server
#define MSG_SERVER_EVENT						9386		///< Event Server
#define MSG_SERVER_IGUNZ						9387		///< iGunZ Server

#define MSG_MT_DEATHMATCH_SOLO					9350
#define MSG_MT_DEATHMATCH_TEAM					9351
#define MSG_MT_GLADIATOR_SOLO					9352
#define MSG_MT_GLADIATOR_TEAM					9353
#define MSG_MT_ASSASSINATE						9354
#define MSG_MT_TRAINING							9355
#define MSG_MT_CLASSIC_SOLO						9356
#define MSG_MT_CLASSIC_TEAM						9357
#define MSG_MT_SURVIVAL							9358
#define MSG_MT_QUEST							9359
#define MSG_MT_BERSERKER						9360
#define MSG_MT_DEATHMATCH_TEAM2					9361
#define MSG_MT_DUEL								9362

#define MSG_REMAIND_PERIOD						9400
#define MSG_JOINED_STAGE						9401
#define MSG_JOINED_STAGE2						9402

#define MSG_WORD_ON								9500
#define MSG_WORD_OFF							9501

#define MSG_DISCONNMSG_XTRAPHACK				9601

#define MSG_HACKING_DETECTED					20000
#define MSG_EXPIRED								20001
#define MSG_SHOPMSG								20002
#define MSG_DONOTSUPPORT_GPCARD					20003
#define MSG_DIRECTX_NOT_INSTALL					20004
#define MSG_DIRECTX_DOWNLOAD_URL				20005
#define MSG_CHARDELETE_ERROR					20006

#define MSG_WRONG_WORD_NAME					100300


const char* ZGetSexStr(MMatchSex nSex, bool bShort=false);
void ZGetTimeStrFromSec(char* poutStr, size_t maxlen, u32 nSec);
template <size_t size>
void ZGetTimeStrFromSec(char(&poutStr)[size], u32 nSec) {
	return ZGetTimeStrFromSec(poutStr, size, nSec);
}