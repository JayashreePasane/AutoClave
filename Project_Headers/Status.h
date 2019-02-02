/*
 * Status.h
 *
 * Description:
 * File defines enums, macros et.al related to status variable type.
 * 
 *  Created on: Dec 11, 2016
 *      Author: 
 */

#ifndef STATUS_H_
#define STATUS_H_

typedef enum status_type {
	STATUS_SUCCESS = 0,
	STATUS_FAIL = 1,
	STATUS_INVALID_INPUT = 2,
	STATUS_UNKNOWN
}status_en;

#endif /* STATUS_H_ */
