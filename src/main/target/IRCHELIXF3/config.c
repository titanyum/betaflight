/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#ifdef TARGET_CONFIG
#include "common/utils.h"

#include "drivers/io.h"

#include "fc/rc_controls.h"

#include "flight/failsafe.h"
#include "flight/mixer.h"
#include "flight/pid.h"

#include "rx/rx.h"

#include "config/config_profile.h"
#include "config/config_master.h"

void targetConfiguration(master_t *config)
{
	// 5.555 : 1 voltage divider(10k : 2.2k)
	// 5.555 * 10 for 0.1V * 4 = 222
	config->batteryConfig.vbatscale = 222;
	
	// 2.5 : 1 ratio for scale precision
	config->batteryConfig.vbatresdivmultiplier = 4;
	
	// INA139 parameters:
	// Vo = Is * Rs * Rl / 1k
	// Rs=0.0005, Rl=27000
	// V/A = (0.0005 * 0.001 * 27000)
	// rescale to 1/10th mV / A -> * 1000 * 10
	config->batteryConfig.currentMeterScale  = (0.0005 * 27000 * 0.001) * 1000 * 10;
	config->batteryConfig.currentMeterOffset = 7;
}
#endif
