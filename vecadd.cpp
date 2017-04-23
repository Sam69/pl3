#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<CL/cl.h>
using namespace std;

const char *ProgramSource="__kernel void vectorAdd(__global float *a, __global float *b, __global float *c)\n"\
	"{\n"\
	"int id=get_global_id(0);\n"\
	"c[id]=a[id]+b[id];\n"\
	"}\n";


int main()
{
	cl_context context;
	cl_kernel kernel;
	cl_command_queue command_queue;
	cl_program program;
	cl_int err;
	cl_uint no_of_platforms=0;
	cl_platform_id platform_id;
	cl_device_id device_id;
	cl_uint no_of_devices=0;
	cl_mem da,db,dc;

	size_t global;

	float *a,*b,*c;
	int n;
	cout<<"Enter size of the vectors: ";
	cin>>n;
	a=new float[n];
	b=new float[n];
	c=new float[n];

	cout<<"Enter Vector A:\n";
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<"Enter Vector B:\n";
	for(int i=0;i<n;i++)
	{
		cin>>b[i];
		c[i]=0;
	}

	if(clGetPlatformIDs(1,&platform_id,&no_of_platforms)!=CL_SUCCESS)
	{
		cout<<"Unable to get Platforms\n";
		getch();
		return 1;
	}

	if(clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_ALL,1,&device_id,&no_of_devices)!=CL_SUCCESS)
	{
		cout<<"Unable to get devices\n";
		getch();
		return 1;
	}

	context=clCreateContext(NULL,1,&device_id,NULL,NULL,&err);

	command_queue=clCreateCommandQueue(context,device_id,0,&err);

	program=clCreateProgramWithSource(context,1,(const char **)&ProgramSource,NULL,&err);

	if(clBuildProgram(program,0,NULL,NULL,NULL,NULL)!=CL_SUCCESS)
	{
		cout<<"Program Build Failed\n";
		getch();
		return 1;
	}

	kernel=clCreateKernel(program,"vectorAdd",&err);

	da=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*n,NULL,NULL);
	db=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*n,NULL,NULL);
	dc=clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(float)*n,NULL,NULL);

	clEnqueueWriteBuffer(command_queue,da,CL_TRUE,0,sizeof(float)*n,a,0,NULL,NULL);
	clEnqueueWriteBuffer(command_queue,db,CL_TRUE,0,sizeof(float)*n,b,0,NULL,NULL);
	//clEnqueueWriteBuffer(command_queue,dc,CL_TRUE,0,sizeof(float)*n,c,0,NULL,NULL);

	clSetKernelArg(kernel,0,sizeof(float)*n,&da);
	clSetKernelArg(kernel,1,sizeof(float)*n,&db);
	clSetKernelArg(kernel,2,sizeof(float)*n,&dc);

	global=n;

	clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global,NULL,0,NULL,NULL);
	clFinish(command_queue);

	clEnqueueReadBuffer(command_queue,dc,CL_TRUE,0,sizeof(float)*n,c,0,NULL,NULL);
	cout<<"Output Vector is"<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<c[i]<<endl;
	}
	getch();
	return 0;
}