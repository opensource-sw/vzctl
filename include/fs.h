/*
 *  Copyright (C) 2000-2008, Parallels, Inc. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef	_FS_H_
#define _FS_H_

#include "types.h"
#include "quota.h"

#define MNT_DETACH		0x00000002
/** Action script prefixes.
 */
#define MOUNT_PREFIX		"mount"
#define UMOUNT_PREFIX		"umount"
#define START_PREFIX		"start"
#define STOP_PREFIX		"stop"

#define DESTR_PREFIX		"destroyed"

/**  Data structure for file system parameter.
 */
typedef struct {
	char *private;		/**< CT private path. */
	char *private_orig;	/**< original not expanded private path. */
	char *root;		/**< CT root path. */
	char *root_orig;	/**< original not expanded root path. */
	char *tmpl;		/**< TEMPLATE path. */
	int noatime;
} fs_param;

/** Get CT mount status.
 *
 * @param root		CT root.
 * @return		 1 - CT mounted
 *			 0 - CT unmounted.
 *			-1 - error
 */
int vps_is_mounted(char *root);

/** Mount CT.
 *
 * @param veid		CT ID.
 * @param fs		file system parameters.
 * @param dq		disk quota parameters.
 * @return		0 on success.
 */
int fsmount(envid_t veid, fs_param *fs, dq_param *dq);

/** Mount CT and run mount action script if exists.
 *
 * @param h		CT handler.
 * @param veid		CT ID.
 * @param fs		file system parameters.
 * @param dq		disk quota parameters.
 * @param skip		skip mount action scrips
 * @return		0 on success.
 */
int vps_mount(vps_handler *h, envid_t veid, fs_param *fs, dq_param *dq,
	skipFlags skip);

/** Unmount CT.
 *
 * @param veid		CT ID.
 * @param root		CT root.
 * @return		0 on success.
 */
int fsumount(envid_t veid, char *root);

/** Unmount CT and run unmount action script if exists.
 *
 * @param h		CT handler.
 * @param veid		CT ID.
 * @param root		CT root.
 * @param skip		skip unmount action scrips
 * @return		0 on success.
 */
int vps_umount(vps_handler *h, envid_t veid, char *root, skipFlags skip);

int vps_set_fs(fs_param *g_fs, fs_param *fs);

extern const char *vz_fs_get_name();
extern int vz_fs_is_mounted(char *root);
extern int vz_mount(fs_param *fs, int remount);

#endif
