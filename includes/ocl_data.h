/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:08:48 by jhache            #+#    #+#             */
/*   Updated: 2018/06/27 11:15:47 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_DATA_H
# define OCL_DATA_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# ifndef KERNEL_PATH
#  error "KERNEL_PATH not specified"
# endif

/*
** program building's flags :
*/
# ifndef OPENCL_BUILD_FLAGS
#  error "OPENCL_BUILD_FLAGS not specified"
# endif

# define BUFF_SIZE 128
# define TAB_STEP_SIZE 10

/*
** definition of the t_ocl struct, which contain data for openCL functions.
*/
typedef struct			s_ocl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				ocl_img;
}						t_ocl;

struct s_rt;

/*
** definition of the t_kargs struct,
** which is just a container for several kernel args.
*/
typedef struct			s_kargs
{
	cl_mem				arg1;
	cl_mem				arg2;
	cl_mem				arg3;
	cl_mem				arg4;
	cl_mem				arg9;
	cl_mem				arg11;
}						t_kargs;

/*
typedef struct			s_ocl_stack
{
	size_t				wg_size[2];
}						t_ocl_stack;
*/

/*
** definition of the t_mem_info struct,
** which store data about the memory available on the device
** for the creation of the opencl pseudo-stack.
** NB: wg stand for work_group
*/
typedef struct				s_mem_info
{
	size_t					dim[3];
	size_t					wg_mult;
	cl_ulong				buffer_size;
}							t_mem_info;

/*
** OpenCL creation and destruction functions :
*/
cl_int					ocl_init(t_ocl *ocl, struct s_rt *core);
cl_int					init_kernel_args(t_ocl *ocl, struct s_rt *core);
cl_int					create_ocl_stack(struct s_rt *core, t_mem_info *mem_info);
cl_int					compute_work_size(t_mem_info *mem_info,
		struct s_rt *core);
void					update_frame_size(struct s_rt *core, t_mem_info *mem_info);
cl_int					ft_create_kernel(t_ocl *ocl);
cl_int					ocl_release(t_ocl *ocl, const char *debug_msg,
		cl_int ret);

/*
** Functions for reading the kernel :
*/
void					*free_strtab(char **tab, size_t size);
char					**read_src_file(const char *file_name, size_t *size);

#endif
