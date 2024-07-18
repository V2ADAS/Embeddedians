/*
 * Personal_Parking.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Omar
 */

#include"Inc/Personal_Parking.h"



PersonalParking_Data_ST personalparking_data_st;

void PersonalParking_StartSaving(){

	memset(&personalparking_data_st, 0, sizeof(personalparking_data_st));
	personalparking_data_st.Global_CarHistory_ST_PTR = CarHistory_GetStructADD();
	/* Get start ptr */
	personalparking_data_st.Start_PTR = personalparking_data_st.Global_CarHistory_ST_PTR->Buffer_PTR;

}
void PersonalParking_EndSaving(){

	/* get end ptr */
	personalparking_data_st.End_PTR = personalparking_data_st.Global_CarHistory_ST_PTR->Buffer_PTR;

	u16 Loc_Start_idx=personalparking_data_st.Start_PTR;
	u16 Loc_End_idx=personalparking_data_st.End_PTR;
	CarHistory_CopyArray(personalparking_data_st.Global_CarHistory_ST_PTR->History_Buffer,
			personalparking_data_st.Parking_Buffer, Loc_Start_idx,Loc_End_idx , CARHIST_BUFFER_SIZE,CARHIST_NEEDED_STATES);

	/*Save to eprom*/
	HEPROM_vWriteData(PARKING_EPROM_START_PAGE, CMP_EPROM_PAGE_OFFSET,personalparking_data_st.Parking_Buffer
			,sizeof(personalparking_data_st.Parking_Buffer));





}
void PersonalParking_Apply(){

	/* read from eprom */
	HEPROM_vReadData(PARKING_EPROM_START_PAGE, CMP_EPROM_PAGE_OFFSET,personalparking_data_st.Parking_Buffer
			,sizeof(personalparking_data_st.Parking_Buffer));
	/* Set Applying Parameters*/
	personalparking_data_st.Global_CarHistory_ST_PTR->Apply_Buffer_Dir=FORWORD;
	personalparking_data_st.Global_CarHistory_ST_PTR->Apply_Buffer_PTR=personalparking_data_st.Parking_Buffer;
	/*Start Applying*/
	CarHistory_StartApplying();

}
