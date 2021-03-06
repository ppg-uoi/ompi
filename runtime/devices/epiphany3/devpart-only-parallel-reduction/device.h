/*
  OMPi OpenMP Compiler
  == Copyright since 2001 the OMPi Team
  == Dept. of Computer Science & Engineering, University of Ioannina

  This file is part of OMPi.

  OMPi is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  OMPi is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OMPi; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "shared_data.h"

#define ALIGN8                        8
#define PARALLELLA_CORES              16
#define MAX_ACTIVE_REGIONS              1

#define __SETMYCB(v) (myeecb = (private_eecb_t *)(v))
#define __MYCB       ((private_eecb_t *) myeecb)

#define ORT_BARRIER_DELAY            100
#define omp_lock_t       ee_lock_t

typedef struct ee_lock_s
{
	int owner;
	int initialized;
	e_mutex_t mutex;
} ee_lock_t;

typedef struct __attribute__((aligned(ALIGN8)))
{
	volatile e_barrier_t  barriers[PARALLELLA_CORES]; /* Each PE */
	         e_barrier_t *tgt_bars[PARALLELLA_CORES]; /* has private variables */
} ee_barrier_t;

typedef struct __attribute__((aligned(ALIGN8))) private_eecb_s
{
	int thread_num;              // Id of a PE
	int parent_row;              // Row of master PE for use in ort_e_get_global_address
	int parent_col;              // Column of master PE for use in ort_e_get_global_address
	int parent_core;             // Master PE core
	int parent_level;            // Nested level of parent PE
	int core;
	int num_siblings;            // # threads in my team
	int num_children;
	int have_created_team;
	int activelevel;             // Parallel level
	struct private_eecb_s *parent;      // Pointer to parent thread

} private_eecb_t;


typedef struct __attribute__((aligned(ALIGN8)))
{
	void  *(* volatile func)(void *);      // parallel func
	volatile void  *args;                  // parallel func arguments
	volatile private_eecb_t *team_parent;  // parent of parallel team
} pe_shared_t;

int   omp_in_parallel(void);
int   omp_get_num_threads(void);
int   omp_get_thread_num(void);
int   omp_is_initial_device(void);
int   omp_get_num_procs(void);

int   ort_taskwait(int how);
int   ort_barrier_me(void);

int   e_my_barrier(void);
void  ort_barrier_init(void);

void  prepare_master(int teamsize);
void  ort_execute_parallel(void *(*func)(void *), void *shared, int nthr,
                           int iscombined, int procbind_type);
void  parallella_ort_power_save(void);
void  do_work(void);
void *ort_dev_gaddr(void *local_address);

void *read_address_from_master_local_address(void *local_address);
void *read_from_master_local_address(void *local_address);
void  write_to_master_local_address(void *local_address, void *data);
void *ort_e_get_global_address(int core, const void *ptr);
void *ort_e_get_global_master_address(const void *ptr);

int   ee_init_lock(ee_lock_t *lock, int type);
int   ee_set_lock(ee_lock_t *lock);
int   ee_unset_lock(ee_lock_t *lock);
int   ee_test_lock(ee_lock_t *lock);

void  ort_init(void);

#endif /* __DEVICE_H__ */
