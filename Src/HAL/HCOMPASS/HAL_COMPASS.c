/*
 * HAL_COMPASS.c
 *
 *  Created on: Dec 19, 2023
 *      Author: Omar
 */


void HAL_CMP_vInit(){

	/* Send CMP ADD with write */

	/* Send ConfigREGA ADD --> 0x00 */

	/* Send 0x70 --> 8 sampled average , 15 HZ data rate  */


	/* Send CMP ADD with write */

	/* Send ConfigREGB ADD --> 0x01 */

	/* Send 0xA0 --> 5 Gain  */


	/* Send CMP ADD with write */

	/* Send ModREG ADD --> 0x02 */

	/* Send 0x00 --> continuous measurment mode  */


	/*** wait 6ms ***/


}
void HAL_CMP_GetReading();
