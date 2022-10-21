#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

#define  MAX 13

float (*A)[8192];
float (*B)[8192];
float (*C)[8192];
int N = 8192;

static inline void getMatrices()
{
        A=malloc(N*N* sizeof(float));
        B=malloc(N*N* sizeof(float));
        C=malloc(N*N* sizeof(float));
}

static inline void initializeMatrices()
{
         srand(time(0));
     int i = 0, j = 0;
     for(i = 0; i < 8192; i++)
        for(int j = 0; j < 8192; j++)
        {
                        A[i][j]=0.0;
                        B[i][j] = rand();
                        C[i][j] = rand();
        }
}
static inline void freeMatrices()
{
        free(A);
        free(B);
        free(C);
}

static inline void multiply_k_i_j(int b)
{
	int ii = 0, jj = 0, kk = 0;
	int i,j,k;
    for (k=0; k < N; k=k+b)
    	for(i=0; i<N; i=i+b)
    		for(j=0; j<N; j=j+b)
    		{
           	 	for(ii=i; ii<i+b && ii < N; ii++)
           			for(jj=j; jj < j+b && jj < N; jj++)
           				for(kk=k; kk < k+b && kk < N; kk++)
							A[ii][jj] += B[ii][kk] * C[kk][jj];
        	}
		
}



static inline long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
    int ret;

   ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                   group_fd, flags);
    return ret;
}

int
main(int argc, char **argv)
{

		if(argc==1)
        {
                printf("Block size is missing!!");
                return 0;
        }
        int b=atoi(argv[1]);
        
        getMatrices();
        initializeMatrices();

    struct perf_event_attr pe[MAX];
    long long count[MAX];
    int fd[MAX];
    
    __u64 perf_hw_cache_id[MAX]=	{
    									0, 0, 0, 
    									PERF_COUNT_HW_CACHE_L1D, 
    									PERF_COUNT_HW_CACHE_L1I, 
    									PERF_COUNT_HW_CACHE_LL, 
    									PERF_COUNT_HW_CACHE_DTLB, 
    									PERF_COUNT_HW_CACHE_ITLB,
    									PERF_COUNT_HW_CACHE_L1D, 
    									PERF_COUNT_HW_CACHE_L1I, 
    									PERF_COUNT_HW_CACHE_LL, 
    									PERF_COUNT_HW_CACHE_DTLB, 
    									PERF_COUNT_HW_CACHE_ITLB
    								};
    
    __u64 perf_hw_cache_op_id;
    __u64 perf_hw_cache_op_result_id=PERF_COUNT_HW_CACHE_RESULT_MISS;
    
    
	__u32 type[MAX]={PERF_TYPE_HARDWARE, PERF_TYPE_SOFTWARE, PERF_TYPE_SOFTWARE };
	__u64 config[MAX]={PERF_COUNT_HW_CACHE_MISSES, PERF_COUNT_SW_TASK_CLOCK, PERF_COUNT_SW_PAGE_FAULTS};
	
	
	char * str[MAX]=	{
							"cache-misses", 
							"time elapsed (in secs) " , 
							"page-faults", 
							"L1-dcache-load-misses", 
							"L1-icache-load-misses", 
							"LLC-load-misses",
							"dTLB-load-misses", 
							"iTLB-load-misses",
							"L1-dcache-store-misses", 
							"L1-icache-store-misses", 
							"LLC-store-misses",
							"dTLB-store-misses", 
							"iTLB-store-misses"
						};
	
	int i;
	perf_hw_cache_op_id=PERF_COUNT_HW_CACHE_OP_READ;
	for (i=3;i<8;i++)
	{	
		type[i]= PERF_TYPE_HW_CACHE;
		config[i]=(perf_hw_cache_id[i]) | (perf_hw_cache_op_id << 8) | (perf_hw_cache_op_result_id << 16);
	}
	
	perf_hw_cache_op_id=PERF_COUNT_HW_CACHE_OP_WRITE;
	for (i=8;i<13;i++)
	{
		type[i]=PERF_TYPE_HW_CACHE;
		config[i]=(perf_hw_cache_id[i]) | (perf_hw_cache_op_id << 8) | (perf_hw_cache_op_result_id << 16);
	}
	
	for (i=0;i<MAX;i++)
	{
		if (i==12 || i==8 || i==9)
			continue;
   		memset(&pe[i], 0, sizeof(struct perf_event_attr));
    	pe[i].type = type[i];//PERF_TYPE_SOFTWARE;//PERF_TYPE_HARDWARE;
    	pe[i].size = sizeof(struct perf_event_attr);
    	pe[i].config = config[i];//PERF_COUNT_SW_PAGE_FAULTS;//PERF_COUNT_HW_INSTRUCTIONS;
    	pe[i].disabled = 1;
    	pe[i].exclude_kernel = 1;
    	pe[i].exclude_hv = 1;
	
   		fd[i] = perf_event_open(&pe[i], 0, -1, -1, 0);
    	if (fd[i] == -1) {
       	fprintf(stderr, "Error opening %s\n", str[i] /*pe[i].config*/);
       	//exit(EXIT_FAILURE);
    	}
    }

	for(i=0;i<MAX;i++)
	{
   		ioctl(fd[i], PERF_EVENT_IOC_RESET, 0);
   		ioctl(fd[i], PERF_EVENT_IOC_ENABLE, 0);
	}
	
	
   	        multiply_k_i_j(b);


	for(i=0;i<MAX;i++)
   		ioctl(fd[i], PERF_EVENT_IOC_DISABLE, 0);
   	
   	for(i=0;i<MAX;i++)
   	{
   		if (i==12 || i==8 || i==9)
			continue;
   		read(fd[i], &count[i], sizeof(long long));
		if(i==1)
   			printf("%s = %0.2f\n",str[i], count[i]/1e+9);
   		else
   			printf("%s = %lld\n",str[i], count[i]);
   		close(fd[i]);
	}
	                freeMatrices();

   	
}
