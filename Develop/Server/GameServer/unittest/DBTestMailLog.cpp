#include "stdafx.h"
#include "DBTestGlobal.h"
#include "GDB_CODE.h"


SUITE(DB_MAIL_LOG)
{
	const int64 GSN				= 1;
	const int64 CSN				= 2;
	const int	WORLD			= 3;
	const int64 RCVR_GSN		= 4;
	const int64 RCVR_CSN		= 5;
	const int	CHAR_PTM		= 6;
	const int	DELTA_CHAR_PTM	= 7;
	const uint8	LEV				= 8;
	const int	CUR_MONEY		= 9;
	const uint8	SEND_MAIL_TYPE	= 10;
	const int	DELTA_MONEY		= 11;
	const int	POSTAGE			= 12;
	const int64	MAIL_UID		= 13;

	const int64 IUID_1				= 1;
	const int64 NEW_IUID_1			= 101;
	const int	ITEM_ID_1			= 2;
	const int	CUR_STACK_AMT_1		= 3;
	const int	DELTA_STACK_AMT_1	= 4;

	const int64 IUID_2				= 11;
	const int64 NEW_IUID_2			= 201;
	const int	ITEM_ID_2			= 12;
	const int	CUR_STACK_AMT_2		= 13;
	const int	DELTA_STACK_AMT_2	= 14;

	const int64 IUID_3				= 21;
	const int64 NEW_IUID_3			= 301;
	const int	ITEM_ID_3			= 22;
	const int	CUR_STACK_AMT_3		= 23;
	const int	DELTA_STACK_AMT_3	= 24;

	const int64 IUID_4				= 31;
	const int64 NEW_IUID_4			= 401;
	const int	ITEM_ID_4			= 32;
	const int	CUR_STACK_AMT_4		= 33;
	const int	DELTA_STACK_AMT_4	= 34;

	const int64 IUID_5				= 41;
	const int64 NEW_IUID_5			= 501;
	const int	ITEM_ID_5			= 42;
	const int	CUR_STACK_AMT_5		= 43;
	const int	DELTA_STACK_AMT_5	= 44;

	const int LOG_CODE_MAIL_SEND		= GDB_CODE::CD_L_MAIL_SEND;
	const int LOG_CODE_MAIL_RECIVE		= GDB_CODE::CD_L_MAIL_RECV;
	const int LOG_CODE_MAIL_DELETE		= GDB_CODE::CD_L_MAIL_DEL;

	const int LOG_CODE_MAIL_POSTAGE		= GDB_CODE::CD_L_MAIL_POSTAGE;
	const int LOG_CODE_MAIL_SEND_MONEY	= GDB_CODE::CD_L_MAIL_MONEY_ATTACH;
	const int LOG_CODE_MAIL_SEND_ITEM	= GDB_CODE::CD_L_MAIL_ITEM_ATTACH;
	const int LOG_CODE_MAIL_GET_MONEY	= GDB_CODE::CD_L_MAIL_MONEY_GAIN;
	const int LOG_CODE_MAIL_GET_ITEM	= GDB_CODE::CD_L_MAIL_ITEM_GAIN;
	

	void CHECK_MAIL_LOG(int64 GSN, int WORLD, int64 CSN, int CHAR_PTM, int64 MAIL_UID, int64 REF_ACCN_ID, int64 REF_CHAR_ID, int LOG_CODE)
	{
		TDBRecordSet rs;
		UTestDB.Execute(rs, L"SELECT CHAR_PTM, MAIL_ID, REF_ACCN_ID, REF_CHAR_ID FROM dbo.RZ_MAIL_LOG \
							 WHERE ACCN_ID = %I64d AND WORLD_ID = %d AND CHAR_ID = %I64d AND CODE = %d AND MAIL_TYPE = %d;"
			, GSN, WORLD, CSN, LOG_CODE, SEND_MAIL_TYPE);
		CHECK_EQUAL(1, rs.GetFetchedRowCount());
		CHECK_EQUAL(CHAR_PTM, rs.Field(L"CHAR_PTM").AsInt());
		CHECK_EQUAL(MAIL_UID, rs.Field(L"MAIL_ID").AsInt64());
		CHECK_EQUAL(REF_ACCN_ID, rs.Field(L"REF_ACCN_ID").AsInt64());
		CHECK_EQUAL(REF_CHAR_ID, rs.Field(L"REF_CHAR_ID").AsInt64());
		rs.Close();
	}

	void CHECK_MONEY(const int64 GSN, const int WORLD, const int64 CSN, const int CHAR_PTM, int DELTA_CHAR_PTM, uint8 LEV, const int CUR_MONEY, const int DELTA_MONEY
		, const int LOG_CODE, const int64 REF_CHAR_ID, const int64 REF_MAIL_UID)
	{
		TDBRecordSet rs;
		UTestDB.Execute(rs, L"SELECT CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, DELTA_MONEY, REF_OWNER_ID, MAIL_ID \
							 FROM dbo.RZ_ITEM_LOG \
							 WHERE ACCN_ID = %I64d AND WORLD_ID = %d AND OWNER_ID = %I64d AND CODE = %d;"
							 , GSN, WORLD, CSN, LOG_CODE);
		CHECK_EQUAL(1, rs.GetFetchedRowCount());
		CHECK_EQUAL(CHAR_PTM, rs.Field(L"CHAR_PTM").AsInt());
		CHECK_EQUAL(DELTA_CHAR_PTM, rs.Field(L"DELTA_CHAR_PTM").AsInt());
		CHECK_EQUAL(LEV, rs.Field(L"LEV").AsByte());
		CHECK_EQUAL(CUR_MONEY, rs.Field(L"CUR_MONEY").AsInt());
		CHECK_EQUAL(DELTA_MONEY, rs.Field(L"DELTA_MONEY").AsInt());
		CHECK_EQUAL(REF_CHAR_ID, rs.Field(L"REF_OWNER_ID").AsInt64());
		CHECK_EQUAL(REF_MAIL_UID, rs.Field(L"MAIL_ID").AsInt64());		
		rs.Close();
	}

	void CHECK_ITEM(const int64 GSN, const int WORLD, const int64 CSN, const int CHAR_PTM, int DELTA_CHAR_PTM, uint8 LEVEL, int CUR_MONEY, const int64 nIUID, const int ITEM_ID
		, const int16 CUR_STACK_AMT, const int16 DELTA_STACK_AMT, const int LOG_CODE, const int64 REF_ACCN_ID, const int64 REF_CHAR_ID, const int64 REF_IUID, const int64 REF_MAIL_UID)
	{
		TDBRecordSet rs;
		UTestDB.Execute(rs, L"SELECT CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, ITEM_ID, CUR_STACK_AMT, DELTA_STACK_AMT, REF_ACCN_ID, REF_OWNER_ID, REF_IUID, MAIL_ID \
							 FROM dbo.RZ_ITEM_LOG \
							 WHERE ACCN_ID = %I64d AND WORLD_ID = %d AND OWNER_ID = %I64d AND CODE = %d AND IUID = %I64d;"
							 , GSN, WORLD, CSN, LOG_CODE, nIUID);
		CHECK_EQUAL(1, rs.GetFetchedRowCount());
		CHECK_EQUAL(CHAR_PTM, rs.Field(L"CHAR_PTM").AsInt());
		CHECK_EQUAL(DELTA_CHAR_PTM, rs.Field(L"DELTA_CHAR_PTM").AsInt());
		CHECK_EQUAL(LEVEL, rs.Field(L"LEV").AsByte());
		CHECK_EQUAL(CUR_MONEY, rs.Field(L"CUR_MONEY").AsInt());
		CHECK_EQUAL(ITEM_ID, rs.Field(L"ITEM_ID").AsInt());
		CHECK_EQUAL(CUR_STACK_AMT, rs.Field(L"CUR_STACK_AMT").AsShort());
		CHECK_EQUAL(DELTA_STACK_AMT, rs.Field(L"DELTA_STACK_AMT").AsShort());
		CHECK_EQUAL(REF_ACCN_ID, rs.Field(L"REF_ACCN_ID").AsInt64());
		CHECK_EQUAL(REF_CHAR_ID, rs.Field(L"REF_OWNER_ID").AsInt64());
		CHECK_EQUAL(REF_IUID, rs.Field(L"REF_IUID").AsInt64());
		CHECK_EQUAL(REF_MAIL_UID, rs.Field(L"MAIL_ID").AsInt64());
		rs.Close();
	}

	LOGDB_TEST(USP_RZ_MAIL_SEND_LOG)
	{
		UTestDB.Execute(L"{CALL dbo.USP_RZ_MAIL_SEND_LOG (%I64d, %d, %I64d, %I64d, %I64d, %d, %d, %d, %d, %d, %d, %d, %I64d\
						 , %I64d, %I64d, %d, %d, %d \
						 , %I64d, %I64d, %d, %d, %d \
						 , %I64d, %I64d, %d, %d, %d \
						 , %I64d, %I64d, %d, %d, %d \
						 , %I64d, %I64d, %d, %d, %d)}"
						 , GSN, WORLD, CSN, RCVR_GSN, RCVR_CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, SEND_MAIL_TYPE, CUR_MONEY, -DELTA_MONEY, -POSTAGE, MAIL_UID
						 , IUID_1, NEW_IUID_1, ITEM_ID_1, CUR_STACK_AMT_1, DELTA_STACK_AMT_1
						 , IUID_2, NEW_IUID_2, ITEM_ID_2, CUR_STACK_AMT_2, DELTA_STACK_AMT_2
						 , IUID_3, NEW_IUID_3, ITEM_ID_3, CUR_STACK_AMT_3, DELTA_STACK_AMT_3
						 , IUID_4, NEW_IUID_4, ITEM_ID_4, CUR_STACK_AMT_4, DELTA_STACK_AMT_4
						 , IUID_5, NEW_IUID_5, ITEM_ID_5, CUR_STACK_AMT_5, DELTA_STACK_AMT_5);

		CHECK_MAIL_LOG(GSN, WORLD, CSN, CHAR_PTM, MAIL_UID, RCVR_GSN, RCVR_CSN, LOG_CODE_MAIL_SEND);
		CHECK_MAIL_LOG(RCVR_GSN, WORLD, RCVR_CSN, 0, MAIL_UID, GSN, CSN, LOG_CODE_MAIL_RECIVE);
		
		CHECK_MONEY(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY + DELTA_MONEY, -POSTAGE, LOG_CODE_MAIL_POSTAGE, RCVR_CSN, MAIL_UID);
		CHECK_MONEY(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, -DELTA_MONEY, LOG_CODE_MAIL_SEND_MONEY, RCVR_CSN, MAIL_UID);

		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_1, ITEM_ID_1, CUR_STACK_AMT_1, -DELTA_STACK_AMT_1, LOG_CODE_MAIL_SEND_ITEM, RCVR_GSN, RCVR_CSN, NEW_IUID_1, MAIL_UID);
		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_2, ITEM_ID_2, CUR_STACK_AMT_2, -DELTA_STACK_AMT_2, LOG_CODE_MAIL_SEND_ITEM, RCVR_GSN, RCVR_CSN, NEW_IUID_2, MAIL_UID);
		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_3, ITEM_ID_3, CUR_STACK_AMT_3, -DELTA_STACK_AMT_3, LOG_CODE_MAIL_SEND_ITEM, RCVR_GSN, RCVR_CSN, NEW_IUID_3, MAIL_UID);
		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_4, ITEM_ID_4, CUR_STACK_AMT_4, -DELTA_STACK_AMT_4, LOG_CODE_MAIL_SEND_ITEM, RCVR_GSN, RCVR_CSN, NEW_IUID_4, MAIL_UID);
		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_5, ITEM_ID_5, CUR_STACK_AMT_5, -DELTA_STACK_AMT_5, LOG_CODE_MAIL_SEND_ITEM, RCVR_GSN, RCVR_CSN, NEW_IUID_5, MAIL_UID);		
	}

	LOGDB_TEST(USP_RZ_MAIL_GET_MONEY_LOG)
	{
		UTestDB.Execute(L"{CALL dbo.USP_RZ_MAIL_GET_MONEY_LOG (%I64d, %d, %I64d, %d, %d, %d, %d, %d, %I64d)}"
			, GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, DELTA_MONEY, MAIL_UID);

		CHECK_MONEY(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, DELTA_MONEY, LOG_CODE_MAIL_GET_MONEY, 0, MAIL_UID);
	}

	LOGDB_TEST(USP_RZ_MAIL_GET_ITEM_LOG)
	{
		UTestDB.Execute(L"{CALL dbo.USP_RZ_MAIL_GET_ITEM_LOG (%I64d, %d, %I64d, %d, %d, %d, %d, %I64d, %d, %d, %I64d)}"
			, GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_1, ITEM_ID_1, DELTA_STACK_AMT_1, MAIL_UID);

		CHECK_ITEM(GSN, WORLD, CSN, CHAR_PTM, DELTA_CHAR_PTM, LEV, CUR_MONEY, IUID_1, ITEM_ID_1, DELTA_STACK_AMT_1, DELTA_STACK_AMT_1, LOG_CODE_MAIL_GET_ITEM, 0, 0, 0, MAIL_UID);
	}

	LOGDB_TEST(USP_RZ_MAIL_DELETE_LOG)
	{
		UTestDB.Execute(L"{CALL dbo.USP_RZ_MAIL_DELETE_LOG (%I64d, %d, %I64d, %d, %I64d)}"
			, GSN, WORLD, CSN, CHAR_PTM, MAIL_UID);

		TDBRecordSet rs;
		UTestDB.Execute(rs, L"SELECT CHAR_PTM, MAIL_ID FROM dbo.RZ_MAIL_LOG WHERE ACCN_ID = %I64d AND WORLD_ID = %d AND CHAR_ID = %I64d AND CODE = %d;"
			, GSN, WORLD, CSN, LOG_CODE_MAIL_DELETE);
		CHECK_EQUAL(1, rs.GetFetchedRowCount());
		CHECK_EQUAL(CHAR_PTM, rs.Field(L"CHAR_PTM").AsInt());
		CHECK_EQUAL(MAIL_UID, rs.Field(L"MAIL_ID").AsInt64());
		rs.Close();
	}
}